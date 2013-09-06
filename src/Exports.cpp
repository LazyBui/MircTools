#include "stdafx.h"
#include "Exports.h"
#include "MircFunction.h"
#include "WinampCommunicator.h"

using std::string;

const string author = "Bui";
const string version = "1.0d";
const int maxCallerArgumentAndReturnCommandOrData = 900;
WinampCommunicator winamp;

#pragma region Winamp
MIRCTOOLS_API MIRCFUNCTION(GetWinamp) {
	int msg = atoi(callerArgumentAndReturnCommandOrData);
	try {
		switch (msg) {
			case 1: lstrcpy(callerArgumentAndReturnCommandOrData, winamp.getTitle()); break;
			case 2: wsprintf(callerArgumentAndReturnCommandOrData, "%d", winamp.getAction(WinampInfoPairs::TrackCount)); break;
			case 3: wsprintf(callerArgumentAndReturnCommandOrData, "%d", winamp.getAction(WinampInfoPairs::Kbps)); break;
			case 4: wsprintf(callerArgumentAndReturnCommandOrData, "%li", winamp.getAction(WinampInfoPairs::TotalTrackTime)); break;
			case 5: wsprintf(callerArgumentAndReturnCommandOrData, "%d", winamp.getAction(WinampInfoPairs::CurrentPos)); break;
			case 6: wsprintf(callerArgumentAndReturnCommandOrData, "%d", winamp.getAction(WinampInfoPairs::Khz)); break;
			case 7: wsprintf(callerArgumentAndReturnCommandOrData, "%d", winamp.getAction(WinampInfoPairs::Mode)); break;
		}
	}
	catch (std::runtime_error) {
		lstrcpy(callerArgumentAndReturnCommandOrData, "Error: Unable to find Winamp");
	}
	return FilledCallerArgumentWithResult;
}

MIRCTOOLS_API MIRCFUNCTION(SendWinamp) {
	int msg = atoi(callerArgumentAndReturnCommandOrData);
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
		lstrcpy(callerArgumentAndReturnCommandOrData, "Error: Unable to find Winamp");
	}
	return FilledCallerArgumentWithResult;
}
#pragma endregion

#pragma region Windows
MIRCTOOLS_API MIRCFUNCTION(GetActive) {
	HWND h = GetForegroundWindow();
	char buff[901];
	GetWindowText(h, buff, maxCallerArgumentAndReturnCommandOrData);
	lstrcpy(callerArgumentAndReturnCommandOrData, buff);
	return FilledCallerArgumentWithResult;
}

MIRCTOOLS_API MIRCFUNCTION(GetActiveProcess) {
	HWND h = GetForegroundWindow();
	HMODULE hMod;
	DWORD cbNeeded;
	DWORD processId;
	GetWindowThreadProcessId(h, &processId);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
	if (hProcess != NULL) {
		if (EnumProcessModulesEx(hProcess, &hMod, sizeof(hMod), &cbNeeded, LIST_MODULES_ALL)) {
			GetModuleBaseName(hProcess, hMod, callerArgumentAndReturnCommandOrData, maxCallerArgumentAndReturnCommandOrData);
		}
		else {
			lstrcpy(callerArgumentAndReturnCommandOrData, "error");
		}
	}
	else {
		lstrcpy(callerArgumentAndReturnCommandOrData, "unavailable");
	}
	CloseHandle(hProcess);
	return FilledCallerArgumentWithResult;
}

MIRCTOOLS_API MIRCFUNCTION(ActiveShowState) {
	HWND h = GetForegroundWindow();
	WINDOWPLACEMENT p;
	p.length = sizeof(WINDOWPLACEMENT);
	if (GetWindowPlacement(h, &p) && p.showCmd == SW_MAXIMIZE) {
		lstrcpy(callerArgumentAndReturnCommandOrData, "1");
	}
	else {
		lstrcpy(callerArgumentAndReturnCommandOrData, "0");
	}
	return FilledCallerArgumentWithResult;
}
#pragma endregion

MIRCTOOLS_API MIRCFUNCTION(Version) {
	lstrcpy(callerArgumentAndReturnCommandOrData, version.c_str());
	return FilledCallerArgumentWithResult;
}

MIRCTOOLS_API MIRCFUNCTION(Author) {
	lstrcpy(callerArgumentAndReturnCommandOrData, author.c_str());
	return FilledCallerArgumentWithResult;
}
