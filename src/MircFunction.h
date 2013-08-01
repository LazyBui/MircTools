#pragma once

#include <Windows.h>

// Documentation-style parameter args - not very useful at indicating what they actually do
//#define MIRCFUNCTION(x) int __stdcall x(HWND mWnd, HWND aWnd, char *data, char *parms, BOOL show, BOOL nopause)
#define MIRCFUNCTION(x) MircFunctionReturn __stdcall x(HWND mircWindowHandle, HWND callingContextWindowHandle, char *callerArgumentAndReturnCommandOrData, char *returnCommandArgument, BOOL callIsQuiet, BOOL mircInCriticalRoutine)

enum MircFunctionReturn : int {
	HaltProcessing = 0,
	ContinueProcessing = 1,
	FilledCallerArgumentWithCommand = 2,
	FilledCallerArgumentWithResult = 3,
};