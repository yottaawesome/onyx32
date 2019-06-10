#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "../h/Input.h"
#include  <Commctrl.h>

namespace Onyx32::Gui
{
	const std::wstring Input::Class = L"EDIT";

	Input::Input(
		std::wstring_view text,
		const UINT width,
		const UINT height,
		const unsigned int controlId)
		:text(text), _width(width), _height(height), _controlId(controlId), _wndHandle(nullptr), _parent(nullptr)
	{

	}
	
	Input::~Input()
	{
		DestroyWindow(_wndHandle);
	}

	void Input::Initialize(IWindow* window)
	{
	}

	void Input::SetParent(IWindow* parent)
	{
		_parent = parent;
	}

	UINT Input::GetId()
	{
		return _controlId;
	}

	const std::wstring& Input::GetName()
	{
		return Input::Class;
	}

	UINT Input::GetWidth()
	{
		return _width;
	}

	UINT Input::GetHeight()
	{
		return _height;
	}

	int Input::GetStyles()
	{
		return Input::Styles;
	}

	const wstring Input::GetText()
	{
		//WCHAR* ptr = new WCHAR[100];
		//GetWindowText(
		//	hwndEdit,
		//	ptr,
		//	100);
		return text;
	}

	void Input::SetText(wstring_view str)
	{
		this->text = str;
		SetWindowText(_wndHandle, text.c_str());
	}
	
	LRESULT Input::Process(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			default:
				return DefSubclassProc(_wndHandle, message, wParam, lParam);
		}

		return DefSubclassProc(_wndHandle, message, wParam, lParam);
	}
	
	void Input::SetHwnd(HWND hWnd)
	{
		_wndHandle = hWnd;
	}
	
	HWND Input::GetHwnd()
	{
		return nullptr;
	}
}