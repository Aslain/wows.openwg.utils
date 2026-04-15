#include <regex>
#include <memory>
#include <algorithm>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <limits>
#include <optional>
#include <sstream>
#include <system_error>
#include <unordered_set>
#include <vector>
#include <string_view>

#include <pugixml.hpp>
#include <json/json.h>

#include "archive/api_archive.h"
#include "common/encoding.h"
#include "fs/fs.h"
#include "json/json_utils.h"
#include "string/string.h"
#include "process/process_module.h"
#include "wot/client_wot.h"

namespace {

std::optional<std::string> ExtractEntryToString(void* archive, const std::wstring& entry) {
    if (!archive) {
        return std::nullopt;
    }

    ARCHIVE_FileContext context{};
    if (!ARCHIVE_GetEntryInfoW(archive, entry.c_str(), &context)) {
        return std::nullopt;
    }

    if (context.is_directory) {
        return std::nullopt;
    }

    if (context.uncompressed_size == 0) {
        return std::string{};
    }

    if (context.uncompressed_size > std::numeric_limits<size_t>::max()) {
        return std::nullopt;
    }

    const size_t bufferSize = static_cast<size_t>(context.uncompressed_size);
    std::string buffer;
    buffer.resize(bufferSize);
    void* destination = buffer.data();

    uint64_t written = 0;
    if (!ARCHIVE_ExtractToMemory(archive, entry.c_str(), destination, bufferSize, &written)) {
        return std::nullopt;
    }

    buffer.resize(static_cast<size_t>(written));
    return buffer;
}

uint64_t DetermineNextResourceId(const Json::Value& resourceMap) {
    uint64_t maxId = 0;
    bool hasValue = false;

    for (const auto& key : resourceMap.getMemberNames()) {
        uint64_t numeric = 0;
        const auto result = std::from_chars(key.data(), key.data() + key.size(), numeric, 16);
        if (result.ec == std::errc()) {
            if (!hasValue || numeric > maxId) {
                maxId = numeric;
                hasValue = true;
            }
        }
    }

    if (!hasValue) {
        return 0;
    }

    if (maxId == std::numeric_limits<uint64_t>::max()) {
        return std::numeric_limits<uint64_t>::max();
    }

    return maxId + 1;
}

uint32_t MergeModItems(const Json::Value& items,
                       Json::Value& resourceMap,
                       uint64_t& nextId,
                       std::unordered_set<std::string>& seenItemIds) {
    if (!items.isArray()) {
        return 0;
    }

    uint32_t addedItems = 0;

    for (const auto& item : items) {
        if (!item.isObject()) {
            continue;
        }

        if (!item.isMember("itemID")) {
            continue;
        }

        const auto& itemIdValue = item["itemID"];
        if (!itemIdValue.isString()) {
            continue;
        }

        const std::string itemId = itemIdValue.asString();
        if (itemId.empty()) {
            continue;
        }

        if (!seenItemIds.insert(itemId).second) {
            continue;
        }

        if (nextId == std::numeric_limits<uint64_t>::max()) {
            break;
        }

        Json::Value payload = item;
        payload.removeMember("itemID");

        std::ostringstream keyStream;
        keyStream << std::hex << std::nouppercase << nextId;
        const std::string key = keyStream.str();

        resourceMap[key] = payload;

        ++nextId;
        ++addedItems;
    }

    return addedItems;
}

std::optional<std::wstring> GetEntryNameByIndex(void* archive, uint32_t index) {
    if (!archive) {
        return std::nullopt;
    }

    uint32_t required = ARCHIVE_GetEntryNameW(archive, index, nullptr, 0);
    if (required <= 1) {
        return std::nullopt;
    }

    std::wstring buffer(required, L'\0');
    uint32_t written = ARCHIVE_GetEntryNameW(archive, index, buffer.data(), required);
    if (written == 0) {
        return std::nullopt;
    }

    if (!buffer.empty() && buffer.back() == L'\0') {
        buffer.resize(buffer.size() - 1);
    } else {
        buffer.resize(written);
    }

    return buffer;
}

} // namespace

namespace OpenWG::Utils::WoT {

