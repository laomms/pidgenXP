
#include "pch.h"
HINSTANCE g_hinst = NULL;

BOOL APIENTRY DllMain(
    HANDLE hinst,
    ULONG ulReason,
    LPVOID lpReserved)
{
    if (DLL_PROCESS_ATTACH == ulReason)
    {
        g_hinst = (HINSTANCE)hinst;
    }

    return TRUE;
}

