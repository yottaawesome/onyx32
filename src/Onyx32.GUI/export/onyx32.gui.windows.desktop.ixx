module;

#include <Windows.h>;

export module onyx32.gui.windows.desktop;

export namespace Onyx32::GUI::Windows::Desktop
{
	struct __declspec(dllexport) IDesktopWindow
	{
		virtual ~IDesktopWindow();
		virtual WPARAM MainLoop() = 0;
	};
}
