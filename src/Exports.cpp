#include "stdafx.hpp"
#include "Exports.hpp"
#include "MircFunction.hpp"
#include "WinampCommunicator.hpp"

using std::string;

const string author = "Bui";
const string version = "1.0d";
const int maxCallerArgumentAndReturnCommandOrData = 900;
winamp_communicator winamp_instance;

#pragma region Winamp
MIRCTOOLS_API MIRC_FUNCTION(GetWinamp) {
	int msg = atoi(caller_argument_and_return_command_or_data);
	try {
		switch (msg) {
			case 1: lstrcpy(caller_argument_and_return_command_or_data, winamp_instance.get_title()); break;
			case 2: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp_instance.get_action(winamp::info_pairs::TrackCount)); break;
			case 3: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp_instance.get_action(winamp::info_pairs::Kbps)); break;
			case 4: wsprintf(caller_argument_and_return_command_or_data, "%li", winamp_instance.get_action(winamp::info_pairs::TotalTrackTime)); break;
			case 5: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp_instance.get_action(winamp::info_pairs::CurrentPos)); break;
			case 6: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp_instance.get_action(winamp::info_pairs::Khz)); break;
			case 7: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp_instance.get_action(winamp::info_pairs::Mode)); break;
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
			case 1: winamp_instance.send_action(winamp::commands::play); break;
			case 2: winamp_instance.send_action(winamp::commands::next); break;
			case 3: winamp_instance.send_action(winamp::commands::last); break;
			case 4: winamp_instance.send_action(winamp::commands::pause); break;
			case 5: winamp_instance.send_action(winamp::commands::stop); break;
			case 6: winamp_instance.send_action(winamp::commands::fade_stop); break;
			case 7: winamp_instance.send_action(winamp::commands::fast_forward); break;
			case 8: winamp_instance.send_action(winamp::commands::rewind); break;
			case 9: winamp_instance.send_action(winamp::commands::kill); break;
			case 10: winamp_instance.send_action(winamp::commands::file_dialog); break;
			case 11: winamp_instance.send_action(winamp::commands::time_dialog); break;
			case 12: winamp_instance.send_action(winamp::commands::vis); break;
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
