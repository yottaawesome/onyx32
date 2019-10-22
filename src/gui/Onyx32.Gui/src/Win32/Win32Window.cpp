#include "../h/stdafx.h"
#include "Win32Window.h"
#include "../h/dllmain.h"
#include "../h/StaticFunctions.h"
#include  <Commctrl.h>

namespace Onyx32::Gui
{
	HWND CreateChildWindow(const Win32ChildWindowCreationArgs& args)
	{
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-createwindowexw
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-createwindowa
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

	HWND CreateParentWindow(const Win32ParentWindowCreationArgs& args)
	{
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-createwindowexw
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-createwindowa
		HWND hWnd = CreateWindowEx
		(
			args.ExtendedStyles,
			args.WndClass.lpszClassName, // class name
			args.WindowName.c_str(), // window title
			args.Styles, // window styles
			args.X, // initial horizontal x position
			args.Y,  // initial horizontal y position
			args.Width,  // window width
			args.Height, // window height
			args.ParentOrOwner, // parent HWND
			args.Menu, // HWND menu/child
			Dll::GetModule(),//hInstance, // instance of the module
			(LPVOID)args.Window // additional data
		);

		return hWnd;
	}

	void Resize(Button* button, const unsigned int width, const unsigned int height)
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
