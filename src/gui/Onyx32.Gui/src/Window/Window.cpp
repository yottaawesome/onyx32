#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "Window.h"
#include "../Controls/Button/Button.h"
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

	Window::Window(const WindowClass& wndClass, wstring_view title, const int customStyle, const unsigned int width, const unsigned int height, const unsigned int xPos, const unsigned int yPos)
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
		_isActive(false),
		_windowState(WindowState::Uninitialized),
		_isBeingResized(false),
		_hasFocus(false),
		_isEnabled(false)
	{ }

	Window::Window(const WindowClass& wndClass, wstring_view title, const unsigned int width, const unsigned int height, const unsigned int xPos, const unsigned int yPos)
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
		_isActive(false),
		_windowState(WindowState::Uninitialized),
		_isBeingResized(false),
		_hasFocus(false),
		_isEnabled(false)
	{ }

	Window::~Window()
	{
		//for (auto& key : _children)
		//	delete key.second;
		if (_windowState == WindowState::Initialized && DestroyWindow(_wndHandle))
			_windowState = WindowState::Destroyed;
	}

	const std::wstring& Window::GetTitle() const { return _title; }
	int Window::GetStyles() const { return _styles; }
	HWND Window::GetHwnd() const { return _wndHandle; }
	WindowDisplayState Window::GetDisplayState() const { return _displayState; }
	bool Window::IsActive() const { return _isActive; }
	bool Window::HasFocus() const { return _hasFocus; }
	bool Window::IsVisible() const { return _isVisible; }
	bool Window::IsEnabled() const { return _isEnabled; }

	void Window::GetDimensions(Dimensions& dimensions) const
	{
		dimensions.xPos = _xPos;
		dimensions.yPos = _yPos;
		dimensions.width = _width;
		dimensions.height = _height;
	}

	void Window::SetEnabled(const bool isEnabled)
	{
		if (_windowState == WindowState::Initialized)
		{
			_isEnabled = isEnabled;
			EnableWindow(_wndHandle, isEnabled);
		}
	}

	void Window::SetTitle(wstring_view title)
	{
		if(_windowState == WindowState::Initialized && SetWindowText(_wndHandle, wstring(_title).c_str()))
			_title = title;
	}

	void Window::Move(const unsigned int xPos, const unsigned int yPos)
	{
		if (_windowState == WindowState::Initialized && MoveWindow(_wndHandle, xPos, yPos, _width, _height, true))
		{
			_xPos = xPos;
			_yPos = yPos;
		}
	}

	void Window::SetVisibility(const bool isVisible)
	{
		if (_windowState == WindowState::Initialized)
		{
			int value = isVisible ? SW_SHOW : SW_HIDE;
			ShowWindow(_wndHandle, value);
		}
	}

	void Window::SetDisplayState(const WindowDisplayState state)
	{
		if (_windowState == WindowState::Initialized)
		{
			switch (state)
			{
				case WindowDisplayState::Restored:
					ShowWindow(_wndHandle, SW_RESTORE);
					break;
				case WindowDisplayState::Minimized:
					ShowWindow(_wndHandle, SW_MINIMIZE);
					break;
				case WindowDisplayState::Maximized:
					ShowWindow(_wndHandle, SW_MAXIMIZE);
					break;
				default:
					break;
			}
		}
	}

	void Window::SetHwnd(HWND hWnd)
	{
		_wndHandle = hWnd;
	}

	void Window::SetEvent(WindowEvents evt, OnWindowEvent&& evtHandler)
	{
		_eventHandlers[evt] = std::move(evtHandler);
	}

	void Window::Initialize()
	{
		if (_windowState == WindowState::Uninitialized)
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
			_wndHandle = CreateParentWindow(args);
			if (_wndHandle)
			{
				// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548%28v=vs.85%29.aspx
				ShowWindow(_wndHandle, SW_SHOWDEFAULT);
				UpdateWindow(_wndHandle);
				_displayState = WindowDisplayState::Restored;
				_isActive = true;
				_windowState = WindowState::Initialized;
			}
			else
			{
				_windowState = WindowState::Error;
			}
		}
	}

	void Window::Resize(const unsigned int width, const unsigned int height)
	{
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-movewindow
		// See also: https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowpos
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-adjustwindowrectex
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-begindeferwindowpos
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-enddeferwindowpos
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-deferwindowpos
		if (_windowState == WindowState::Initialized && MoveWindow(_wndHandle, _xPos, _yPos, width, height, true))
		{
			_width = width;
			_height = height;
		}
	}

	void Window::AddControl(Onyx32::Gui::Controls::IControl* const control)
	{
		if (_windowState == WindowState::Initialized)
		{
			control->Initialize();
			_children[control] = std::shared_ptr<Onyx32::Gui::Controls::IControl>(control);
		}
	}

	void Window::DestroyControl(Onyx32::Gui::Controls::IControl* const control)
	{
		if (_windowState == WindowState::Initialized && _children.count(control))
			_children.erase(control);
	}

	void Window::InvokeEvent(const WindowEvents evt)
	{
		if (_windowState == WindowState::Initialized && _eventHandlers.count(evt))
			_eventHandlers[evt](evt, *this);
	}

	void Window::RequestFocus()
	{
		if(_windowState == WindowState::Initialized)
			SetFocus(_wndHandle);
	}

	LRESULT Window::Process(unsigned int message, WPARAM wParam, LPARAM lParam)
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

			// Sent to a window when the window is about to be hidden or shown.
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-showwindow
			case WM_SHOWWINDOW:
			{
				_isVisible = wParam;
				InvokeEvent(WindowEvents::OnVisibilityChanged);
				return 0;
			}

			// Continually sent while the window is being resized. wParam is always SIZE_RESTORED
			// if the user is dragging the resize bars.
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-size
			case WM_SIZE:
			{
				//LOWORD(lParam) = client width
				//HIWORD(lParam) = client height
				_displayState = (WindowDisplayState)wParam;
				if(_isBeingResized)
					InvokeEvent(WindowEvents::OnResizing);
				else
					InvokeEvent(WindowEvents::OnDisplayStateChanged);
				return 0;
			}

			// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-entersizemove
			case WM_ENTERSIZEMOVE:
			{
				_isBeingResized = true;
				InvokeEvent(WindowEvents::OnBeginResize);
				return 0;
			}

			// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-exitsizemove
			case WM_EXITSIZEMOVE:
			{
				RECT r;
				GetClientRect(_wndHandle, &r);
				_width = r.right;
				_height = r.bottom;
				_isBeingResized = false;
				InvokeEvent(WindowEvents::OnResized);
				return 0;
			}

			// Window has been activated or deactivated for keyboard input
			// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-activate
			case WM_ACTIVATE:
			{
				_isActive = LOWORD(wParam) != WA_INACTIVE && HIWORD(wParam) == 0;
				//_displayState = HIWORD(wParam) > 0 ? WindowDisplayState::Minimized : WindowDisplayState::Restored;
				InvokeEvent(WindowEvents::OnActivateChange);
				return 0;
			}

			// Window has gained focus
			// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-setfocus
			case WM_SETFOCUS:
			{
				_hasFocus = true;
				InvokeEvent(WindowEvents::OnFocusChange);
				return 0;
			}

			// Window is about to lose focus
			// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-killfocus
			case WM_KILLFOCUS:
			{
				_hasFocus = false;
				InvokeEvent(WindowEvents::OnFocusChange);
				return 0;
			}

			// Window is being enabled or disabled
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-enable
			case WM_ENABLE:
			{
				_isEnabled = wParam;
				InvokeEvent(WindowEvents::OnEnabledChange);
				return 0;
			}

			// Close box on the window was clicked
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-close
			case WM_CLOSE:
			{
				InvokeEvent(WindowEvents::OnClose);
				return 0;
			}

			// Window is being destroyed
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-destroy
			case WM_DESTROY:
			{
				InvokeEvent(WindowEvents::OnDestroy);
				return 0;
			}

			// Window has been moved
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-move
			case WM_MOVE:
			{
				_xPos = (int)(short)LOWORD(lParam);   // horizontal position 
				_yPos = (int)(short)HIWORD(lParam);   // vertical position 
				InvokeEvent(WindowEvents::OnMoved);
				return 0;
			}

			// Window is being moved
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-moving
			case WM_MOVING:
			{
				InvokeEvent(WindowEvents::OnMoving);
				return 0;
			}

			// Window is being painted
			// https://docs.microsoft.com/en-us/windows/win32/gdi/wm-paint
			case WM_PAINT:
			{
				hdc = BeginPaint(_wndHandle, &ps);
				// TODO: Add any drawing code here...
				EndPaint(_wndHandle, &ps);
				return 0;
			}

			default:
				return DefWindowProc(_wndHandle, message, wParam, lParam);
		}
		return 0;
	}
}