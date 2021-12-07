module;

#include <Windows.h>

export module onyx32.gui.infra;

export namespace Onyx32::GUI::Infra
{
	LRESULT CALLBACK WndProc(
		HWND hWnd, 
		unsigned message, 
		WPARAM wParam, 
		LPARAM lParam
	);
	LRESULT CALLBACK DefCtrlProc(
		HWND hWnd, 
		unsigned message, 
		WPARAM wParam, 
		LPARAM lParam, 
		UINT_PTR uIdSubclass, 
		DWORD_PTR dwRefData
	);
	const WNDCLASSEX& GetDefaultWindowClass();
}