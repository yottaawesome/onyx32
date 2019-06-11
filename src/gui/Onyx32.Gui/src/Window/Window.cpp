#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "Window.h"
#include "../Button/Button.h"
#include "../WindowClassManager/WindowClassManager.h"
#include "../h/Resource.h"
#include "../h/dllmain.h"
#include "../Renderer/Renderer.h"

namespace Onyx32::Gui
{
	Window::Window(const WindowClass& wndClass, wstring_view title, unsigned int width, unsigned int height)
		: _width(width), _height(height), _title(title), WndClass(wndClass), _hWnd(nullptr) { }

	Window::~Window()
	{
		for (auto item : _children)
		{
			delete item.first;
			delete item.second;
		}
		DestroyWindow(_hWnd);
	}

	void Window::SetTitle(wstring_view title)
	{
		_title = title;
		SetWindowText(_hWnd, _title.c_str());
	}

	std::wstring& Window::GetTitle()
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

	void Window::Initialize()
	{
		Renderer renderer;
		_hWnd = renderer.Render(this);

		if (!_hWnd)
			return;

		// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548%28v=vs.85%29.aspx
		ShowWindow(_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(_hWnd);
	}

	void Window::AddControl(IButton& control, UINT xPos, UINT yPos)
	{
		control.Initialize(this);
		Renderer renderer;
		control.SetHwnd(renderer.Render((Window*)this, (BaseControl<IButton>*) & control, xPos, yPos));

		_children[&control] = new ControlInfo(control, xPos, yPos);
	}

	void Window::AddControl(ITextInput& control, UINT xPos, UINT yPos)
	{
		control.Initialize(this);
		Renderer renderer;
		control.SetHwnd(renderer.Render((Window*)this, (BaseControl<ITextInput>*) &control, xPos, yPos));

		_children[&control] = new ControlInfo(control, xPos, yPos);
	}

	LRESULT Window::Process(UINT message, WPARAM wParam, LPARAM lParam)
	{
		int wmId, wmEvent;
		PAINTSTRUCT ps;
		HDC hdc;

		switch (message)
		{
			case WM_COMMAND:
				wmId = LOWORD(wParam);
				wmEvent = HIWORD(wParam);
				// Parse the menu selections:
				switch (wmId)
				{
					case IDM_ABOUT:
						//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
						break;

					case IDM_EXIT:
						DestroyWindow(_hWnd);
						break;

					default:
						return DefWindowProc(_hWnd, message, wParam, lParam);
				}
				break;

			case WM_PAINT:
				hdc = BeginPaint(_hWnd, &ps);
				// TODO: Add any drawing code here...
				EndPaint(_hWnd, &ps);
				break;

			case WM_DESTROY:
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProc(_hWnd, message, wParam, lParam);
		}
		return 0;
	}

	void Window::SetHwnd(HWND hWnd)
	{
		_hWnd = hWnd;
	}

	HWND Window::GetHwnd()
	{
		return _hWnd;
	}
}