    ClientWoT::ClientWoT(std::filesystem::path path, LauncherFlavour launcherFlavour) : m_path(path.lexically_normal()),
                                                                                        m_launcherFlavour(launcherFlavour) {
        rescan();
    }

    ClientWoT::~ClientWoT() = default;


    bool ClientWoT::IsValid() const {
        return m_valid;
    }

    ClientBranch ClientWoT::GetBranch() const {
        return m_branch;
    }

    std::wstring ClientWoT::GetExeName() const
    {
        return m_exe_name;
    }

    LauncherFlavour ClientWoT::GetLauncherFlavour() const {
        return m_launcherFlavour;
    }

    std::wstring ClientWoT::GetLocale() const {
        return m_locale;
    }

    std::filesystem::path ClientWoT::GetPath() const {
        return m_path;
    }

    std::wstring ClientWoT::GetRealm() const {
        return m_realm;
    }

    ClientType ClientWoT::GetType() const {
        return m_type;
    }

    ClientVendor ClientWoT::GetVendor() const {
        return m_vendor;
    }

    std::wstring ClientWoT::GetPathMods() const {
        return m_path_mods;
    }

    std::wstring ClientWoT::GetPathResmods() const {
        return m_path_resmods;
    }

    const std::vector<ClientWoT::PackageDefinition>& ClientWoT::GetPackages() const {
        return m_packages;
    }

    bool ClientWoT::ExtractPackageFileToFile(const std::wstring& package_relative_path,
                                             const std::wstring& entry_path,
                                             const std::filesystem::path& destination) {
        if (package_relative_path.empty() || entry_path.empty() || destination.empty()) {
            return false;
        }

        auto package_path = resolvePackagePath(package_relative_path);
        if (package_path.empty()) {
            return false;
        }

        const std::wstring package_w = package_path.wstring();
        void* archive_handle = ARCHIVE_OpenW(package_w.c_str());
        if (!archive_handle) {
            return false;
        }

        auto archive_closer = [](void* handle) {
            ARCHIVE_Close(handle);
        };
        std::unique_ptr<void, decltype(archive_closer)> archive_guard(archive_handle, archive_closer);

        std::filesystem::path destination_normalized = destination;
        destination_normalized = destination_normalized.lexically_normal();
        const std::wstring destination_w = destination_normalized.wstring();

        return ARCHIVE_ExtractToFileW(archive_guard.get(), entry_path.c_str(), destination_w.c_str());
    }

    bool ClientWoT::ExtractPackageFileToMemory(const std::wstring& package_relative_path,
                                               const std::wstring& entry_path,
                                               void* destination,
                                               uint64_t destination_size,
                                               uint64_t* bytes_written) {
        if (bytes_written) {
            *bytes_written = 0;
        }

        if (package_relative_path.empty() || entry_path.empty()) {
            return false;
        }

        auto package_path = resolvePackagePath(package_relative_path);
        if (package_path.empty()) {
            return false;
        }

        const std::wstring package_w = package_path.wstring();
        void* archive_handle = ARCHIVE_OpenW(package_w.c_str());
        if (!archive_handle) {
            return false;
        }

        auto archive_closer = [](void* handle) {
            ARCHIVE_Close(handle);
        };
        std::unique_ptr<void, decltype(archive_closer)> archive_guard(archive_handle, archive_closer);

        ARCHIVE_FileContext context{};
        if (!ARCHIVE_GetEntryInfoW(archive_guard.get(), entry_path.c_str(), &context)) {
            return false;
        }

        if (context.is_directory) {
            return false;
        }

        if (context.uncompressed_size == 0) {
            if (!destination && destination_size == 0) {
                return true;
            }

            if (!destination) {
                return false;
            }

            if (bytes_written) {
                *bytes_written = 0;
            }
            return true;
        }

        if (!destination) {
            if (bytes_written) {
                *bytes_written = context.uncompressed_size;
            }
            return false;
        }

        if (destination_size < context.uncompressed_size) {
            if (bytes_written) {
                *bytes_written = context.uncompressed_size;
            }
            return false;
        }

        uint64_t extracted_bytes = 0;
        if (!ARCHIVE_ExtractToMemory(archive_guard.get(),
                                     entry_path.c_str(),
                                     destination,
                                     destination_size,
                                     &extracted_bytes)) {
            return false;
        }

        if (bytes_written) {
            *bytes_written = extracted_bytes;
        }

        return true;
    }

