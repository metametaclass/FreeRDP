/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * FreeRDP Proxy Server
 *
 * Copyright 2019 Kobi Mizrachi <kmizrachi18@gmail.com>
 * Copyright 2019 Idan Freiberg <speidy@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <winpr/crt.h>
#include <winpr/collections.h>

#include "pf_log.h"
#include "pf_server.h"
#include "pf_config.h"
#include "pf_modules.h"

#define TAG PROXY_TAG("config")

#define CONFIG_PRINT_SECTION(section) WLog_INFO(TAG, "\t%s:", section)
#define CONFIG_PRINT_STR(config, key) WLog_INFO(TAG, "\t\t%s: %s", #key, config->key)
#define CONFIG_PRINT_BOOL(config, key) WLog_INFO(TAG, "\t\t%s: %s", #key, config->key ? "TRUE" : "FALSE")
#define CONFIG_PRINT_UINT16(config, key) WLog_INFO(TAG, "\t\t%s: %"PRIu16"", #key, config->key)
#define CONFIG_PRINT_UINT32(config, key) WLog_INFO(TAG, "\t\t%s: %"PRIu32"", #key, config->key)

BOOL pf_config_get_uint16(wIniFile* ini, const char* section, const char* key, UINT16* result)
{
	int val;

	val = IniFile_GetKeyValueInt(ini, section, key);
	if ((val < 0) || (val > UINT16_MAX))
	{
		WLog_ERR(TAG, "[%s]: invalid value %d for key '%s.%s'.", __FUNCTION__, val, section, key);
		return FALSE;
	}

	*result = (UINT16) val;
	return TRUE;
}

BOOL pf_config_get_uint32(wIniFile* ini, const char* section, const char* key, UINT32* result)
{
	int val;

	val = IniFile_GetKeyValueInt(ini, section, key);
	if ((val < 0) || (val > INT32_MAX))
	{
		WLog_ERR(TAG, "[%s]: invalid value %d for key '%s.%s'.", __FUNCTION__, val, section, key);
		return FALSE;
	}

	*result = (UINT32) val;
	return TRUE;
}

BOOL pf_config_get_bool(wIniFile* ini, const char* section, const char* key)
{
	int num_value;
	const char* str_value;

	str_value = IniFile_GetKeyValueString(ini, section, key);
	if (!str_value)
	{
		WLog_WARN(TAG, "[%s]: key '%s.%s' not found, value defaults to false.", __FUNCTION__, key, section);
		return FALSE;
	}

	if (strcmp(str_value, "TRUE") == 0 || strcmp(str_value, "true") == 0)
		return TRUE;

	num_value = IniFile_GetKeyValueInt(ini, section, key);

	if (num_value == 1)
		return TRUE;

	return FALSE;
}

const char* pf_config_get_str(wIniFile* ini, const char* section, const char* key)
{
	const char* value;

	value = IniFile_GetKeyValueString(ini, section, key);

	if (!value)
	{
		WLog_ERR(TAG, "[%s]: key '%s.%s' not found.", __FUNCTION__, key, section);
		return NULL;
	}

	return value;
}

static BOOL pf_config_load_server(wIniFile* ini, proxyConfig* config)
{
	const char* host;

	if (!pf_config_get_uint16(ini, "Server", "Port", &config->Port))
		return FALSE;

	host = pf_config_get_str(ini, "Server", "Host");

	if (!host)
		return FALSE;

	config->Host = _strdup(host);

	if (!config->Host)
		return FALSE;
	
	return TRUE;
}

static BOOL pf_config_load_target(wIniFile* ini, proxyConfig* config)
{
	const char* target_host;

	if (!pf_config_get_uint16(ini, "Target", "Port", &config->TargetPort))
		return FALSE;

	target_host = pf_config_get_str(ini, "Target", "Host");

	if (!target_host)
		return FALSE;

	config->TargetHost = _strdup(target_host);
	if (!config->TargetHost)
		return FALSE;

	config->UseLoadBalanceInfo = pf_config_get_bool(ini, "Target", "UseLoadBalanceInfo");
	return TRUE;
}

static BOOL pf_config_load_channels(wIniFile* ini, proxyConfig* config)
{
	config->GFX = pf_config_get_bool(ini, "Channels", "GFX");
	config->DisplayControl = pf_config_get_bool(ini, "Channels", "DisplayControl");
	config->Clipboard = pf_config_get_bool(ini, "Channels", "Clipboard");
	config->AudioOutput = pf_config_get_bool(ini, "Channels", "AudioOutput");
	return TRUE;
}

static BOOL pf_config_load_input(wIniFile* ini, proxyConfig* config)
{
	config->Keyboard = pf_config_get_bool(ini, "Input", "Keyboard");
	config->Mouse = pf_config_get_bool(ini, "Input", "Mouse");
	return TRUE;
}

static BOOL pf_config_load_security(wIniFile* ini, proxyConfig* config)
{
	config->ServerTlsSecurity = pf_config_get_bool(ini, "Security", "ServerTlsSecurity");
	config->ServerRdpSecurity = pf_config_get_bool(ini, "Security", "ServerRdpSecurity");

	config->ClientTlsSecurity = pf_config_get_bool(ini, "Security", "ClientTlsSecurity");
	config->ClientNlaSecurity = pf_config_get_bool(ini, "Security", "ClientNlaSecurity");
	config->ClientRdpSecurity = pf_config_get_bool(ini, "Security", "ClientRdpSecurity");
	return TRUE;
}

