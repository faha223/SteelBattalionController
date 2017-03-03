/*++

Module Name:

    Dllsup.cpp

Abstract:

    This module contains the implementation of the Driver DLL entry point.

Environment:

   Windows User-Mode Driver Framework (WUDF)

--*/

#include "internal.h"
#include "dllsup.tmh"

//
// This GUID must match the DriverCLSID value for the service binary in the INF.
// For more information see http://msdn.microsoft.com/en-us/library/ff560526(VS.85).aspx
// 76b49eb5-1d2c-45f9-9557-d57da4a05490
//
const CLSID CLSID_Driver =
{0x76b49eb5,0x1d2c,0x45f9,{0x95,0x57,0xd5,0x7d,0xa4,0xa0,0x54,0x90}};

HINSTANCE g_hInstance = NULL;

class CMyDriverModule :
    public CAtlDllModuleT< CMyDriverModule >
{
};

CMyDriverModule _AtlModule;

//
// DLL Entry Point
// 

extern "C"
BOOL
WINAPI
DllMain(
    HINSTANCE hInstance,
    DWORD dwReason,
    LPVOID lpReserved
    )
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        WPP_INIT_TRACING(MYDRIVER_TRACING_ID);
        
        g_hInstance = hInstance;
        DisableThreadLibraryCalls(hInstance);

    } else if (dwReason == DLL_PROCESS_DETACH) {
        WPP_CLEANUP();
    }

    return _AtlModule.DllMain(dwReason, lpReserved);
}


//
// Returns a class factory to create an object of the requested type
// 

STDAPI
DllGetClassObject(
    __in REFCLSID rclsid,
    __in REFIID riid,
    __deref_out LPVOID FAR* ppv
    )
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


