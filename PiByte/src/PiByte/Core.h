#pragma once

#ifdef PB_PLATFORM_WINDOWS
#ifdef PIBYTE_EXPORTS
	#define PIBYTE_API __declspec( dllexport )
#else
	#define PIBYTE_API __declspec( dllimport )
#endif // BUILD_DLL

#endif // PLATFORM_WINDOWS
