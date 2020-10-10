// Onyx32.Async.cpp : Defines the exported functions for the DLL.
//

#include "pch.hpp"
#include "framework.hpp"
#include "Onyx32.Async.hpp"


// This is an example of an exported variable
ONYX32ASYNC_API int nOnyx32Async=0;

// This is an example of an exported function.
ONYX32ASYNC_API int fnOnyx32Async(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
COnyx32Async::COnyx32Async()
{
    return;
}
