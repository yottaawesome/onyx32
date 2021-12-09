module;

#include <Windows.h>

export module onyx32.gui.windows.desktop.impl;

export namespace Onyx32::GUI::Windows::Desktop::Impl
{
	const WNDCLASSEX& GetDefaultWindowClass();
}