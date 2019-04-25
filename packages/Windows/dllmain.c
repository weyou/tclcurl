#include <windows.h>
#include <tcl.h>

#ifndef DECLSPEC_EXPORT
#define DECLSPEC_EXPORT __declspec(dllexport)
#endif // DECLSPEC_EXPORT

 BOOL APIENTRY
 DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
 {
     return TRUE;
 }
