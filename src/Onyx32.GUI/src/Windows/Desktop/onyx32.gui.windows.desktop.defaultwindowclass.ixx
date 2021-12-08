module;

#include <Windows.h>

export module onyx32.gui.windows.desktop;

export namespace Onyx32::GUI::Windows::Desktop
{
	const WNDCLASSEX& GetDefaultWindowClass();
}