module;
#include <Windows.h>

export module onyx32.gui.global;

export namespace Onyx32::GUI::Global
{
	void SetHInstance(HMODULE module);
	HMODULE GetHInstance();
}
