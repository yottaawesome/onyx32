#include "../h/stdafx.h"
#include "../h/Button.h"
#include "../h/Win32Renderer.h"
#include "../h/StaticFunctions.h"
#include  <Commctrl.h>

function<void(void)> defaultClickHandler = []() -> void
{
	MessageBox(nullptr, L"You rock!", L"Brilliant", MB_OK);
};

namespace Onyx32::Gui
{
	FunctionHandler Button::DefaultClickHandler = []() -> void {};
	const std::wstring Button::Class = L"BUTTON";

	Button::Button(
		std::wstring_view text,
		const UINT width,
		const UINT height,
		FunctionHandler& onClick,
		const unsigned int controlId)
		:	_parent(nullptr),
			_text(text),
			_onClick(defaultClickHandler),
			_controlId(controlId),
			_width(width),
			_height(height),
			_wndHandle(nullptr)
	{
	}

	const std::wstring& Button::GetName()
	{
		return Button::Class;
	}

	int Button::GetStyles()
	{
		return Button::Styles;
	}

	void Button::SetHwnd(HWND hWnd)
	{
		_wndHandle = hWnd;
	}

	HWND Button::GetHwnd()
	{
		return _wndHandle;
	}

	void Button::SetParent(IWindow* parent)
	{
		_parent = parent;
	}

	void Button::SetClickHandler(FunctionHandler& onClick)
	{
		_onClick = onClick;
	}

	UINT Button::GetWidth()
	{
		return _width;
	}

	UINT Button::GetHeight()
	{
		return _height;
	}

	const std::wstring& Button::GetText()
	{
		return _text;
	}

	void Button::Resize(const UINT width, const UINT height)
	{
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-movewindow
		MoveWindow(
			_wndHandle,
			0,
			0,
			width,
			height,
			true
		);
	}

	UINT Button::GetId()
	{
		return _controlId;
	}

	void Button::Initialize(IWindow* parent)
	{
		//Win32Renderer renderer;
		//_wndHandle = renderer.Render(static_cast<Window*>(parent), this, 10, 10);
	}

	LRESULT Button::Process(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_LBUTTONUP:
				_onClick();
			default:
				return DefSubclassProc(_wndHandle, message, wParam, lParam);
		}

		return DefSubclassProc(_wndHandle, message, wParam, lParam);
	}

	Button::~Button() 
	{
		DestroyWindow(_wndHandle);
	}
}