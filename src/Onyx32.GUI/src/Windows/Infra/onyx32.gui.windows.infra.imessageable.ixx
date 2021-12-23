module;

#include <Windows.h>

export module onyx32.gui.windows.infra.imessageable;

export namespace Onyx32::GUI::Windows::Infra
{
	struct IMessageable
	{
		virtual ~IMessageable();
		virtual LRESULT Process(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam) = 0;
		virtual void SetHwnd(HWND hWnd) = 0;
	};
}