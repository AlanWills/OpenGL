#pragma once

#ifdef BUILDING_DLL
#define DllExport __declspec(dllexport)
#elif TESTING
#define DllExport 
#else
#define DllExport __declspec(dllimport)
#endif
