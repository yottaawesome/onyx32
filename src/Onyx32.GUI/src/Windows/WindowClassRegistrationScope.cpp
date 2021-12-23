module;

#include <format>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <Windows.h>

module onyx32.gui.windows.windowclassregistrationscope;

namespace Onyx32::GUI::Windows::Desktop
{
	WindowClassRegistrationScope::~WindowClassRegistrationScope() noexcept
	{
		try
		{
			std::wcout << "Unregister";
			if (!IsolationAwareUnregisterClassW(m_class.lpszClassName, GetModuleHandleW(nullptr)))
				std::wcout << std::format(L"IsolationAwareUnregisterClassW() failed: {}\n", GetLastError());
		}
		catch (...) 
		{
		}
	}
	
	WindowClassRegistrationScope::WindowClassRegistrationScope(const WNDCLASSEX& wndClass)
		: m_class(wndClass)
	{
		// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexw
		// No window classes registered by a DLL are unregistered when the DLL is unloaded. 
		// A DLL must explicitly unregister its classes when it is unloaded.
		if (!RegisterClassExW(&m_class))
			throw std::system_error( // https://stackoverflow.com/questions/15854930/how-do-you-use-stdsystem-error-with-getlasterror
				std::error_code(GetLastError(), std::system_category()),
				std::format("{}: RegisterClassEx() failed with {}", __FUNCSIG__, GetLastError()));
	}

	const WNDCLASSEX& WindowClassRegistrationScope::GetClass() const noexcept
	{
		return m_class;
	}
}