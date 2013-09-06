#pragma once

#include <Windows.h>

enum mirc_function_return : int {
	halt_processing = 0,
	continue_processing = 1,
	filled_caller_argument_with_command = 2,
	filled_caller_argument_with_result = 3,
};

// Documentation-style parameter args - not very useful at indicating what they actually do
//#define MIRC_FUNCTION(x) int __stdcall x(HWND mWnd, HWND aWnd, char *data, char *parms, BOOL show, BOOL nopause)
#define MIRC_FUNCTION(x) mirc_function_return __stdcall x(HWND mirc_window_handle, HWND calling_context_window_handle, char *caller_argument_and_return_command_or_data, char *return_command_argument, BOOL call_is_quiet, BOOL mirc_in_critical_routine)
