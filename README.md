# Onyx32

## Introduction

Onyx32 is an experimental Win32 framework written in C++ that is currently in development. It's intended to take advantage of newer C++ features and provide a pleasant interface in lieu of the ugly Win32 C calls. This project has roots in older projects of mine started many years ago as a means for me to learn newer C++ features while also exploring the Win32 API. Onyx32 is the latest incarnation of this effort.

## Status

_Major_ changes are planned. The documentation below may no longer be accurate. It's just on standby for the moment as a I focus a bit more on other things. 

## Caveats

It goes without saying that this project is purely for my own fun and education; it's not meant for production-level work. Win32 also has a huge surface area for an API, and time is a limited resource for me, so Onyx32 is woefully incomplete in terms of features. Remember that building and maintaining quality frameworks takes serious work; if you need a GUI framework for production Win32 work, consider [wxWidgets](https://www.wxwidgets.org/).

## Using the library

Development is best done in Visual Studio 2019 Community Edition. Onyx32 targets the latest Windows SDK, so you will need the "Desktop development with C++" workload installed for your Visual Studio. Cross-platform development makes little sense for this project, so you'll need a recent version of Windows. Simply clone this repo and open it in Visual Studio -- you should be able to build immediately if you have met the prerequisites.

### Using Onyx32.Gui.dll

Check `Onyx32.Gui.Tests project` for an example. Essentially, in your project in which you want to use Onyx32.Gui.dll, do the following:

1. Include `Onyx32.Gui.h` and `Onyx32.Gui.Lib.h` (or just the latter, since it includes the former) located in the `Onyx32.Gui/include/` directory.
2. Create an instance of `Onyx32Lib`. This class will automatically load the DLL and unload it on its destruction, so this instance should remain active for the entire scope of your use of `Onyx32` (which will probably be your entire application lifetime).
3. Create the main factory via `Onyx32Lib::GetMainFactory()`.
4. Use the factory to create windows and controls.
5. Add controls to windows.
6. Add event handlers to windows and controls.
7. Create the application loop via `Onyx32Lib::GetApplication()`.
8. Enter the message pump loop `IApplication::MainLoop()`.
9. Bob's your uncle.

Really simple example below. Note that the API demonstrated below will be changing in the near future to a more [fluid style](https://en.wikipedia.org/wiki/Fluent_interface).

```C++
// Update this as per your folder set up
#include "Onyx32.Gui.Lib.h"

using Onyx32::Gui::IWindow;
using Onyx32::Gui::IFactory;
using Onyx32::Gui::IMainLoop;
using Onyx32::Gui::OnyxFree;

// Declare a memory cleanup function
template<typename T>
auto ReleaseOnyxObject = [](T* t) -> void { t->Destroy(); };

int main()
{
    // Load the library -- this example assumes the DLL exists in the same directory as your executable
    Onyx32::Gui::Onyx32Lib lib;
    // Get factory
    std::shared_ptr<IFactory> factory(lib.GetMainFactory(), OnyxFree<IFactory>);
    // Create a default top-level window
    std::shared_ptr<IWindow> window(factory->CreateDefaultWindow(L"This is a test", 500, 500), OnyxFree<IWindow>);
    // Create the message loop
    std::shared_ptr<IMainLoop> app(factory->CreateMainLoop(), OnyxFree<IMainLoop>);
    // Initialize main window
    window->Initialize();
    // If the user closes the Window, exit the main loop
    window->SetWindowEvent(
        WindowEvents::OnClose,
        [](WindowEvents evt, IWindow& window) -> void { PostQuitMessage(0); });
    // Enter the main loop
    int retVal = app->Enter();
    // End -- lib will automatically unload the DLL when it goes out of scope
    return retVal;
}
```

## Future features

The project is undergoing refactoring and I'm slowly adding more features. Features I intend to add support:

* Custom Windows Win32 classes.
* Additional control support.
* Better support for owner drawn windows and controls.
* Networking.
* Drawing.
* DirectX support.
* In future, I may also update the project to move away from VS Community and use VS Code instead.
* And more!

Obviously, this is a bit ambitious (remember I also have a full-time job!), so it will take a while for me to piece everything together.

## Considerations

Note that Win32 imposes restrictions on threads sharing and manipulating windows. Whilst it's possible for threads to [join their thread input state](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-windows-in-threads), certain operations, [such as destroying windows](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow#remarks), can only be performed by the threads that created said windows.

Currently, the Onyx DLL allocates memory, which the client code must `delete`. This is not safe across clients and DLL that are compiled with different versions of the runtime. I do plan to refactor the code to make use of either a fixed allocation function such as `LocalAlloc()` or a wrapper allocation function exported from the DLL.
