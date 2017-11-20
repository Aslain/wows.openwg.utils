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

#pragma once

#include <string>

enum ClientBranch
{
	WoT_Unknown,
	WoT_Release,
	WoT_CommonTest,
	WoT_SuperTest,
	WoT_Sandbox,
};

enum ClientType
{
	WoTType_Unknown,
	WoTType_SD,
	WoTType_HD,
};


class WotClient {
private:
	bool isValid = false;

	std::wstring path;
	
	ClientBranch clientBranch = ClientBranch::WoT_Unknown;
	ClientType clientType = ClientType::WoTType_Unknown;

	std::wstring exeVersion;
	std::wstring clientVersion;

	std::wstring clientLocale;

	void updateData();
	bool updateData_apptype();
	bool updateData_versionxml();
	void clear();

public:
	bool IsValid();

	WotClient();
	WotClient(const std::wstring& wotDirectory);

	std::wstring GetPath();
	void SetPath(const std::wstring& path);

	ClientBranch GetClientBranch();
	std::wstring GetClientExeVersion();
	std::wstring GetClientVersion();
	std::wstring GetClientLocale();
	ClientType GetClientType();

};
