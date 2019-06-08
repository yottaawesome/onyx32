#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "../h/Input.h"
#include  <Commctrl.h>

namespace Onyx32::Gui
{
	void Input::Initialize(IWindow* window)
	{
		this->parent = window;

		hwndEdit = CreateWindowEx(
			0, L"EDIT",   // predefined class 
			NULL,         // no window title 
			WS_CHILD | WS_VISIBLE | WS_VSCROLL |
			ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			0, 0, 100, 50,   // set size in WM_SIZE message 
			parent->GetHwnd(),         // parent window 
			(HMENU)100,   // edit control ID 
			(HINSTANCE)GetWindowLongPtr(parent->GetHwnd(), GWLP_HINSTANCE),
			NULL);        // pointer not needed 
	}

	wstring Input::GetText()
	{
		//WCHAR* ptr = new WCHAR[100];
		//GetWindowText(
		//	hwndEdit,
		//	ptr,
		//	100);
		wstring s = text;
		return s;
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

	}
	
	HWND Input::GetHwnd()
	{
		return nullptr;
	}

	Input::~Input()
	{

	}
}