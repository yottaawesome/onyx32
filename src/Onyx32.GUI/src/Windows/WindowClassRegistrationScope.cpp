module;

#include <format>
#include <stdexcept>
#include <Windows.h>

module onyx32.gui.windows.windowclassregistrationscope;

namespace Onyx32::GUI::Windows::Desktop
{
	WindowClassRegistrationScope::~WindowClassRegistrationScope()
	{
		UnregisterClassW(m_class.lpszClassName, GetModuleHandleW(nullptr));
	}
	
	WindowClassRegistrationScope::WindowClassRegistrationScope(const WNDCLASSEX& wndClass)
		: m_class(wndClass)
	{
		// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexw
		// No window classes registered by a DLL are unregistered when the DLL is unloaded. 
		// A DLL must explicitly unregister its classes when it is unloaded.
		if (!RegisterClassExW(&m_class))
			throw std::system_error(
				std::error_code(GetLastError(), std::system_category()),
				std::format("{}: RegisterClassEx() failed with {}", __FUNCSIG__, GetLastError()));
	}

	const WNDCLASSEX& WindowClassRegistrationScope::GetClass() const noexcept
	{
		return m_class;
	}
}