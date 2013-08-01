#pragma once

#include "stdafx.h"

struct CommandPair {
	WPARAM w;
	LPARAM l;
};

namespace WinampCommands {
	const WPARAM Play = 40045;
	const WPARAM Next = 40048;
	const WPARAM Last = 40044;
	const WPARAM Pause = 40046;
	const WPARAM Stop = 40047;
	const WPARAM FadeStop = 40147;
	const WPARAM FastForward = 40148;
	const WPARAM Rewind = 40144;
	const WPARAM Kill = 40001;
	const WPARAM Vis = 40192;
	const WPARAM TimeDialog = 40193;
	const WPARAM FileDialog = 40194;
}

namespace WinampInfoPairs {
	const CommandPair TrackCount = {0, 124};
	const CommandPair Kbps = {1, 126};
	const CommandPair TotalTrackTime = {1, 105};
	const CommandPair CurrentPos = {0, 105};
	const CommandPair Khz = {0, 126};
	const CommandPair Mode = {2, 126};
}

class WinampCommunicator {
public:
	// Deliberately no initialization in constructor because Winamp window might change state between calls
	// mIRC also performs its own loading/unloading
	// This makes it unpredictable from the perspective of the DLL
	// e.g. There's no guarantee of re-init every call
	WinampCommunicator() { }
	void init();
	void sendAction(WPARAM);
	long long getAction(const CommandPair &);
	LPCSTR getTitle();
private:
	HWND m_hwnd;
	char m_title[900];
};