module;

#include <format>
#include <stdexcept>
#include <Windows.h>
#include <commctrl.h>

module onyx32.gui.windows.infra;
import onyx32.gui.windows.infra.imessageable;

namespace Onyx32::GUI::Windows::Infra
{
	LRESULT CALLBACK WndProc(HWND hWnd, unsigned message, WPARAM wParam, LPARAM lParam)
	{
		// We need these cases to bounce back messages sent to the parent from
		// child controls.
		// See also: https://stackoverflow.com/questions/29442905/win32-api-process-wm-in-tab-controls-wndproc-instead-of-parents
		if (message == WM_COMMAND)
		{
			return SendMessage((HWND)lParam, message, wParam, lParam);
		}
		if (message == WM_NOTIFY)
		{
			if (lParam == 0)
				return DefWindowProcW(hWnd, message, wParam, lParam);
			// WARNING: never send the sub-message directly to the child window.
			// SendMessage() quietly blocks the message, probably due to security.
			NMHDR* nmh = reinterpret_cast<NMHDR*>(lParam);
			return SendMessage(nmh->hwndFrom, message, wParam, lParam);
		}

		IMessageable* pThis = nullptr;
		if (message == WM_NCCREATE)
		{
			if (lParam == 0)
				return DefWindowProcW(hWnd, message, wParam, lParam);
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			if (!pCreate->lpCreateParams)
				return DefWindowProcW(hWnd, message, wParam, lParam);
			IMessageable* pThis = reinterpret_cast<IMessageable*>(pCreate->lpCreateParams);
			//pThis->SetHwnd(hWnd);
			SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
		}
		else
		{
			pThis = reinterpret_cast<IMessageable*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}

		return pThis ? pThis->Process(hWnd, message, wParam, lParam) : DefWindowProc(hWnd, message, wParam, lParam);
	}

	LRESULT CALLBACK DefCtrlProc(HWND hWnd, unsigned message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		IMessageable* ctrl = (IMessageable*)dwRefData;

		if (ctrl)
			return ctrl->Process(hWnd, message, wParam, lParam);

		return DefSubclassProc(hWnd, message, wParam, lParam);
	}
}