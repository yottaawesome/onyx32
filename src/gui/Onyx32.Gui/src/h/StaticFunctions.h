#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"

class Static
{
public:
	static LRESULT CALLBACK	WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK DefCtrlProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
};