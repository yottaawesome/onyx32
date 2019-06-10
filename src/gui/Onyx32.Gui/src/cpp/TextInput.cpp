#include "../h/stdafx.h"
#include "../h/TextInput.h"
#include  <Commctrl.h>

namespace Onyx32::Gui
{
	const std::wstring TextInput::Class = L"EDIT";

	TextInput::TextInput(
		std::wstring_view text,
		const UINT width,
		const UINT height,
		const unsigned int controlId)
		: BaseControl(controlId, width, height, nullptr, nullptr)
	{

	}

	TextInput::~TextInput()
	{
		DestroyWindow(_wndHandle);
	}

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

	int TextInput::GetStyles()
	{
		return TextInput::Styles;
	}

	const std::wstring& TextInput::GetName()
	{
		return TextInput::Class;
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