    std::wstring ClientWoT::GetVersionClient() const {
        return m_versionClient.Get();
    }

    std::wstring ClientWoT::GetVersionExe() const {
        return m_versionExe;
    }

    bool ClientWoT::IsStarted() const {
        bool result{false};
        for (auto &process: Process::GetProcessList()) {
            if (Filesystem::IsSubpath(process.first, GetPath())) {
                auto process_name = String::ToLower(process.first.filename().wstring());
                if (process_name == String::ToLower(m_exe_name)) {
                    result = true;
                    break;
                }
            }
        }

        return result;
    }

    bool ClientWoT::IsVersionMatch(const std::wstring &pattern) const {
        std::wregex regex(pattern);
        std::wsmatch match;
        return std::regex_match(m_versionClient.Get().begin(), m_versionClient.Get().end(), match, regex);
    }

    bool ClientWoT::Terminate() {
        bool result{false};
        for (auto &process: Process::GetProcessList()) {
            if (Filesystem::IsSubpath(process.first, GetPath())) {
                auto process_name = String::ToLower(process.first.filename().wstring());
                if (process_name == String::ToLower(m_exe_name)) {
                    result = Process::TerminateProcess(process.second);
                }
            }
        }

        return result;
    }

    //
    // Public/Cache
    //

	ClientCache ClientWoT::GetCacheSupported() const
	{
		ClientCache cache{};
		return cache;
	}

	ClientCache ClientWoT::GetCachePresent() const
	{
		ClientCache result{};
		return result;
	}

	bool ClientWoT::ClearCache(ClientCache cache_type)
	{
		return false;
	}
    
