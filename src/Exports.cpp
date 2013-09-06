#include "stdafx.hpp"
#include "Exports.hpp"
#include "MircFunction.hpp"
#include "WinampCommunicator.hpp"

using std::string;

const string author = "Bui";
const string version = "1.0d";
const int maxCallerArgumentAndReturnCommandOrData = 900;
WinampCommunicator winamp;

#pragma region Winamp
MIRCTOOLS_API MIRC_FUNCTION(GetWinamp) {
	int msg = atoi(caller_argument_and_return_command_or_data);
	try {
		switch (msg) {
			case 1: lstrcpy(caller_argument_and_return_command_or_data, winamp.getTitle()); break;
			case 2: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp.getAction(WinampInfoPairs::TrackCount)); break;
			case 3: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp.getAction(WinampInfoPairs::Kbps)); break;
			case 4: wsprintf(caller_argument_and_return_command_or_data, "%li", winamp.getAction(WinampInfoPairs::TotalTrackTime)); break;
			case 5: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp.getAction(WinampInfoPairs::CurrentPos)); break;
			case 6: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp.getAction(WinampInfoPairs::Khz)); break;
			case 7: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp.getAction(WinampInfoPairs::Mode)); break;
		}
	}
	catch (std::runtime_error) {
		lstrcpy(caller_argument_and_return_command_or_data, "Error: Unable to find Winamp");
	}
	return filled_caller_argument_with_result;
}

MIRCTOOLS_API MIRC_FUNCTION(SendWinamp) {
	int msg = atoi(caller_argument_and_return_command_or_data);
	try {
		switch (msg) {
			case 1: winamp.sendAction(WinampCommands::Play); break;
			case 2: winamp.sendAction(WinampCommands::Next); break;
			case 3: winamp.sendAction(WinampCommands::Last); break;
			case 4: winamp.sendAction(WinampCommands::Pause); break;
			case 5: winamp.sendAction(WinampCommands::Stop); break;
			case 6: winamp.sendAction(WinampCommands::FadeStop); break;
			case 7: winamp.sendAction(WinampCommands::FastForward); break;
			case 8: winamp.sendAction(WinampCommands::Rewind); break;
			case 9: winamp.sendAction(WinampCommands::Kill); break;
			case 10: winamp.sendAction(WinampCommands::FileDialog); break;
			case 11: winamp.sendAction(WinampCommands::TimeDialog); break;
			case 12: winamp.sendAction(WinampCommands::Vis); break;
		}
	}
	catch (std::runtime_error) {
		lstrcpy(caller_argument_and_return_command_or_data, "Error: Unable to find Winamp");
	}
	return filled_caller_argument_with_result;
}
#pragma endregion

#pragma region Windows
MIRCTOOLS_API MIRC_FUNCTION(GetActive) {
	HWND h = GetForegroundWindow();
	char buff[901];
	GetWindowText(h, buff, maxCallerArgumentAndReturnCommandOrData);
	lstrcpy(caller_argument_and_return_command_or_data, buff);
	return filled_caller_argument_with_result;
}

MIRCTOOLS_API MIRC_FUNCTION(GetActiveProcess) {
	HWND h = GetForegroundWindow();
	HMODULE hMod;
	DWORD cbNeeded;
	DWORD processId;
	GetWindowThreadProcessId(h, &processId);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
	if (hProcess != NULL) {
		if (EnumProcessModulesEx(hProcess, &hMod, sizeof(hMod), &cbNeeded, LIST_MODULES_ALL)) {
			GetModuleBaseName(hProcess, hMod, caller_argument_and_return_command_or_data, maxCallerArgumentAndReturnCommandOrData);
		}
		else {
			lstrcpy(caller_argument_and_return_command_or_data, "error");
		}
	}
	else {
		lstrcpy(caller_argument_and_return_command_or_data, "unavailable");
	}
	CloseHandle(hProcess);
	return filled_caller_argument_with_result;
}

MIRCTOOLS_API MIRC_FUNCTION(ActiveShowState) {
	HWND h = GetForegroundWindow();
	WINDOWPLACEMENT p;
	p.length = sizeof(WINDOWPLACEMENT);
	if (GetWindowPlacement(h, &p) && p.showCmd == SW_MAXIMIZE) {
		lstrcpy(caller_argument_and_return_command_or_data, "1");
	}
	else {
		lstrcpy(caller_argument_and_return_command_or_data, "0");
	}
	return filled_caller_argument_with_result;
}
#pragma endregion

MIRCTOOLS_API MIRC_FUNCTION(Version) {
	lstrcpy(caller_argument_and_return_command_or_data, version.c_str());
	return filled_caller_argument_with_result;
}

MIRCTOOLS_API MIRC_FUNCTION(Author) {
	lstrcpy(caller_argument_and_return_command_or_data, author.c_str());
	return filled_caller_argument_with_result;
}
