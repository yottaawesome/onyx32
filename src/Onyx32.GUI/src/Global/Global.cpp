module;

#include <Windows.h>

module onyx32.gui.global;

namespace Onyx32::GUI::Global
{
	static HMODULE g_hModule;

	void SetHInstance(HMODULE hModule)
	{
		g_hModule = hModule;
	}

	HMODULE GetHInstance()
	{
		return g_hModule;
	}
}
