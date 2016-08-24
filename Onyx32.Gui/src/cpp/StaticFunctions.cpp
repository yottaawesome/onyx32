#include "../h/StaticFunctions.h"
#include "../../include/Onyx32.Gui.h"
#include  <Commctrl.h>

using namespace Onyx::Windows;

LRESULT CALLBACK Static::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	IWindow* pThis = nullptr;

	if (message == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		IWindow* pThis = (IWindow*)pCreate->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
		pThis->SetHwnd(hWnd);
	}
	else
	{
		pThis = (IWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	return pThis ? pThis->Process(message, wParam, lParam) : DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK Static::DefCtrlProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	IControl* btn = (IControl*)dwRefData;

	if (btn)
		return btn->Process(message, wParam, lParam);

	return DefSubclassProc(hWnd, message, wParam, lParam);
}