    bool ClientWoT::BuildResMapFromMods()
    {
        if (!IsValid() || m_path_resmods.empty() || m_packages.empty())
        {
            return false;
        }
    
        const std::wstring resMapEntry = L"gui/unbound/res_map.json";
        const std::wstring resMapEntryNormalized = OpenWG::Utils::String::NormalizePathLower(resMapEntry);
    
        Json::Value resourceMap(Json::objectValue);
        bool resourceMapLoaded = false;
    
        const auto archiveCloser = [](void* handle)
        {
            if (handle)
            {
                ARCHIVE_Close(handle);
            }
        };
    
        for (const auto& package : m_packages)
        {
            auto packagePath = resolvePackagePath(package.relativePath);
            if (packagePath.empty())
            {
                continue;
            }
    
            const std::wstring packagePathWide = packagePath.wstring();
            std::unique_ptr<void, decltype(archiveCloser)> archiveGuard(ARCHIVE_OpenW(packagePathWide.c_str()), archiveCloser);
            if (!archiveGuard)
            {
                continue;
            }
    
            const uint32_t entriesCount = ARCHIVE_GetEntriesCount(archiveGuard.get());
            for (uint32_t entryIndex = 0; entryIndex < entriesCount; ++entryIndex)
            {
                auto entryName = GetEntryNameByIndex(archiveGuard.get(), entryIndex);
                if (!entryName)
                {
                    continue;
                }
    
                if (OpenWG::Utils::String::NormalizePathLower(*entryName) != resMapEntryNormalized)
                {
                    continue;
                }
    
                auto content = ExtractEntryToString(archiveGuard.get(), *entryName);
                if (!content)
                {
                    continue;
                }
    
                OpenWG::Utils::String::StripUtf8Bom(*content);
                OpenWG::Utils::String::ReplaceAll(*content, ",}", "}");
                OpenWG::Utils::String::ReplaceAll(*content, ",]", "]");
    
                auto parsed = OpenWG::Utils::JSON::ParseJsonUtf8(*content, false);
                if (!parsed || !parsed->isObject())
                {
                    continue;
                }
    
                resourceMap = *parsed;
                resourceMapLoaded = true;
                break;
            }
    
            if (resourceMapLoaded)
            {
                break;
            }
        }
    
        if (!resourceMapLoaded)
        {
            return false;
        }
    
        uint64_t nextResourceId = DetermineNextResourceId(resourceMap);
        std::unordered_set<std::string> seenItemIds;
        seenItemIds.reserve(128);
    
        auto processConfigPayload = [&](std::string&& payload)
        {
            OpenWG::Utils::String::StripUtf8Bom(payload);
            OpenWG::Utils::String::ReplaceAll(payload, ",}", "}");
            OpenWG::Utils::String::ReplaceAll(payload, ",]", "]");
    
            auto parsed = OpenWG::Utils::JSON::ParseJsonUtf8(payload, false);
            if (!parsed || !parsed->isArray())
            {
                return;
            }
    
            MergeModItems(*parsed, resourceMap, nextResourceId, seenItemIds);
        };
    
        const bool processWotmod = (m_vendor & WoT_Vendor_WG) == WoT_Vendor_WG || m_vendor == WoT_Vendor_Unknown;
        const bool processMtmod = (m_vendor & WoT_Vendor_Lesta) == WoT_Vendor_Lesta || m_vendor == WoT_Vendor_Unknown;
    
        std::filesystem::path modsRoot;
        if (!m_path_mods.empty())
        {
            modsRoot = m_path / std::filesystem::path(m_path_mods);
        }
    
        std::error_code fsError;
        if (!modsRoot.empty() && std::filesystem::exists(modsRoot, fsError))
        {
            const auto dirOptions = std::filesystem::directory_options::skip_permission_denied;
            for (std::filesystem::recursive_directory_iterator it(modsRoot, dirOptions, fsError), end;
                 it != end;
                 it.increment(fsError))
            {
                if (fsError)
                {
                    fsError.clear();
                    continue;
                }
    
                if (!it->is_regular_file(fsError))
                {
                    if (fsError)
                    {
                        fsError.clear();
                    }
                    continue;
                }
    
                const std::wstring extensionLower = OpenWG::Utils::String::ToLower(it->path().extension().wstring());
                if (!((processWotmod && extensionLower == L".wotmod") || (processMtmod && extensionLower == L".mtmod")))
                {
                    continue;
                }
    
                std::unique_ptr<void, decltype(archiveCloser)> modArchive(ARCHIVE_OpenW(it->path().wstring().c_str()), archiveCloser);
                if (!modArchive)
                {
                    continue;
                }
    
                const uint32_t modEntries = ARCHIVE_GetEntriesCount(modArchive.get());
                for (uint32_t entryIndex = 0; entryIndex < modEntries; ++entryIndex)
                {
                    auto entryName = GetEntryNameByIndex(modArchive.get(), entryIndex);
                    if (!entryName)
                    {
                        continue;
                    }
    
                    const auto normalizedEntry = OpenWG::Utils::String::NormalizePathLower(*entryName);
                    if (!(normalizedEntry.starts_with(L"mods/configs/res_map") && normalizedEntry.ends_with(L".json")))
                    {
                        continue;
                    }
    
                    auto content = ExtractEntryToString(modArchive.get(), *entryName);
                    if (!content)
                    {
                        continue;
                    }
    
                    processConfigPayload(std::move(*content));
                }
            }
        }
    
        std::vector<std::string> memberNames = resourceMap.getMemberNames();
        struct KeyMetadata
        {
            bool parsed{false};
            uint64_t value{0};
            std::size_t originalIndex{0};
            std::string key;
        };
    
        std::vector<KeyMetadata> metadata;
        metadata.reserve(memberNames.size());
    
        for (std::size_t index = 0; index < memberNames.size(); ++index)
        {
            KeyMetadata meta{};
            meta.key = memberNames[index];
            meta.originalIndex = index;
    
            auto result = std::from_chars(meta.key.data(), meta.key.data() + meta.key.size(), meta.value, 16);
            meta.parsed = (result.ec == std::errc());
    
            metadata.emplace_back(std::move(meta));
        }
    
        std::sort(metadata.begin(), metadata.end(), [](const KeyMetadata& lhs, const KeyMetadata& rhs)
        {
            if (lhs.parsed != rhs.parsed)
            {
                return lhs.parsed > rhs.parsed;
            }
    
            if (lhs.parsed && rhs.parsed && lhs.value != rhs.value)
            {
                return lhs.value < rhs.value;
            }
    
            return lhs.originalIndex < rhs.originalIndex;
        });
    
        Json::Value ordered(Json::objectValue);
        for (const auto& meta : metadata)
        {
            ordered[meta.key] = resourceMap[meta.key];
        }
    
        Json::StreamWriterBuilder writerBuilder;
        writerBuilder["indentation"] = "";
        writerBuilder["enableYAMLCompatibility"] = false;
        writerBuilder["emitUTF8"] = true;
    
        std::string serialized = Json::writeString(writerBuilder, ordered);
        if (!serialized.empty() && serialized.back() == '\n')
        {
            serialized.pop_back();
        }
    
        std::filesystem::path outputPath = m_path / std::filesystem::path(m_path_resmods) / "gui" / "unbound" / "res_map.json";
        std::filesystem::path outputDirectory = outputPath.parent_path();
    
        fsError.clear();
        std::filesystem::create_directories(outputDirectory, fsError);
        if (fsError)
        {
            return false;
        }
    
        std::string existingContent;
        {
            std::ifstream existingStream(outputPath, std::ios::binary);
            if (existingStream)
            {
                existingContent.assign(std::istreambuf_iterator<char>(existingStream), std::istreambuf_iterator<char>());
            }
        }
    
        if (existingContent == serialized)
        {
            return true;
        }
    
        std::ofstream outputStream(outputPath, std::ios::binary | std::ios::trunc);
        if (!outputStream)
        {
            return false;
        }
    
        outputStream.write(serialized.data(), static_cast<std::streamsize>(serialized.size()));
        outputStream.flush();
    
        return outputStream.good();
    }
    