static BOOL pf_config_load_clipboard(wIniFile* ini, proxyConfig* config)
{
	config->TextOnly = pf_config_get_bool(ini, "Clipboard", "TextOnly");

	if (!pf_config_get_uint32(ini, "Clipboard", "MaxTextLength", &config->MaxTextLength))
		return FALSE;

	return TRUE;
}

static BOOL pf_config_load_modules(wIniFile* ini, proxyConfig* config)
{
	int index;
	int modules_count = 0;
	char** module_names = NULL;

	module_names = IniFile_GetSectionKeyNames(ini, "Modules", &modules_count);

	for (index = 0; index < modules_count; index++)
	{
		char* module_name = module_names[index];
		const char* path = pf_config_get_str(ini, "Modules", module_name);

		if (!path)
			continue;

		if (!pf_modules_register_new(path, module_name))
		{
			WLog_ERR(TAG, "pf_config_load_modules(): failed to register %s (%s)", module_name, path);
			continue;
		}

		WLog_INFO(TAG, "module '%s' is loaded!", module_name);
	}

	free(module_names);
	return TRUE;
}

static BOOL pf_config_load_captures(wIniFile* ini, proxyConfig* config)
{
	const char* captures_dir;

	config->SessionCapture = pf_config_get_bool(ini, "SessionCapture", "Enabled");
	if (!config->SessionCapture)
		return TRUE;

	captures_dir = pf_config_get_str(ini, "SessionCapture", "CapturesDirectory");

	if (!captures_dir)
		return FALSE;

	config->CapturesDirectory = strdup(captures_dir);
	if (!config->CapturesDirectory)
		return FALSE;

	if (!PathFileExistsA(config->CapturesDirectory))
	{
		if (!CreateDirectoryA(config->CapturesDirectory, NULL))
		{
			free(config->CapturesDirectory);
			config->CapturesDirectory = NULL;
			return FALSE;
		}
	}

	return TRUE;
}

BOOL pf_server_config_load(const char* path, proxyConfig* config)
{
	BOOL ok = FALSE;
	wIniFile* ini = IniFile_New();

	if (!ini)
	{
		WLog_ERR(TAG, "pf_server_load_config(): IniFile_New() failed!");
		return FALSE;
	}

	if (IniFile_ReadFile(ini, path) < 0)
	{
		WLog_ERR(TAG, "pf_server_load_config(): IniFile_ReadFile() failed!");
		goto out;
	}

	if (!pf_config_load_server(ini, config))
		goto out;

	if (!pf_config_load_target(ini, config))
		goto out;

	if (!pf_config_load_channels(ini, config))
		goto out;

	if (!pf_config_load_input(ini, config))
		goto out;

	if (!pf_config_load_security(ini, config))
		goto out;

	if (!pf_config_load_modules(ini, config))
		goto out;

	if (!pf_config_load_clipboard(ini, config))
		goto out;

	if (!pf_config_load_captures(ini, config))
		goto out;

	ok = TRUE;
out:
	IniFile_Free(ini);
	return ok;
}

void pf_server_config_print(proxyConfig* config)
{
	WLog_INFO(TAG, "Proxy configuration:");

	CONFIG_PRINT_SECTION("Server");
	CONFIG_PRINT_STR(config, Host);
	CONFIG_PRINT_UINT16(config, Port);
	CONFIG_PRINT_BOOL(config, SessionCapture);

	if (!config->UseLoadBalanceInfo)
	{
		CONFIG_PRINT_SECTION("Target");
		CONFIG_PRINT_STR(config, TargetHost);
		CONFIG_PRINT_UINT16(config, TargetPort);
	}

	CONFIG_PRINT_SECTION("Input");
	CONFIG_PRINT_BOOL(config, Keyboard);
	CONFIG_PRINT_BOOL(config, Mouse);

	CONFIG_PRINT_SECTION("Server Security");
	CONFIG_PRINT_BOOL(config, ServerTlsSecurity);
	CONFIG_PRINT_BOOL(config, ServerRdpSecurity);

	CONFIG_PRINT_SECTION("Client Security");
	CONFIG_PRINT_BOOL(config, ClientNlaSecurity);
	CONFIG_PRINT_BOOL(config, ClientTlsSecurity);
	CONFIG_PRINT_BOOL(config, ClientRdpSecurity);

	CONFIG_PRINT_SECTION("Channels");
	CONFIG_PRINT_BOOL(config, GFX);
	CONFIG_PRINT_BOOL(config, DisplayControl);
	CONFIG_PRINT_BOOL(config, Clipboard);
	CONFIG_PRINT_BOOL(config, AudioOutput);

	CONFIG_PRINT_SECTION("Clipboard");
	CONFIG_PRINT_BOOL(config, TextOnly);
	if (config->MaxTextLength > 0)
		CONFIG_PRINT_UINT32(config, MaxTextLength);

	CONFIG_PRINT_SECTION("SessionCapture");
	CONFIG_PRINT_BOOL(config, SessionCapture);
	CONFIG_PRINT_STR(config, CapturesDirectory);
}

void pf_server_config_free(proxyConfig* config)
{
	free(config->CapturesDirectory);
	free(config->TargetHost);
	free(config->Host);
	free(config);
}
