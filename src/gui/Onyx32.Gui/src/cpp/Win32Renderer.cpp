#include "../h/stdafx.h"
#include "../h/Button.h"
#include "../h/Win32Renderer.h"
#include "../h/dllmain.h"
#include "../h/StaticFunctions.h"
#include  <Commctrl.h>

namespace Onyx32::Gui
{
	HWND Onyx32::Gui::Win32Renderer::Render(Window* window)
	{
		HWND hWnd = CreateWindow
		(
			window->GetWndClass().ClassName.c_str(), // class name
			window->GetTitle().c_str(), // window title
			WS_OVERLAPPEDWINDOW, // window styles
			CW_USEDEFAULT, // initial horizontal x position
			0,  // initial horizontal y position
			window->GetWidth(),  // window width
			window->GetHeight(), // window height
			NULL, // parent HWND
			NULL, // HWND menu/child
			Dll::GetModule(),//hInstance, // instance of the module
			window // additional data
		);

		if (!hWnd)
			return nullptr;

		// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548%28v=vs.85%29.aspx
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		return hWnd;
	}

	HWND Onyx32::Gui::Win32Renderer::Render(Window* parent, Button* button, const UINT xPos, const UINT yPos)
	{
		button->SetParent(parent);

		HWND parentHwnd = parent->GetHwnd();
		HWND hwndButton = CreateWindow
		(
			L"BUTTON",  // Predefined class; Unicode assumed 
			button->GetText().c_str(),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			xPos,         // x position 
			yPos,         // y position 
			button->GetWidth(),        // Button width
			button->GetHeight(),        // Button height
			parentHwnd,     // Parent window
			(HMENU)button->GetId(),       // No menu.
			(HINSTANCE)GetWindowLongPtr(parentHwnd, GWLP_HINSTANCE),
			button
		);

		SetWindowSubclass(hwndButton, Static::DefCtrlProc, 0, (DWORD_PTR)button);
		
		return hwndButton;
	}

	Onyx32::Gui::Win32Renderer::~Win32Renderer()
	{
	}
}