    //
    // Private
    //

	bool ClientWoT::isValid(bool skip_exe)
	{
		bool has_game_info = Filesystem::Exists(m_path / "game_info.xml");
		bool has_preferences = Filesystem::Exists(m_path / "preferences.xml");
		bool has_paths_xml_in_bin = false;
		
		std::filesystem::path bin_folder = m_path / "bin";
		if (std::filesystem::exists(bin_folder)) {
			for (const auto& bin_entry : std::filesystem::directory_iterator(bin_folder)) {
				if (!bin_entry.is_directory()) continue;
				if (Filesystem::Exists(bin_entry.path() / "bin64" / "paths.xml")) {
					has_paths_xml_in_bin = true;
					break;
				}
			}
		}
		
		bool valid = Filesystem::Exists(m_path) && (has_game_info || (has_preferences && has_paths_xml_in_bin));
		
		if (!skip_exe) {
			if (m_exe_name.empty()) {
				valid = false;
			}
			else {
				bool exe_found = false;
				if (std::filesystem::exists(bin_folder)) {
					for (const auto& bin_entry : std::filesystem::directory_iterator(bin_folder)) {
						if (!bin_entry.is_directory()) continue;
						if (Filesystem::Exists(bin_entry.path() / "bin64" / m_exe_name)) {
							exe_found = true;
							break;
						}
					}
				}
				if (!exe_found) {
					exe_found = Filesystem::Exists(m_path / m_exe_name);
				}
				valid = valid && exe_found;
			}
		}
		
		return valid;
	}

    void ClientWoT::rescan() {
        m_valid = false;

        if (!isValid(true)) {
            return;
        }

        rescanAppType();
        rescanVersion();
        rescanBinPath();
        rescanExe();

        if (!isValid(false)) {
            return;
        }

        rescanGameInfo();
        rescanPaths();

        m_valid = true;
    }

    void ClientWoT::rescanAppType() {
        m_type = WoT_Type_Unknown;
        auto apptypexml = m_path / L"app_type.xml";
        if (Filesystem::Exists(apptypexml)) {

            pugi::xml_document doc;
            if (!doc.load_file(apptypexml.wstring().c_str())) {
                m_type = WoT_Type_Unknown;
            }

            auto apptype = doc.select_node(L"/protocol/app_type");
            if (apptype) {
                std::wstring value = apptype.node().first_child().value();
                if (value == L"low") {
                    m_type = WoT_Type_SD;
                } else if (value == L"high") {
                    m_type = WoT_Type_HD;
                }
            }
        }
    }
	
