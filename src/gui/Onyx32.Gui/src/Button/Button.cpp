#include "../h/stdafx.h"
#include "Button.h"
#include "../Win32/Win32Window.h"
#include "../h/StaticFunctions.h"
#include <Commctrl.h>

using std::wstring;

namespace Onyx32::Gui
{
	OnClick DefaultClickHandler = [](IButton& button) -> void {};

	const std::wstring Button::Class = L"BUTTON";
	const int Button::Styles = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_NOTIFY;

	Button::Button(
		std::wstring_view text,
		const UINT width,
		const UINT height,
		const UINT xPos,
		const UINT yPos,
		const unsigned int controlId)
		: BaseControl(controlId, ControlState::Uninitialized, width, height, xPos, yPos, nullptr, nullptr),
			_text(text),
			_onClick(DefaultClickHandler),
			_onDblClick(DefaultClickHandler)
	{
	}

	Button::~Button() 
	{
		OutputDebugString(L"\nButton destroyed"); 
	}

	const std::wstring& Button::GetText()
	{
		return _text;
	}

	void Button::SetOnClick(OnClick&& onClick)
	{
		_onClick = std::move(onClick);
	}

	void Button::SetOnDoubleClick(OnClick&& onDblClick)
	{
		_onDblClick = std::move(onDblClick);
	}

	void Button::SetText(std::wstring_view str)
	{
		if (SetWindowText(_wndHandle, wstring(str).c_str()))
			_text = str;
	}

	void Button::Initialize(IWindow* parent)
	{
		if (_state == ControlState::Uninitialized)
		{
			_parent = parent;

			Win32ChildWindowCreationArgs args(
				0,
				Button::Class,
				_text,
				Button::Styles,
				_xPos,
				_yPos,
				_width,
				_height,
				_parent->GetHwnd(),
				(HMENU)_controlId,
				this,
				Static::DefCtrlProc
			);
			if (_wndHandle = Win32Window::CreateChildWindow(args))
			{
				_state = ControlState::Initialized;
				_isVisible = true;
			}
			else
			{
				_state = ControlState::Error;
			}
		}
	}

	LRESULT Button::Process(UINT message, WPARAM wParam, LPARAM lParam)
	{
		// https://docs.microsoft.com/en-us/windows/desktop/Controls/button-messages
		switch (message)
		{
			case WM_COMMAND:
			{
				switch (HIWORD(wParam))
				{
					case BN_CLICKED:
						_onClick(*this);
					break;
					
					case BN_DBLCLK:
						_onDblClick(*this);
					break;

					default:
						return BaseControl<IButton>::Process(message, wParam, lParam);
				}
				return 0;
			}
				
			default:
				return BaseControl<IButton>::Process(message, wParam, lParam);
		}
	}
}