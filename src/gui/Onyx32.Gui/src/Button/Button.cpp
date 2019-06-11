#include "../h/stdafx.h"
#include "Button.h"
#include "../Renderer/Renderer.h"
#include "../h/StaticFunctions.h"
#include <Commctrl.h>

function<void(void)> defaultClickHandler = []() -> void
{
	MessageBox(nullptr, L"You rock!", L"Brilliant", MB_OK);
};

namespace Onyx32::Gui
{
	FunctionHandler Button::DefaultClickHandler = []() -> void {};
	const std::wstring Button::Class = L"BUTTON";
	const int Button::Styles = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON;

	Button::Button(
		std::wstring_view text,
		const UINT width,
		const UINT height,
		const UINT xPos,
		const UINT yPos,
		FunctionHandler& onClick,
		const unsigned int controlId)
		: BaseControl(controlId, ControlState::Uninitialized, width, height, xPos, yPos, nullptr, nullptr),
			_text(text),
			_onClick(defaultClickHandler)
	{
	}

	Button::~Button() { }

	const std::wstring& Button::GetCreateWindowText()
	{
		return _text;
	}

	void Button::SetClickHandler(FunctionHandler& onClick)
	{
		_onClick = onClick;
	}

	const std::wstring& Button::GetText()
	{
		return _text;
	}

	void Button::Resize(const UINT width, const UINT height)
	{
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-movewindow
		if (MoveWindow(_wndHandle, _xPos, _yPos, width, height, true))
		{
			_width = width;
			_height = height;
		}
	}

	void Button::Initialize(IWindow* parent)
	{
		if (_state == ControlState::Uninitialized)
		{
			_parent = parent;
			Win32CreationArgs args(
				0,
				Button::Class,
				_text,
				Button::Styles,
				_xPos,
				_yPos,
				_width,
				_height,
				parent->GetHwnd(),
				(HMENU)_controlId,
				this,
				Static::DefCtrlProc
			);

			_wndHandle = Win32Window::CreateChildWindow(args);
			_state = ControlState::Initialized;
		}
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
}