#include <iostream>
#include <Windows.h>
#include "headers/Onyx32/Async/ISemaphore.hpp"

typedef Onyx32::Core::Async::ISemaphore* (*CreateNamedOnyxSemaphore)(
    const std::wstring& name,
    const bool isInheritable,
    const long initialCount,
    const long maxCount
);

int main(int argc, char** args)
{
    HMODULE lib = LoadLibraryW(L"Onyx32.Core.dll");
    if (lib == nullptr)
        return -1;

    CreateNamedOnyxSemaphore semaphoreFactory = (CreateNamedOnyxSemaphore)GetProcAddress(lib, "CreateNamedOnyxSemaphore");
    if (semaphoreFactory == nullptr)
        return -2;

    Onyx32::Core::Async::ISemaphore* semaphore = semaphoreFactory(L"", false, 10, 10);
    semaphore->Acquire(1000);
    semaphore->Release();
    semaphore->Free();

    FreeLibrary(lib);

    return 0;
}
