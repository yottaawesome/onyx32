#pragma once
#include "index.hpp"

namespace Onyx32::Gui::Win32
{
	LRESULT CALLBACK WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK DefCtrlProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
}