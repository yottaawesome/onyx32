#include "../h/stdafx.h"
#include "../h/Button.h"
#include "../h/Win32Renderer.h"
#include "../h/StaticFunctions.h"
#include  <Commctrl.h>

namespace Onyx32::Gui
{
	Button::Button(unsigned int controlId, std::wstring& text, FunctionHandler& onClick, unsigned int width, unsigned int height)
		: parent(nullptr), text(text), onClick(onClick), controlId(controlId), width(width), height(height), hwndButton(nullptr)
	{
		width = width > 0 ? width : 100;
		height = height > 0 ? height : 100;
		if (text.length() == 0)
			this->text = L"Default";
	}

	void Button::SetHwnd(HWND hWnd)
	{
		this->hwndButton = hWnd;
	}

	HWND Button::GetHwnd()
	{
		return hwndButton;
	}

	void Button::SetParent(IWindow* parent)
	{
		this->parent = parent;
	}

	UINT Button::GetWidth()
	{
		return width;
	}

	UINT Button::GetHeight()
	{
		return height;
	}

	const std::wstring& Button::GetText()
	{
		return text;
	}

	UINT Button::GetId()
	{
		return controlId;
	}

	void Button::Initialize(IWindow* parent)
	{
		Win32Renderer renderer;
		hwndButton = renderer.Render(static_cast<Window*>(parent), this, 10, 10);
	}

	LRESULT Button::Process(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_LBUTTONUP:
				this->onClick();
			default:
				return DefSubclassProc(hwndButton, message, wParam, lParam);
		}

		return DefSubclassProc(hwndButton, message, wParam, lParam);
	}

	Button::~Button() { }
}