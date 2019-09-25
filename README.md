# Onyx32

## Introduction

Onyx32 is a simple experimental Win32 framework written in C++ that is currently in development. It's intended to take advantage of newer C++ features and provide a pleasant interface in lieu of the ugly Win32 C calls. The project initially started as a means for me to learn newer C++ features while also exploring the Win32 API.

## Status

_In development._ The framework is continually being improved and refactored with time, so the API may not be stable.

## Using the library

Development is best done in Visual Studio 2019. Onyx32 targets the latest Windows SDK. Simply clone this repo and open it in Visual Studio -- you should be able to build immediately.

### Using Onyx32.Gui.dll

Check `Onyx32.Gui.Tests project` for an example. Essentially, in your project in which you want to use Onyx32.Gui.dll, do the following:

1. Include `Onyx32.Gui.h` and `Onyx32.Gui.Lib.h` (or just the latter, since it includes the former) located in the `Onyx32.Gui/include/` directory.
2. Create an instance of `Onyx32Lib` -- this library will automatically load the DLL.
3. Create the main factory via `Onyx32Lib::GetMainFactory()`.
4. Use the factory to create windows and controls.
5. Add controls to windows.
6. Add event handlers to windows and controls.
7. Create the application loop via `Onyx32Lib::GetApplication()`.
8. Enter the message pump loop `IApplication::MainLoop()`.
9. Bob's your uncle.

Really simple example below.

```C++
// Update this as per your folder set up
#include "Onyx32.Gui.Lib.h"

using Onyx32::Gui::IWindow;
using Onyx32::Gui::IFactory;
using Onyx32::Gui::IApplication;

// Load the library -- this example assumes the DLL exists in the same directory as your executable
Onyx32::Gui::Onyx32Lib lib;
// Get factory
std::shared_ptr<IFactory> factory(lib.GetMainFactory());
// Create a default top-level window
std::shared_ptr<IWindow> window(factory->CreateDefaultWindow(L"This is a test", 500, 500));
// Create an application
std::shared_ptr<IApplication> app(factory->GetApplication());
// Initialize main window
window->Initialize();
// If the user closes the Window, exit the main loop
window->SetWindowEvent(
    WindowEvents::OnClose,
    [](WindowEvents evt, IWindow& window) -> void { PostQuitMessage(0); });
// Enter the main lopp
int retVal = app->MainLoop();
// End -- lib will automatically unload the DLL when it goes out of scope
return retVal;
```

## Future features

The project is undergoing refactoring and I'm slowly adding more features. Features I intend to add support:

* Custom Windows Win32 classes.
* Additional control support.
* Better support for owner drawn windows and controls.
* Networking.
* Drawing.
* DirectX support.
* And more!

Obviously, this is a bit ambitious (remember I also have a full-time job!), so it will take a while for me to piece everything together.

## Considerations

Note that Win32 imposes restrictions on threads sharing and manipulating windows. Whilst it's possible for threads to [join their thread input state](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-windows-in-threads), certain operations, [such as destroying windows](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow#remarks), can only be performed by the threads that created said windows.
