#pragma once

#ifdef PLATFORM_WINDOWS
#ifdef BUILD_DLL
	#define PIBYTE_API __declspec(dllexport)
#else
	#define PIBYTE_API __declspec(dllimport)
#endif // BUILD_DLL

#endif // PLATFORM_WINDOWS
