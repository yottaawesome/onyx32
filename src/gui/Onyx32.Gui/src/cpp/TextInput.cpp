#include "../h/stdafx.h"
#include "../h/TextInput.h"
#include  <Commctrl.h>

namespace Onyx32::Gui
{
	const std::wstring TextInput::Class = L"EDIT";
	const int TextInput::Styles = WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL;

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