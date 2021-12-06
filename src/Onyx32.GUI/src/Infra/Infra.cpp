module;

#include <Windows.h>
#include <commctrl.h>

module onyx32.gui.infra;
import onyx32.gui.infra.imessageable;

namespace Onyx32::Gui::Infra
{
	LRESULT CALLBACK WndProc(HWND hWnd, unsigned message, WPARAM wParam, LPARAM lParam)
	{
		IMessageable* pThis = nullptr;

		if (message == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			IMessageable* pThis = static_cast<IMessageable*>(pCreate->lpCreateParams);
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
		else if (message == WM_NOTIFY)
		{
			// WARNING: never send the sub-message directly to the child window.
			// SendMessage() quietly blocks the message, probably due to security.
			NMHDR* nmh = (NMHDR*)lParam;
			return SendMessage(nmh->hwndFrom, message, wParam, lParam);
		}
		else
		{
			pThis = (IMessageable*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}

		return pThis ? pThis->Process(message, wParam, lParam) : DefWindowProc(hWnd, message, wParam, lParam);
	}

	LRESULT CALLBACK DefCtrlProc(HWND hWnd, unsigned message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		IMessageable* ctrl = (IMessageable*)dwRefData;

		if (ctrl)
			return ctrl->Process(message, wParam, lParam);

		return DefSubclassProc(hWnd, message, wParam, lParam);
	}
}