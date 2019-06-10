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
		:text(text), _width(width), _height(height), _controlId(controlId)
	{

	}
	
	Input::~Input()
	{

	}

	void Input::Initialize(IWindow* window)
	{
		/*_parent = window;

		hwndEdit = CreateWindowEx(
			0, 
			L"EDIT",   // predefined class 
			NULL,         // no window title 
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			0, 0, 100, 50,   // set size in WM_SIZE message 
			_parent->GetHwnd(),         // parent window 
			(HMENU)100,   // edit control ID 
			(HINSTANCE)GetWindowLongPtr(_parent->GetHwnd(), GWLP_HINSTANCE),
			NULL);        // pointer not needed 
			*/
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

	wstring Input::GetText()
	{
		//WCHAR* ptr = new WCHAR[100];
		//GetWindowText(
		//	hwndEdit,
		//	ptr,
		//	100);
		return text;
	}

	void Input::SetText(wstring* str)
	{
		this->text = std::move(*str);
		SetWindowText(hwndEdit, text.c_str());
	}

	void Input::SetText(wstring&& str)
	{
		this->text = std::move(str);
		SetWindowText(hwndEdit, text.c_str());
	}
	
	LRESULT Input::Process(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			default:
				return DefSubclassProc(hwndEdit, message, wParam, lParam);
		}

		return DefSubclassProc(hwndEdit, message, wParam, lParam);
	}
	
	void Input::SetHwnd(HWND hWnd)
	{
		hwndEdit = hWnd;
	}
	
	HWND Input::GetHwnd()
	{
		return nullptr;
	}
}