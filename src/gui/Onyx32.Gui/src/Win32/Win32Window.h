#pragma once
#include "../h/Onyx32.Gui.internal.h"
#include "../Window/Window.h"
#include "../Controls/Button/Button.h"
#include "../Controls/TextInput/TextInput.h"

namespace Onyx32::Gui
{
	HWND CreateParentWindow(const Win32ParentWindowCreationArgs& args);
	HWND CreateChildWindow(const Win32ChildWindowCreationArgs& args);
	void Resize(Button* button, const unsigned int width, const unsigned int height);
}