	void ClientWoT::rescanBinPath() {
		m_binPath.clear();
		
		std::wstring target_version;
		auto gameinfoxml = m_path / L"game_info.xml";
		if (Filesystem::Exists(gameinfoxml)) {
			pugi::xml_document doc;
			if (doc.load_file(gameinfoxml.wstring().c_str())) {
				auto version_node = doc.select_node(L"/protocol/game/part_versions/version[@name='client']");
				if (version_node) {
					std::wstring installed = version_node.node().attribute(L"installed").value();
					auto parts = String::Split(installed, L'.');
					if (parts.size() >= 5) {
						target_version = parts[4];
					}
				}
			}
		}
		
		if (target_version.empty()) {
			auto prefxml = m_path / L"preferences.xml";
			if (Filesystem::Exists(prefxml)) {
				std::ifstream ifs(prefxml, std::ios::binary);
				if (ifs) {
					std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
					size_t start = content.find("<last_server_version>");
					if (start != std::string::npos) {
						start += 21;
						size_t end = content.find("</last_server_version>", start);
						if (end != std::string::npos) {
							std::string version_str = content.substr(start, end - start);
							version_str.erase(std::remove_if(version_str.begin(), version_str.end(), ::isspace), version_str.end());
							size_t last_comma = version_str.find_last_of(',');
							if (last_comma != std::string::npos) {
								std::string bin_num = version_str.substr(last_comma + 1);
								target_version = std::wstring(bin_num.begin(), bin_num.end());
							}
						}
					}
				}
			}
		}
		
		if (target_version.empty()) {
			std::filesystem::path bin_folder = m_path / "bin";
			if (std::filesystem::exists(bin_folder)) {
				uint64_t latest_version = 0;
				for (const auto& bin_entry : std::filesystem::directory_iterator(bin_folder)) {
					if (!bin_entry.is_directory()) continue;
					std::wstring folder_name = bin_entry.path().filename().wstring();
					try {
						uint64_t version_num = std::stoull(folder_name);
						if (version_num > latest_version) {
							latest_version = version_num;
							target_version = folder_name;
						}
					} catch (...) {}
				}
			}
		}
		
		if (!target_version.empty()) {
			std::filesystem::path bin_folder = m_path / "bin" / target_version;
			if (std::filesystem::exists(bin_folder) &&
				(Filesystem::Exists(bin_folder / "bin64" / L"WorldOfWarships64.exe") ||
				 Filesystem::Exists(bin_folder / "bin64" / L"Korabli64.exe"))) {
				m_binPath = bin_folder;
			}
		}
	}

	void ClientWoT::rescanExe() {
		m_versionExe.clear();
		m_exe_name.clear();

		if (m_vendor == WoT_Vendor_Lesta) {
			m_exe_name = L"Korabli64.exe";
		}
		else {
			m_exe_name = L"WorldOfWarships64.exe";
		}

		if (!m_binPath.empty()) {
			auto path = m_binPath / "bin64" / m_exe_name;
			if (Filesystem::Exists(path)) {
				m_versionExe = Filesystem::GetExeVersion(path.wstring());
				return;
			}
		}

		auto path = m_path / m_exe_name;
		if (Filesystem::Exists(path)) {
			m_versionExe = Filesystem::GetExeVersion(path.wstring());
						return;
		}
	}

