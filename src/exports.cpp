#include "stdafx.hpp"
#include "exports.hpp"
#include "mirc_function.hpp"
#include "winamp_communicator.hpp"

using std::string;

const string author_string = "Bui";
const string version_string = "1.0e";
winamp_communicator winamp_instance;

#pragma region Winamp
MIRCTOOLS_API MIRC_FUNCTION(get_winamp) {
	int msg = atoi(caller_argument_and_return_command_or_data);
	try {
		switch (msg) {
			case 1: lstrcpy(caller_argument_and_return_command_or_data, winamp_instance.get_title().c_str()); break;
			case 2: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp_instance.get_action(winamp::info_pairs::track_count)); break;
			case 3: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp_instance.get_action(winamp::info_pairs::kbps)); break;
			case 4: wsprintf(caller_argument_and_return_command_or_data, "%li", winamp_instance.get_action(winamp::info_pairs::total_track_time)); break;
			case 5: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp_instance.get_action(winamp::info_pairs::current_position)); break;
			case 6: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp_instance.get_action(winamp::info_pairs::khz)); break;
			case 7: wsprintf(caller_argument_and_return_command_or_data, "%d", winamp_instance.get_action(winamp::info_pairs::mode)); break;
		}
	}
	catch (std::runtime_error) {
		lstrcpy(caller_argument_and_return_command_or_data, "Error: Unable to find Winamp");
	}
	return filled_caller_argument_with_result;
}

MIRCTOOLS_API MIRC_FUNCTION(send_winamp) {
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
MIRCTOOLS_API MIRC_FUNCTION(get_active) {
	HWND current_window = GetForegroundWindow();
	char buff[901];
	GetWindowText(current_window, buff, max_caller_argument_and_return_command_or_data);
	lstrcpy(caller_argument_and_return_command_or_data, buff);
	return filled_caller_argument_with_result;
}

MIRCTOOLS_API MIRC_FUNCTION(get_active_process) {
	HWND current_window = GetForegroundWindow();
	HMODULE module_handle = nullptr;
	DWORD bytes_needed = 0;
	DWORD current_process_id = 0;
	GetWindowThreadProcessId(current_window, &current_process_id);
	HANDLE process_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, current_process_id);
	if (process_handle != NULL) {
		if (EnumProcessModulesEx(process_handle, &module_handle, sizeof(module_handle), &bytes_needed, LIST_MODULES_ALL)) {
			GetModuleBaseName(process_handle, module_handle, caller_argument_and_return_command_or_data, max_caller_argument_and_return_command_or_data);
		}
		else {
			lstrcpy(caller_argument_and_return_command_or_data, "error");
		}
	}
	else {
		lstrcpy(caller_argument_and_return_command_or_data, "unavailable");
	}
	CloseHandle(process_handle);
	return filled_caller_argument_with_result;
}

MIRCTOOLS_API MIRC_FUNCTION(active_show_state) {
	HWND current_window = GetForegroundWindow();
	WINDOWPLACEMENT p;
	p.length = sizeof(WINDOWPLACEMENT);
	if (GetWindowPlacement(current_window, &p) && p.showCmd == SW_MAXIMIZE) {
		lstrcpy(caller_argument_and_return_command_or_data, "1");
	}
	else {
		lstrcpy(caller_argument_and_return_command_or_data, "0");
	}
	return filled_caller_argument_with_result;
}
#pragma endregion

#pragma region Meta
MIRCTOOLS_API MIRC_FUNCTION(version) {
	lstrcpy(caller_argument_and_return_command_or_data, version_string.c_str());
	return filled_caller_argument_with_result;
}

MIRCTOOLS_API MIRC_FUNCTION(author) {
	lstrcpy(caller_argument_and_return_command_or_data, author_string.c_str());
	return filled_caller_argument_with_result;
}
#pragma endregion