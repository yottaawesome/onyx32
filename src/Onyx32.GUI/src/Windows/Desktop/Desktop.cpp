module;

#include <format>
#include <stdexcept>
#include <Windows.h>

module onyx32.gui.windows.desktop;
import onyx32.gui.infra;

namespace Onyx32::GUI::Windows::Desktop
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

		if (!RegisterClassExW(&WndClass))
			throw std::system_error(
				std::error_code(GetLastError(), std::system_category()),
				std::format("{}: RegisterClassEx() failed with {}", __FUNCSIG__, GetLastError()));

		created = true;
		return WndClass;
	}
}