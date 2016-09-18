#include "../h/stdafx.h"
#include "../h/Button.h"
#include "../h/StaticFunctions.h"
#include  <Commctrl.h>

namespace Onyx32::Gui
{
	Button::Button(unsigned int controlId, wstring& text, FunctionHandler& onClick, unsigned int width, unsigned int height)
		: parent(nullptr), text(text), onClick(onClick), controlId(controlId), width(width), height(height)
	{
		width = width > 0 ? width : 100;
		height = height > 0 ? height : 100;
		if (text.length() == 0)
			this->text = L"Default";
	}

	void Button::Initialize(IWindow* parent)
	{
		if (parent == nullptr)
		{
			OutputDebugString(L"Cannot initialize a control without a parent");
			return;
		}
		this->parent = parent;

		HWND parentHwnd = parent->GetHwnd();
		hwndButton = CreateWindow
		(
			L"BUTTON",  // Predefined class; Unicode assumed 
			this->text.c_str(),      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,         // x position 
			10,         // y position 
			width,        // Button width
			height,        // Button height
			parentHwnd,     // Parent window
			(HMENU)controlId,       // No menu.
			(HINSTANCE)GetWindowLongPtr(parentHwnd, GWLP_HINSTANCE),
			this
		);

		SetWindowSubclass(hwndButton, Static::DefCtrlProc, 0, (DWORD_PTR)this);
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

	void Button::SetHwnd(HWND hWnd)
	{
		this->hwndButton = hWnd;
	}

	HWND Button::GetHwnd()
	{
		return hwndButton;
	}

	Button::~Button() { }
}