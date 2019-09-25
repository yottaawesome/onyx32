#include "../../h/stdafx.h"
#include "TextInput.h"
#include "../..//Win32/Win32Window.h"
#include "../../h/StaticFunctions.h"
#include  <Commctrl.h>

using std::wstring;
using std::wstring_view;

namespace Onyx32::Gui
{
	const std::wstring TextInput::Class = L"EDIT";
	const int TextInput::Styles = WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL;

	ITextInput* TextInput::Create(IWindow* parent, UINT controlId, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos)
	{
		auto control = new TextInput(text, width, height, xPos, yPos, controlId);
		Win32ChildWindowCreationArgs args(
			0,
			TextInput::Class,
			text,
			TextInput::Styles,
			xPos,
			yPos,
			width,
			height,
			parent->GetHwnd(),
			(HMENU)controlId,
			control,
			Static::DefCtrlProc
		);
		;
		if (control->_wndHandle = CreateChildWindow(args))
		{
			control->_state = ControlState::Initialized;
			control->_isVisible = true;
			return control;
		}

		delete control;
		return nullptr;
	}

	TextInput::TextInput(
		std::wstring_view text,
		const UINT width,
		const UINT height,
		const UINT xPos,
		const UINT yPos,
		const unsigned int controlId)
		: BaseControl(controlId, ControlState::Uninitialized, width, height, xPos, yPos, nullptr, nullptr), _text(text)
	{ }

	TextInput::~TextInput() { }

	void TextInput::Initialize(IWindow* window)
	{
	}

	const wstring TextInput::GetText()
	{
		//WCHAR* ptr = new WCHAR[100];
		//GetWindowText(
		//	hwndEdit,
		//	ptr,
		//	100);
		return _text;
	}

	void TextInput::SetText(wstring_view str)
	{
		_text = str;
		SetWindowText(_wndHandle, _text.c_str());
	}

	LRESULT TextInput::Process(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			default:
				return DefSubclassProc(_wndHandle, message, wParam, lParam);
		}

		return DefSubclassProc(_wndHandle, message, wParam, lParam);
	}
}