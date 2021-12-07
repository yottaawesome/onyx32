// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"

// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain
BOOL APIENTRY DllMain( 
    HMODULE hModule,
    DWORD  reasonForCall,
    void* lpReserved
)
{
    switch (reasonForCall)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return true;
}

