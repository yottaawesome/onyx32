#include "../h/stdafx.h"
#include "Renderer.h"
#include "../h/dllmain.h"
#include "../h/StaticFunctions.h"
#include  <Commctrl.h>

namespace Onyx32::Gui
{
	HWND Win32Window::CreateChildWindow(const Win32CreationArgs& args)
	{
		HWND hWnd = CreateWindowEx
		(
			args.ExtendedStyles,
			args.ClassName.c_str(),  // Predefined class; Unicode assumed 
			args.WindowName.c_str(),      // Button text 
			args.Styles,  // Styles 
			args.X,         // x position 
			args.Y,         // y position 
			args.Width,        // Button width
			args.Height,        // Button height
			args.Parent,     // Parent window
			args.MenuOrId,       // Menu or control id
			Dll::GetModule(),// can also use (HINSTANCE)GetWindowLongPtr(args.Parent, GWLP_HINSTANCE),
			(LPVOID)args.Control
		);
		
		// https://docs.microsoft.com/en-us/windows/desktop/api/commctrl/nf-commctrl-setwindowsubclass
		SetWindowSubclass(hWnd, args.SubclassProc, 0, (DWORD_PTR)args.Control);

		return hWnd;
	}

	HWND Win32Window::CreateParentWindow(Window* window)
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

	void Win32Window::Resize(Button* button, const UINT width, const UINT height)
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
}
