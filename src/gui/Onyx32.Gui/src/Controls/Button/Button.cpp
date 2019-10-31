#include "../../h/stdafx.h"
#include "Button.h"
#include "../../Win32/Win32Window.h"
#include "../../h/Win32Callbacks.h"
#include <Commctrl.h>

using std::wstring;

namespace Onyx32::Gui::Controls
{
	OnClick DefaultClickHandler = [](IButton& button) -> void {};

	const std::wstring Button::Class = L"BUTTON";
	const int Button::Styles = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_NOTIFY;

	IButton* Button::Create(IWindow* parent, uint64_t controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos)
	{
		auto control = new Button(text, width, height, xPos, yPos, controlId);
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
			control,
			DefCtrlProc
		);
		if (control->_wndHandle = CreateChildWindow(args))
		{
			control->_state = ControlState::Initialized;
			control->_isVisible = true;
			return control;
		}

		delete control;
		return nullptr;
	}

	Button::Button(
		std::wstring_view text,
		const unsigned int width,
		const unsigned int height,
		const unsigned int xPos,
		const unsigned int yPos,
		const uint64_t controlId)
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

	void Button::Initialize()
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

	LRESULT Button::Process(unsigned int message, WPARAM wParam, LPARAM lParam)
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