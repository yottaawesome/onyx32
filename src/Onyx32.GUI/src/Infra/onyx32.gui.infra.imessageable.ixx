module;

#include <Windows.h>

export module onyx32.gui.infra.imessageable;

export namespace Onyx32::GUI::Infra
{
	struct IMessageable
	{
		virtual LRESULT Process(unsigned int message, WPARAM wParam, LPARAM lParam) = 0;
		virtual void SetHwnd(HWND hWnd) = 0;
		virtual ~IMessageable();
	};
}