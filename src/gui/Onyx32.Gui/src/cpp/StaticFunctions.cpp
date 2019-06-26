#include "../h/StaticFunctions.h"
#include "../h/Onyx32.Gui.internal.h"
#include "../Window/Window.h"
#include  <Commctrl.h>

using namespace Onyx32::Gui;

LRESULT CALLBACK Static::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	IWindow* pThis = nullptr;

	if (message == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		Window* pThis = (Window*)pCreate->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
		pThis->SetHwnd(hWnd);
	}
	// We need these cases to bounce back messages sent to the parent from
	// child controls.
	// See also: https://stackoverflow.com/questions/29442905/win32-api-process-wm-in-tab-controls-wndproc-instead-of-parents
	else if (message == WM_COMMAND)
	{
		return SendMessage((HWND)lParam, message, wParam, lParam);
	}
	else if(message == WM_NOTIFY)
	{
		// WARNING: never send the sub-message directly to the child window.
		// SendMessage() quietly blocks the message, probably due to security.
		NMHDR* nmh = (NMHDR*) lParam;
		return SendMessage(nmh->hwndFrom, message, wParam, lParam);
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