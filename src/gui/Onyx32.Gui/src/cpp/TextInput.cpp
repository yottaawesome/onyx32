#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
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
		: _text(text), _width(width), _height(height), _controlId(controlId), _wndHandle(nullptr), _parent(nullptr)
	{

	}
	
	TextInput::~TextInput()
	{
		DestroyWindow(_wndHandle);
	}

	void TextInput::Initialize(IWindow* window)
	{
	}

	void TextInput::SetParent(IWindow* parent)
	{
		_parent = parent;
	}

	UINT TextInput::GetId()
	{
		return _controlId;
	}

	const std::wstring& TextInput::GetName()
	{
		return TextInput::Class;
	}

	UINT TextInput::GetWidth()
	{
		return _width;
	}

	UINT TextInput::GetHeight()
	{
		return _height;
	}

	int TextInput::GetStyles()
	{
		return TextInput::Styles;
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
	
	void TextInput::SetHwnd(HWND hWnd)
	{
		_wndHandle = hWnd;
	}
	
	HWND TextInput::GetHwnd()
	{
		return nullptr;
	}
}