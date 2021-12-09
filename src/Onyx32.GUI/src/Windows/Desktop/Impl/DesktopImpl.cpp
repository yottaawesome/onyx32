module;

#include <format>
#include <stdexcept>
#include <Windows.h>

module onyx32.gui.windows.desktop.impl;
import onyx32.gui.infra;
import onyx32.gui.windows.windowclassregistrationscope;

namespace Onyx32::GUI::Windows::Desktop::Impl
{
	const WNDCLASSEX& GetDefaultWindowClass()
	{
		static bool created = false;
		static WNDCLASSEX WndClass
		{
			.cbSize = sizeof(WNDCLASSEX),
			.style = CS_HREDRAW | CS_VREDRAW,
			.lpfnWndProc = Infra::WndProc,
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

		static WindowClassRegistrationScope DefaultWindowClassScope(WndClass);
		created = true;

		return WndClass;
	}
}