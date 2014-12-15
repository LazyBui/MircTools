#include "stdafx.hpp"
#include "winamp_communicator.hpp"
#include "mirc_function.hpp"

auto winamp_communicator::init() -> HWND {
	HWND window_handle = FindWindow(_T("Winamp v1.x"), NULL);
	if (!window_handle) {
		throw std::runtime_error("Error: Unable to find Winamp");
	}
	return window_handle;
}

auto winamp_communicator::send_action(WPARAM w_param) -> void {
	HWND window_handle = init();
	SendMessage(window_handle, WM_COMMAND, w_param, NULL);
}

auto winamp_communicator::get_action(const winamp_command_pair &pair) -> LRESULT {
	HWND window_handle = init();
	return SendMessage(window_handle, WM_USER, pair.w, pair.l);
}

auto winamp_communicator::get_title() -> std::string {
	HWND window_handle = init();
	char title[max_caller_argument_and_return_command_or_data];
	GetWindowText(window_handle, title, sizeof(title));

	static std::string ending = "- Winamp";
	char *p = title + lstrlen(title) - ending.length();
	while (p >= title) {
		if (!lstrcmpi(p, ending.c_str())) {
			break;
		}
		p--;
	}
	if (p >= title) {
		p--;
	}
	while (p >= title && *p == ' ') {
		p--;
	}

	*++p = 0;

	return std::string{title};
}