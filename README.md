# Onyx32

## Introduction

Onyx32 is a simple experimental Win32 framework written in C++ that is currently in development. It's intended to take advantage of newer C++ features and provide a pleasant interface in lieu of the ugly Win32 C calls. The project initially started as a means for me to learn newer C++ features while also exploring the Win32 API.

## Status

_In development._

## Using the library

Development is best done in Visual Studio 2019. Onyx32 targets the latest Windows SDK. Simply clone this repo and open it in Visual Studio -- you should be able to build immediately.

### Using Win32.Gui.dll

Check `Onyx32.Gui.Tests project` for an example. Essentially, in your project in which you want to use Win32.Gui.dll, do the following:

1. Include `Onyx32.Gui.h` and `Onyx32.Gui.Lib.h` (or just the latter, since it includes the former) located in the `Onyx32.Gui/include/` directory.
2. Create an instance of `Onyx32Lib`.
3. Create the main factory via `Onyx32Lib::GetMainFactory()`.
4. Create a form builder via `IFormBuilder::GetFormBuilder()`.
5. Use the form builder to create windows and add controls.
6. Create the application loop via `Onyx32Lib::GetApplication()`.
7. Enter the message pump loop `IApplication::MainLoop()`.
8. Bob's your uncle.

Really simple example below.

```C++
// Load library
Onyx32Lib lib;
// Get factory
IFactory* factory = lib.GetMainFactory();
// Get a form builder
IFormBuilder* fmBuilder = factory->GetFormBuilder();
// Create a default top-level window
IWindow* wnd = fmBuilder->CreateDefaultWindow(L"This is a test", 500, 500);
// Create an application
Onyx32::Gui::IApplication* app = factory->GetApplication();
// Enter the main lopp
int retVal = app->MainLoop();
// Clean up -- obviously, use something like std::shared_pointer
delete wnd;
delete app;
delete fmBuilder;
delete factory;
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
* And more!
