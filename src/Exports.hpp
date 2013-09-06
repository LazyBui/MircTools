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

#include "mirc_function.hpp"

/* Do not forget to modify the .def file associated with the project if modifying code here */

#pragma region Winamp
MIRCTOOLS_API MIRC_FUNCTION(get_winamp);
MIRCTOOLS_API MIRC_FUNCTION(send_winamp);
#pragma endregion

#pragma region Windows
MIRCTOOLS_API MIRC_FUNCTION(get_active);
MIRCTOOLS_API MIRC_FUNCTION(get_active_process);
MIRCTOOLS_API MIRC_FUNCTION(active_show_state);
#pragma endregion

#pragma region Meta
MIRCTOOLS_API MIRC_FUNCTION(version);
MIRCTOOLS_API MIRC_FUNCTION(author);
#pragma endregion