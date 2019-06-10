#include "../h/stdafx.h"
#include "../h/Button.h"
#include "../h/Win32Renderer.h"
#include "../h/dllmain.h"
#include "../h/StaticFunctions.h"
#include  <Commctrl.h>

namespace Onyx32::Gui
{
	HWND Win32Renderer::Render(Window* window)
	{
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-createwindowexw
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-createwindowa
		HWND hWnd = CreateWindow
		(
			window->WndClass.ClassName.c_str(), // class name
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

	HWND Win32Renderer::Render(Window* parent, Button* control, const UINT xPos, const UINT yPos)
	{
		control->SetParent(parent);

		HWND parentHwnd = parent->GetHwnd();
		HWND hwndButton = CreateWindow
		(
			control->GetName().c_str(),  // Predefined class; Unicode assumed 
			control->GetText().c_str(),      // Button text 
			control->GetStyles(),  // Styles 
			xPos,         // x position 
			yPos,         // y position 
			control->GetWidth(),        // Button width
			control->GetHeight(),        // Button height
			parentHwnd,     // Parent window
			(HMENU)control->GetId(),       // No menu.
			(HINSTANCE)GetWindowLongPtr(parentHwnd, GWLP_HINSTANCE),
			control
		);

		// https://docs.microsoft.com/en-us/windows/desktop/api/commctrl/nf-commctrl-setwindowsubclass
		SetWindowSubclass(hwndButton, Static::DefCtrlProc, 0, (DWORD_PTR)control);
		
		return hwndButton;
	}

	HWND Win32Renderer::Render(Window* parent, Input* control, const UINT xPos, const UINT yPos)
	{
		control->SetParent(parent);

		HWND hwndEdit = CreateWindowEx(
			0, 
			L"EDIT",   // predefined class 
			NULL,         // no window title 
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			xPos, 
			yPos, 
			control->GetWidth(),
			control->GetHeight(),   // set size in WM_SIZE message 
			parent->GetHwnd(),         // parent window 
			(HMENU)control->GetId(),   // edit control ID 
			(HINSTANCE)GetWindowLongPtr(parent->GetHwnd(), GWLP_HINSTANCE),
			control);

		return hwndEdit;
	}

	void Win32Renderer::Resize(Button* button, const UINT width, const UINT height)
	{
		MoveWindow(
			button->GetHwnd(),
			0,
			0,
			width,
			height,
			true
		);
	}

	Onyx32::Gui::Win32Renderer::~Win32Renderer()
	{
	}
}
