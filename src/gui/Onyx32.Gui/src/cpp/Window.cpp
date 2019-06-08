#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "../h/Window.h"
#include "../h/WindowClassManager.h"
#include "../h/Resource.h"
#include "../h/dllmain.h"
#include "../h/Win32Renderer.h"

using namespace Onyx32::Gui;

namespace Onyx32::Gui
{
	Window::Window(wstring& title, unsigned int width, unsigned int height)
		: width(width), height(height), title(title), wcex(WindowClassManager::GetDefaultWindowClass()), hWnd(nullptr) { }

	Window::Window(wstring&& title, unsigned int width, unsigned int height)
		: width(width), height(height), title(title), wcex(WindowClassManager::GetDefaultWindowClass()), hWnd(nullptr) { }

	void Window::SetTitle(wstring& title)
	{
		this->title = title;
		SetWindowText(hWnd, this->title.c_str());
	}

	std::wstring& Window::GetTitle()
	{
		return title;
	}

	UINT Window::GetWidth()
	{
		return width;
	}

	UINT Window::GetHeight()
	{
		return height;
	}

	WindowClass Window::GetWndClass()
	{
		return wcex;
	}

	void Window::SetTitle(wstring&& title)
	{
		this->title = title;
		SetWindowText(hWnd, this->title.c_str());
	}

	void Window::Initialize()
	{
		Win32Renderer renderer;
		hWnd = renderer.Render(this);

		if (!hWnd)
			return;

		// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548%28v=vs.85%29.aspx
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);
	}

	void Window::AddControl(IControl* control, unsigned int xPos, unsigned int yPos)
	{
		if (control != nullptr)
			control->Initialize(this);
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
						DestroyWindow(hWnd);
						break;

					default:
						return DefWindowProc(hWnd, message, wParam, lParam);
				}
				break;

			case WM_PAINT:
				hdc = BeginPaint(hWnd, &ps);
				// TODO: Add any drawing code here...
				EndPaint(hWnd, &ps);
				break;

			case WM_DESTROY:
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	void Window::SetHwnd(HWND hWnd)
	{
		this->hWnd = hWnd;
	}

	HWND Window::GetHwnd()
	{
		return this->hWnd;
	}
}