	void ClientWoT::rescanGameInfo() {
		m_locale.clear();
		auto gameinfoxml = m_path / L"game_info.xml";
		if (Filesystem::Exists(gameinfoxml)) {

			pugi::xml_document doc;
			if (doc.load_file(gameinfoxml.wstring().c_str())) {
				// id
				auto id = doc.select_node(L"/protocol/game/id");
				if (id) {
					std::wstring id_str = id.node().first_child().value();
					if (id_str.contains(L".PT.")) {
						m_branch = ClientBranch::WoT_Branch_CommonTest;
					}
				}

				// localization
				auto localization = doc.select_node(L"/protocol/game/localization");
				if (localization) {
					m_locale = localization.node().first_child().value();
				}
			}
		}
		
		if (m_locale.empty()) {
			auto prefxml = m_path / L"preferences.xml";
			if (Filesystem::Exists(prefxml)) {
				std::ifstream ifs(prefxml, std::ios::binary);
				if (ifs) {
					std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
					size_t start = content.find("<locale>");
					if (start != std::string::npos) {
						start += 8;
						size_t end = content.find("</locale>", start);
						if (end != std::string::npos) {
							std::string locale_str = content.substr(start, end - start);
							locale_str.erase(std::remove_if(locale_str.begin(), locale_str.end(), ::isspace), locale_str.end());
							m_locale = std::wstring(locale_str.begin(), locale_str.end());
							std::transform(m_locale.begin(), m_locale.end(), m_locale.begin(), ::toupper);
						}
					}
				}
			}
		}
	}

	void ClientWoT::rescanPaths() {
		m_path_mods.clear();
		m_path_resmods.clear();
		m_packages.clear();

		auto normalizeRelativePath = [](std::wstring value) {
			value = String::Trim(value);
			value = String::Replace(value, L"\\", L"/");
			while (value.starts_with(L"./")) {
				value = value.substr(2);
			}
			return value;
		};

		auto pathsxml = m_binPath.empty() ? m_path / L"paths.xml" : m_binPath / L"bin64" / L"paths.xml";
		if (Filesystem::Exists(pathsxml)) {
			pugi::xml_document doc;
			if (doc.load_file(pathsxml.wstring().c_str())) {
				auto pathNodes = doc.select_nodes(L"/root/Paths/Path");
				for (const auto& pathNode : pathNodes) {
					const auto& xmlNode = pathNode.node();
					std::wstring relativePath = normalizeRelativePath(std::wstring(xmlNode.text().as_string()));
					if (relativePath.empty()) {
						continue;
					}

					if (m_path_resmods.empty() && relativePath.find(L"res_mods") != std::wstring::npos) {
						std::filesystem::path fullPath = pathsxml.parent_path() / relativePath;
						fullPath = fullPath.lexically_normal();
						std::wstring fullPathStr = fullPath.wstring();
						std::wstring rootPathStr = m_path.wstring();
						if (fullPathStr.find(rootPathStr) == 0) {
							m_path_resmods = fullPathStr.substr(rootPathStr.length() + 1);
						} else {
							m_path_resmods = relativePath;
						}
					} else if (m_path_mods.empty() && relativePath.find(L"mods") != std::wstring::npos) {
						std::filesystem::path fullPath = m_path / relativePath;
						fullPath = fullPath.lexically_normal();
						std::wstring fullPathStr = fullPath.wstring();
						std::wstring rootPathStr = m_path.wstring();
						if (fullPathStr.find(rootPathStr) == 0) {
							m_path_mods = fullPathStr.substr(rootPathStr.length() + 1);
						} else {
							m_path_mods = relativePath;
						}
					}
				}

				auto packageNodes = doc.select_nodes(L"/root/Paths/Packages/Package");
				for (const auto& packageNode : packageNodes) {
					const auto& xmlNode = packageNode.node();
					std::wstring relativePath = normalizeRelativePath(std::wstring(xmlNode.text().as_string()));
					if (relativePath.empty()) {
						continue;
					}

					PackageDefinition definition{};
					definition.relativePath = relativePath;

					if (auto attribute = xmlNode.attribute(L"type")) {
						auto tokens = String::Split(std::wstring(attribute.as_string()), L',');
						definition.types.reserve(tokens.size());
						for (auto& token : tokens) {
							std::wstring trimmed = String::Trim(token);
							if (!trimmed.empty()) {
								definition.types.emplace_back(trimmed);
							}
						}
					}

					m_packages.emplace_back(definition);
				}
			}
		}

		if (m_path_resmods.empty() && !m_binPath.empty()) {
			std::filesystem::path resmods_path = m_binPath / L"res_mods";
			if (std::filesystem::exists(resmods_path)) {
				std::wstring fullPathStr = resmods_path.wstring();
				std::wstring rootPathStr = m_path.wstring();
				if (fullPathStr.find(rootPathStr) == 0) {
					m_path_resmods = fullPathStr.substr(rootPathStr.length() + 1);
				}
			}
		}
	}

