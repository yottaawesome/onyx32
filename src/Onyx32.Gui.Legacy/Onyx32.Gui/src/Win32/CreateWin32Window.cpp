#include "stdafx.h"
#include "index.internal.hpp"
#include "../dllmain.hpp"
#include "../Win32/index.hpp"

namespace Onyx32::Gui::Win32
{
	HWND CreateWin32Window(const ParentWindowDescriptor& args)
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
			DLL::GetModule(),//hInstance, // instance of the module
			(void*)args.Window // additional data
		);

		return hWnd;
	}

	HWND CreateWin32Window(const ChildWindowDescriptor& args)
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
			DLL::GetModule(),// can also use (HINSTANCE)GetWindowLongPtr(args.Parent, GWLP_HINSTANCE),
			(LPVOID)args.Control
		);
		
		// https://docs.microsoft.com/en-us/windows/desktop/api/commctrl/nf-commctrl-setwindowsubclass
		SetWindowSubclass(hWnd, args.SubclassProc, 0, (DWORD_PTR)args.Control);

		return hWnd;
	}
}
