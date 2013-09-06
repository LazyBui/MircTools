#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MIRCTOOLS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MIRCTOOLS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#include "stdafx.hpp"

#ifdef MIRCTOOLS_EXPORTS
#	define MIRCTOOLS_API __declspec(dllexport)
#else
#	define MIRCTOOLS_API __declspec(dllimport)
#endif

#include "MircFunction.hpp"

/* Do not forget to modify the .def file associated with the project if modifying code here */

#pragma region Winamp
MIRCTOOLS_API MIRC_FUNCTION(GetWinamp);
MIRCTOOLS_API MIRC_FUNCTION(SendWinamp);
#pragma endregion

#pragma region Windows
MIRCTOOLS_API MIRC_FUNCTION(GetActive);
MIRCTOOLS_API MIRC_FUNCTION(GetActiveProcess);
MIRCTOOLS_API MIRC_FUNCTION(ActiveShowState);
#pragma endregion

MIRCTOOLS_API MIRC_FUNCTION(Version);
MIRCTOOLS_API MIRC_FUNCTION(Author);