// Onyx32.Core.cpp : Defines the exported functions for the DLL.
//

#include "pch.hpp"
#include "framework.hpp"
#include "Onyx32.Core.hpp"


// This is an example of an exported variable
ONYX32CORE_API int nOnyx32Core=0;

// This is an example of an exported function.
ONYX32CORE_API int fnOnyx32Core(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
COnyx32Core::COnyx32Core()
{
    return;
}
