#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "Window.h"
#include "../Button/Button.h"
#include "../WindowClassManager/WindowClassManager.h"
#include "../h/Resource.h"
#include "../h/dllmain.h"
#include "../Win32/Win32Window.h"
#include <map>

namespace Onyx32::Gui
{
	OnWindowActivateChange defaultActivateChange = [](IWindow& window, bool isActive) -> void {};
	OnWindowResized defaultOnResized = [](IWindow& window) -> void {};

	Window::Window(const WindowClass& wndClass, wstring_view title, UINT width, UINT height, UINT xPos, UINT yPos)
		: _width(width), 
		_height(height),
		_xPos(xPos),
		_yPos(yPos),
		_title(title),
		WndClass(wndClass), 
		_wndHandle(nullptr),
		_activateEvtHandler(defaultActivateChange),
		_onResized(defaultOnResized)
	{ }

	Window::~Window()
	{
		for (auto const i : _children)
			delete i;
		DestroyWindow(_wndHandle);
	}

	void Window::SetTitle(wstring_view title)
	{
		if(SetWindowText(_wndHandle, wstring(_title).c_str()))
			_title = title;
	}

	const std::wstring& Window::GetTitle()
	{
		return _title;
	}

	UINT Window::GetWidth()
	{
		return _width;
	}

	UINT Window::GetHeight()
	{
		return _height;
	}

	void Window::SetHwnd(HWND hWnd)
	{
		_wndHandle = hWnd;
	}

	HWND Window::GetHwnd()
	{
		return _wndHandle;
	}

	void Window::Initialize()
	{
		Win32ParentWindowCreationArgs args(
			0,
			_title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			_width,
			_height,
			nullptr,
			nullptr,
			this,
			WndClass.WndClass
		);
		_wndHandle = Win32Window::CreateParentWindow(args);
		if (!_wndHandle)
			return;

		// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548%28v=vs.85%29.aspx
		ShowWindow(_wndHandle, SW_SHOWDEFAULT);
		UpdateWindow(_wndHandle);
	}

	void Window::Resize(const UINT width, const UINT height)
	{
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-movewindow
		// See also: https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowpos
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-adjustwindowrectex
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-begindeferwindowpos
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-enddeferwindowpos
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-deferwindowpos
		if (MoveWindow(_wndHandle, _xPos, _yPos, width, height, true))
		{
			_width = width;
			_height = height;
		}
	}

	void Window::AddControl(IControl& control)
	{
		control.Initialize(this);
		_children.push_back(&control);
	}

	LRESULT Window::Process(UINT message, WPARAM wParam, LPARAM lParam)
	{
		int wmId, wmEvent;
		PAINTSTRUCT ps;
		HDC hdc;

		switch (message)
		{
			case WM_COMMAND:
			{
				wmId = LOWORD(wParam);
				wmEvent = HIWORD(wParam);
				// Parse the menu selections:
				switch (wmId)
				{
					case IDM_ABOUT:
						//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
						break;

					case IDM_EXIT:
						DestroyWindow(_wndHandle);
						break;

					default:
						return DefWindowProc(_wndHandle, message, wParam, lParam);
				}
				break;
			}

			// Continually sent while the window is being resized. wParam is always SIZE_RESTORED
			// if the user is dragging the resize bars.
			case WM_SIZE:
				//LOWORD(lParam) = client width
				//HIWORD(lParam) = client height
				return OnResizing((WindowResizeState)wParam);

			// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
			case WM_ENTERSIZEMOVE:
				return OnBeginUserResize();

			// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
			case WM_EXITSIZEMOVE:
				return OnEndUserResize();

			case WM_ACTIVATE:
				return OnActivate(LOWORD(wParam) != WA_INACTIVE);

			case WM_PAINT:
			{
				hdc = BeginPaint(_wndHandle, &ps);
				// TODO: Add any drawing code here...
				EndPaint(_wndHandle, &ps);
				break;
			}

			case WM_DESTROY:
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProc(_wndHandle, message, wParam, lParam);
		}
		return 0;
	}
}