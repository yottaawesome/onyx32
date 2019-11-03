// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "dllmain.h"
#include "shared/Onyx32.Gui.internal.h"
#include "Factory/Factory.h"

namespace Onyx32::Gui
{
	HMODULE Dll::module = nullptr;
	
	void Dll::SetModule(HMODULE dllModule)
	{
		Dll::module = dllModule;
	}

	HMODULE Dll::GetModule()
	{
		return Dll::module;
	}

	//https://stackoverflow.com/questions/3628529/should-c-interfaces-have-a-virtual-destructor
	//https://stackoverflow.com/questions/2691611/destructors-for-c-interface-like-classes
	inline IWindow::~IWindow() { }
	inline IFactory::~IFactory() { }
	inline IApplication::~IApplication() { }
	inline IMenu::~IMenu() { }
	IFactory* GetMainFactory()
	{
		return new Factory();
	}
}

namespace Onyx32::Gui::Controls
{
	inline IControl::~IControl() { }
	inline IButton::~IButton() { }
	inline ITextInput::~ITextInput() { }
	inline IDateTime::~IDateTime() { }
}

bool APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			OutputDebugString(L"DLL_PROCESS_ATTACH");
			Onyx32::Gui::Dll::SetModule(hModule);
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return true;
}
