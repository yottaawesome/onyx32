#pragma once
#include "index.h"

namespace Onyx32::Gui
{
	LRESULT CALLBACK WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK DefCtrlProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
}