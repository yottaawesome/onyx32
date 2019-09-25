#include "../../h/stdafx.h"
#include "Button.h"
#include "../../Win32/Win32Window.h"
#include "../../h/StaticFunctions.h"
#include <Commctrl.h>

using std::wstring;

namespace Onyx32::Gui
{
	OnClick DefaultClickHandler = [](IButton& button) -> void {};

	const std::wstring Button::Class = L"BUTTON";
	const int Button::Styles = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_NOTIFY;

	IButton* Button::Create(IWindow* parent, UINT controlId, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos)
	{
		auto button = new Button(text, width, height, xPos, yPos, controlId);
		Win32ChildWindowCreationArgs args(
			0,
			Button::Class,
			text,
			Button::Styles,
			xPos,
			yPos,
			width,
			height,
			parent->GetHwnd(),
			(HMENU)controlId,
			button,
			Static::DefCtrlProc
		);
		HWND _wndHandle = nullptr;
		if (_wndHandle = CreateChildWindow(args))
		{
			button->SetHwnd(_wndHandle);
		}
		else
		{
			delete button;
			return nullptr;
		}
		return button;
	}

	void Button::SetHwnd(HWND hWnd) 
	{
		this->_wndHandle = hWnd;
		_state = ControlState::Initialized;
		_isVisible = true;
	}

	Button::Button(
		std::wstring_view text,
		const UINT width,
		const UINT height,
		const UINT xPos,
		const UINT yPos,
		const unsigned int controlId)
		: BaseControl(controlId, ControlState::Uninitialized, width, height, xPos, yPos, nullptr, nullptr),
			_text(text)
	{
	}

	Button::~Button() 
	{
		OutputDebugString(L"\nButton destroyed"); 
	}

	const std::wstring& Button::GetText() const
	{
		return _text;
	}

	void Button::SetText(std::wstring_view str)
	{
		if (SetWindowText(_wndHandle, wstring(str).c_str()))
			_text = str;
	}

	void Button::Initialize(IWindow* parent)
	{
	}

	void Button::SetEvent(ButtonEvents evt, OnButtonEvent&& evtHandler)
	{
		_buttonEventHandlers[evt] = std::move(evtHandler);
	}

	void Button::InvokeEvent(const ButtonEvents evt)
	{
		if (_state == ControlState::Initialized && _buttonEventHandlers.count(evt))
			_buttonEventHandlers[evt](evt, *this);
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
						InvokeEvent(ButtonEvents::OnClick);
						return 0;
					
					case BN_DBLCLK:
						InvokeEvent(ButtonEvents::OnDoubleClick);
						return 0;

					default:
						return BaseControl<IButton>::Process(message, wParam, lParam);
				}
			}
				
			default:
				return BaseControl<IButton>::Process(message, wParam, lParam);
		}
	}
}