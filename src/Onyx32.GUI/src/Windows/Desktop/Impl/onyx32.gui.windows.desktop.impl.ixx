module;

#include <Windows.h>

export module onyx32.gui.windows.desktop.impl;
import onyx32.gui.windows.desktop;
import onyx32.gui.windows.infra.imessageable;

export namespace Onyx32::GUI::Windows::Desktop::Impl
{
	class DesktopWindow : public IDesktopWindow, public Infra::IMessageable
	{
		public:
			virtual ~DesktopWindow();
			DesktopWindow();
		
		// Imessageable
		public:
			virtual LRESULT Process(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam) override;
			virtual void SetHwnd(HWND hWnd) override;
			virtual WPARAM MainLoop() override;

		public:
			const WNDCLASSEX& GetDefaultWindowClass();

		protected:
			virtual void Construct();

		protected:
			HWND m_hwnd;
	};
}