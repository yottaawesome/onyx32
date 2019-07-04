#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "Window.h"
#include "../Button/Button.h"
#include "../WindowClassManager/WindowClassManager.h"
#include "../h/Resource.h"
#include "../h/dllmain.h"
#include "../Win32/Win32Window.h"
#include <map>

using std::wstring;
using std::wstring_view;

namespace Onyx32::Gui
{
	const int DefaultWindowStyles = WS_OVERLAPPEDWINDOW;

	Window::Window(const WindowClass& wndClass, wstring_view title, const int customStyle, UINT width, UINT height, UINT xPos, UINT yPos)
		: _width(width),
		_height(height),
		_xPos(xPos),
		_yPos(yPos),
		_title(title),
		_windowClass(wndClass),
		_wndHandle(nullptr),
		_styles(customStyle),
		_displayState(WindowDisplayState::Restored),
		_isVisible(false),
		_isActive(false)
	{ }

	Window::Window(const WindowClass& wndClass, wstring_view title, UINT width, UINT height, UINT xPos, UINT yPos)
		: _width(width), 
		_height(height),
		_xPos(xPos),
		_yPos(yPos),
		_title(title),
		_windowClass(wndClass),
		_wndHandle(nullptr),
		_styles(DefaultWindowStyles),
		_displayState(WindowDisplayState::Restored),
		_isVisible(false),
		_isActive(false)
	{ }

	Window::~Window()
	{
		//for (auto& key : _children)
		//	delete key.second;
		DestroyWindow(_wndHandle);
	}

	void Window::SetTitle(wstring_view title)
	{
		if(SetWindowText(_wndHandle, wstring(_title).c_str()))
			_title = title;
	}

	void Window::Move(const UINT xPos, const UINT yPos)
	{
		if (MoveWindow(_wndHandle, xPos, yPos, _width, _height, true))
		{
			_xPos = xPos;
			_yPos = yPos;
		}
	}

	void Window::SetVisibility(const bool isVisible)
	{
		int value = isVisible ? SW_SHOW : SW_HIDE;
		_isActive = isVisible;
		_isVisible = isVisible;
		ShowWindow(_wndHandle, value);
	}

	void Window::SetDisplayState(WindowDisplayState state)
	{
		switch (state)
		{
			case Onyx32::Gui::Restored:
				_isVisible = true;
				ShowWindow(_wndHandle, SW_RESTORE);
				_displayState = WindowDisplayState::Restored;
				_isActive = true;
				break;
			case Onyx32::Gui::Minimized:
				_isVisible = false;
				ShowWindow(_wndHandle, SW_MINIMIZE);
				_displayState = WindowDisplayState::Minimized;
				_isActive = false;
				break;
			case Onyx32::Gui::Maximized:
				_isVisible = true;
				ShowWindow(_wndHandle, SW_MAXIMIZE);
				_displayState = WindowDisplayState::Maximized;
				_isActive = true;
				break;
			default:
				break;
		}
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

	int Window::GetStyles()
	{
		return _styles;
	}

	HWND Window::GetHwnd()
	{
		return _wndHandle;
	}

	WindowDisplayState Window::GetDisplayState()
	{
		return _displayState;
	}

	void Window::SetWindowEvent(WindowEvents evt, OnWindowEvent&& evtHandler)
	{
		_eventHandlers[evt] = std::move(evtHandler);
	}

	void Window::Initialize()
	{
		Win32ParentWindowCreationArgs args(
			0,
			_title,
			_styles,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			_width,
			_height,
			nullptr,
			nullptr,
			this,
			_windowClass.WndClass
		);
		_wndHandle = Win32Window::CreateParentWindow(args);
		if (!_wndHandle)
			return;

		// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548%28v=vs.85%29.aspx
		ShowWindow(_wndHandle, SW_SHOWDEFAULT);
		_displayState = WindowDisplayState::Restored;
		_isActive = true;
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

	void Window::AddControl(IControl* control)
	{
		control->Initialize(this);
		_children[control] = std::shared_ptr<IControl>(control);
	}

	void Window::DestroyControl(IControl* control)
	{
		if (_children.count(control))
			_children.erase(control);
	}
	
	bool Window::IsActive()
	{
		return _isActive;
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
			{
				//LOWORD(lParam) = client width
				//HIWORD(lParam) = client height
				_displayState = (WindowDisplayState)wParam;
				return 0;
			}

			// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
			case WM_ENTERSIZEMOVE:
			{
				return 0;
			}

			// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
			case WM_EXITSIZEMOVE:
			{
				WindowEvents evt = WindowEvents::OnResized;
				if (_eventHandlers.count(evt))
					_eventHandlers[evt](evt, *this);
				return 0;
			}

			// Window has gained or lost focus
			case WM_ACTIVATE:
			{
				_isActive = LOWORD(wParam) != WA_INACTIVE;
				WindowEvents evt = WindowEvents::OnActivateChange;
				if (_eventHandlers.count(evt))
					_eventHandlers[evt](evt, *this);
				return 0;
			}

			// Close box on the window was clicked
			case WM_DESTROY:
			{
				WindowEvents evt = WindowEvents::OnClose;
				if (_eventHandlers.count(evt))
					_eventHandlers[evt](evt, *this);
				return 0;
			}

			case WM_PAINT:
			{
				hdc = BeginPaint(_wndHandle, &ps);
				// TODO: Add any drawing code here...
				EndPaint(_wndHandle, &ps);
				break;
			}

			default:
				return DefWindowProc(_wndHandle, message, wParam, lParam);
		}
		return 0;
	}
}