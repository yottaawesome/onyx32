#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "Window.h"
#include "../Button/Button.h"
#include "../WindowClassManager/WindowClassManager.h"
#include "../h/Resource.h"
#include "../h/dllmain.h"
#include "../Win32/Win32Window.h"

namespace Onyx32::Gui
{
	OnWindowActivateChange defaultActivateChange = [](bool isActive) -> void {};

	Window::Window(const WindowClass& wndClass, wstring_view title, UINT width, UINT height, UINT xPos, UINT yPos)
		: _width(width), 
		_height(height),
		_xPos(xPos),
		_yPos(yPos),
		_title(title),
		WndClass(wndClass), 
		_wndHandle(nullptr),
		_activateEvtHandler(defaultActivateChange)
	{ }

	Window::~Window()
	{
		for (auto item : _children)
		{
			delete item.first;
			delete item.second;
		}
		DestroyWindow(_wndHandle);
	}

	void Window::SetTitle(wstring_view title)
	{
		_title = title;
		SetWindowText(_wndHandle, _title.c_str());
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

	void Window::SetOnActivate(OnWindowActivateChange evtHandler)
	{
		_activateEvtHandler = evtHandler;
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
		_children[&control] = new ControlInfo(control);
	}

	int Window::OnActivate(bool isActive)
	{
		_activateEvtHandler(isActive);
		return 0;
	}

	int Window::OnResize(UINT_PTR operation, UINT clientWidth, UINT clientHeight)
	{
		if (operation == SIZE_MINIMIZED)
		{
		}
		else if (operation == SIZE_MAXIMIZED)
		{
		}
		else if (operation == SIZE_RESTORED)
		{
		}
		return 0;
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

			case WM_SIZE:
				return OnResize(wParam, LOWORD(lParam), HIWORD(lParam));

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