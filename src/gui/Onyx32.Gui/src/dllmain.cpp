// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "dllmain.h"

using namespace Onyx32::Gui;

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
}

bool APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			OutputDebugString(L"DLL_PROCESS_ATTACH");
			Dll::SetModule(hModule);
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return true;
}