	void ClientWoT::rescanVersion() {
		m_branch = ClientBranch::WoT_Branch_Release;
		m_realm.clear();
		m_versionClient.Set(L"0.0.0.0");

		auto gameinfoxml = m_path / L"game_info.xml";
		if (Filesystem::Exists(gameinfoxml)) {
			pugi::xml_document doc;
			if (doc.load_file(gameinfoxml.wstring().c_str())) {
				auto id_node = doc.select_node(L"/protocol/game/id");
				if (id_node) {
					std::wstring id_str = id_node.node().first_child().value();
					if (id_str.contains(L".PT.")) {
						m_branch = ClientBranch::WoT_Branch_CommonTest;
					}
				}

				auto version_node = doc.select_node(L"/protocol/game/part_versions/version[@name='client']");
				if (version_node) {
					std::wstring version_raw = version_node.node().attribute(L"installed").value();
					if (!version_raw.empty()) {
						auto parts = String::Split(version_raw, L'.');
						std::wstring final_version = version_raw;
						if (parts.size() >= 5) {
							final_version = parts[0] + L"." + parts[1] + L"." + parts[2] + L"." + parts[3];
						}
						m_versionClient.Set(final_version);
					}
				}
			}
		}

		auto prefxml = m_path / L"preferences.xml";
		if (Filesystem::Exists(prefxml)) {
			std::ifstream ifs(prefxml, std::ios::binary);
			if (ifs) {
				std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
				
				size_t start = content.find("<active_server>");
				if (start != std::string::npos) {
					start += 15;
					size_t end = content.find("</active_server>", start);
					if (end != std::string::npos) {
						std::string server_str = content.substr(start, end - start);
						server_str.erase(std::remove_if(server_str.begin(), server_str.end(), [](unsigned char c) { 
							return std::isspace(c); 
						}), server_str.end());
						
						if (server_str.find("EU") != std::string::npos || server_str.find("eu") != std::string::npos) m_realm = L"EU";
						else if (server_str.find("NA") != std::string::npos || server_str.find("na") != std::string::npos) m_realm = L"NA";
						else if (server_str.find("ASIA") != std::string::npos || server_str.find("asia") != std::string::npos) m_realm = L"ASIA";
						else if (server_str.find("RU") != std::string::npos || server_str.find("ru") != std::string::npos) m_realm = L"RU";
						else if (server_str.find("360") != std::string::npos || server_str.find("CHINA") != std::string::npos || server_str.find("china") != std::string::npos) m_realm = L"CN";
						else if (server_str.find("Publictest") != std::string::npos || server_str.find("publictest") != std::string::npos) m_branch = WoT_Branch_CommonTest;
					}
				}
				
				if (m_versionClient.Get() == L"0.0.0.0") {
					start = content.find("<clientVersion>");
					if (start != std::string::npos) {
						start += 15;
						size_t end = content.find("</clientVersion>", start);
						if (end != std::string::npos) {
							std::string version_str = content.substr(start, end - start);
							version_str.erase(std::remove_if(version_str.begin(), version_str.end(), ::isspace), version_str.end());
							std::replace(version_str.begin(), version_str.end(), ',', '.');
							m_versionClient.Set(std::wstring(version_str.begin(), version_str.end()));
						}
					}
				}
			}
		}

		m_vendor = (m_realm == L"RU") ? WoT_Vendor_Lesta : WoT_Vendor_WG;
	}

    std::filesystem::path ClientWoT::resolvePackagePath(const std::wstring& package_relative_path) const {
        if (package_relative_path.empty()) {
            return {};
        }

        std::filesystem::path relative_path(package_relative_path);
        std::filesystem::path combined = relative_path.is_absolute()
                                         ? relative_path
                                         : (m_path / relative_path);
        combined = combined.lexically_normal();

        if (!Filesystem::IsSubpath(combined, m_path)) {
            return {};
        }

        if (!Filesystem::Exists(combined)) {
            return {};
        }

        std::error_code ec;
        if (std::filesystem::is_directory(combined, ec)) {
            return {};
        }
        if (ec) {
            return {};
        }

        return combined;
    }

}
