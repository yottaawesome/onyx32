module;

#include <format>
#include <stdexcept>
#include <Windows.h>
#include <commctrl.h>

module onyx32.gui.infra;
import onyx32.gui.infra.imessageable;

namespace Onyx32::GUI::Infra
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
			SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
			pThis->SetHwnd(hWnd);
		}
		else
		{
			pThis = reinterpret_cast<IMessageable*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
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
	
	const WNDCLASSEX& GetDefaultWindowClass()
	{
		static bool created = false;
		static WNDCLASSEX WndClass
		{
			.cbSize = sizeof(WNDCLASSEX),
			.style = CS_HREDRAW | CS_VREDRAW,
			.lpfnWndProc = WndProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = GetModuleHandleW(nullptr),
			.hIcon = nullptr,
			.hCursor = LoadCursorW(nullptr, IDC_ARROW),
			.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
			.lpszMenuName = nullptr,
			.lpszClassName = L"Onyx32DefaultWindow",		
			.hIconSm = nullptr
		};
		if (created)
			return WndClass;

		if (!RegisterClassExW(&WndClass))
			throw std::system_error(
				std::error_code(GetLastError(), std::system_category()), 
				std::format("{}: RegisterClassEx() failed with {}", __FUNCSIG__, GetLastError()));
		
		created = true;
		return WndClass;
	}
}