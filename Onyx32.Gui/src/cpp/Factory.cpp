#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "../h/Window.h"
#include "../h/WindowClassManager.h"
#include "../h/Resource.h"
#include "../h/dllmain.h"

using namespace Onyx32::Gui;

namespace Onyx32::Gui
{
	IWindow* Factory::TestWindowing()
	{
		return new Window(L"Blah", GetModuleHandle(nullptr), 1000, 1000);
		OutputDebugString(L"DLL thread detached\n");
	}
}
