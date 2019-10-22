#pragma once
#include "../h/Onyx32.Gui.internal.h"
#include "../Window/Window.h"
#include "../Controls/Button/Button.h"
#include "../Controls/TextInput/TextInput.h"

namespace Onyx32::Gui
{
	HWND CreateParentWindow(const Win32ParentWindowCreationArgs& args);
	HWND CreateChildWindow(const Onyx32::Gui::Controls::Win32ChildWindowCreationArgs& args);
	void Resize(Onyx32::Gui::Controls::Button* button, const unsigned int width, const unsigned int height);
}