#pragma once

#include "stdafx.hpp"

struct winamp_command_pair {
	WPARAM w;
	LPARAM l;
};

namespace winamp {
	namespace commands {
		const WPARAM play = 40045;
		const WPARAM next = 40048;
		const WPARAM last = 40044;
		const WPARAM pause = 40046;
		const WPARAM stop = 40047;
		const WPARAM fade_stop = 40147;
		const WPARAM fast_forward = 40148;
		const WPARAM rewind = 40144;
		const WPARAM kill = 40001;
		const WPARAM vis = 40192;
		const WPARAM time_dialog = 40193;
		const WPARAM file_dialog = 40194;
	}

	namespace info_pairs {
		const winamp_command_pair track_count = {0, 124};
		const winamp_command_pair kbps = {1, 126};
		const winamp_command_pair total_track_time = {1, 105};
		const winamp_command_pair current_position = {0, 105};
		const winamp_command_pair khz = {0, 126};
		const winamp_command_pair mode = {2, 126};
	}
}

class winamp_communicator {
public:
	// Deliberately no initialization in constructor because Winamp window might change state between calls
	// mIRC also performs its own loading/unloading
	// This makes it unpredictable from the perspective of the DLL
	// e.g. There's no guarantee of re-init every call
	winamp_communicator() = default;
	auto send_action(WPARAM) -> void;
	auto get_action(const winamp_command_pair &) -> long long;
	auto get_title() -> LPCSTR;
private:
	auto init() -> void;

	HWND m_hwnd = nullptr;
	char m_title[900];
};