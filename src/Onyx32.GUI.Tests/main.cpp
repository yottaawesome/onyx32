#include <iostream>
#include <stdexcept>
#include <format>
#include <Windows.h>

import onyx32.gui;

int main(int argc, char* args[])
{
    // Works as long as the lib is attached
    Onyx32::GUI::ICoreFactory* test = Onyx32::GUI::GetCoreFactory();
    // Can also do this
    HMODULE libHandle = GetModuleHandleW(L"Onyx32.GUI.dll");
    const auto GetCoreFactory = reinterpret_cast<Onyx32::GUI::CoreFactorySignature>(GetProcAddress(libHandle, "GetCoreFactory"));
    if (!GetCoreFactory)
        throw std::runtime_error(std::format("{}: could not reslve GetCoreFactory()", __FUNCSIG__));

    std::cout << std::format("Hello World! {}\n", test->Blah());
    return 0;
}

