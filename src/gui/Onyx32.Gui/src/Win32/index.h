#pragma once
#include "../h/Onyx32.Gui.internal.h"
#include "../Window/Window.h"
#include "../Controls/Button/Button.h"
#include "../Controls/TextInput/TextInput.h"
#include "../../include/Onyx32.Gui.h"
#include <string>

namespace Onyx32::Gui
{
	HWND CreateParentWindow(const Win32ParentWindowCreationArgs& args);
	HWND CreateChildWindow(const Onyx32::Gui::Controls::Win32ChildWindowCreationArgs& args);
	void Resize(Onyx32::Gui::Controls::Button* button, const unsigned int width, const unsigned int height);
	LRESULT CALLBACK WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK DefCtrlProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
	// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getclassinfoexa
	enum WindowClassTypes
	{
		DEFAULT
	};

	WindowClass GetDefaultWindowClass();
}
