/* Copyright (c) 2017, Mikhail Paulyshka
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#include "wgc.h"
#include "common/filesystem.h"

#include <filesystem>

#include "rapidxml.hpp"

using namespace rapidxml;

std::wstring WGC::GetWGCInstallPath()
{
	std::wstring programDataPath = Filesystem::GetProgramDataPath();

	std::wstring wgcPathFile(programDataPath + L"\\Wargaming.net\\GameCenter\\data\\wgc_path.dat");
	if (std::filesystem::exists(wgcPathFile))
	{
		std::wstring path = Filesystem::GetFileContent(wgcPathFile);
		if (std::filesystem::exists(path + L"\\wgc.exe"))
		{
			return path;
		}
	}
	else if (std::filesystem::exists(programDataPath + L"\\Wargaming.net\\GameCenter\\wgc.exe"))
	{
		return programDataPath + L"\\Wargaming.net\\GameCenter";
	}

	return std::wstring();
}


std::vector<std::wstring> WGC::GetWotPaths()
{
	std::wstring programDataPath = Filesystem::GetProgramDataPath();

	std::vector<std::wstring> wotPaths;

	try
	{
		for (auto& p : std::filesystem::directory_iterator(programDataPath + L"\\Wargaming.net\\GameCenter\\apps\\wot\\"))
		{
			std::wstring path = Filesystem::GetFileContent(p.path().wstring());

			if (std::filesystem::exists(path + L"\\WorldOfTanks.exe"))
			{
				wotPaths.push_back(path);
			}
		}
	}
	catch (const std::exception&) {}

	return wotPaths;
}


std::wstring WGC::GetWotPreferedPath()
{
	std::wstring wgcPath = GetWGCInstallPath();

	std::wstring preferences(wgcPath + L"\\preferences.xml");
	if (!std::filesystem::exists(preferences))
		return std::wstring();

	std::wstring content = Filesystem::GetFileContent(preferences);
	xml_document<wchar_t> doc;
	doc.parse<0>(_wcsdup(content.c_str()));

	//try to get preferences.xml->protocol->application->games_manager->selectedGames->WOT
	try
	{
		xml_node<wchar_t> *protocol = doc.first_node(L"protocol");
		if (protocol == nullptr)
			return std::wstring();

		xml_node<wchar_t> *application = protocol->first_node(L"application");
		if (application == nullptr)
			return std::wstring();

		xml_node<wchar_t> *gamemanager = application->first_node(L"games_manager");
		if (gamemanager == nullptr)
			return std::wstring();

		xml_node<wchar_t> *selectedgames = gamemanager->first_node(L"selectedGames");
		if (selectedgames == nullptr)
			return std::wstring();

		xml_node<wchar_t> *target = selectedgames->first_node(L"WOT");
		if (target == nullptr)
			return std::wstring();

		if (std::filesystem::exists(std::wstring(target->value()) + L"\\WorldOfTanks.exe"))
		{
			return std::wstring(target->value());
		}
		else {
			return std::wstring();
		}

	}
	catch (const std::exception&) {
		return std::wstring();
	}
}
