// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "dllmain.hpp"
#include "../include/Onyx32.Gui.hpp"
#include "Factory/Factory.hpp"

namespace Onyx32::Gui
{
	HMODULE DLL::module = nullptr;
	HANDLE DLL::heapHandle = nullptr;
	
	void DLL::SetModule(HMODULE dllModule)
	{
		DLL::module = dllModule;
	}

	HMODULE DLL::GetModule()
	{
		return DLL::module;
	}

	void DLL::SetHeap(HANDLE heap)
	{
		heapHandle = heap;
	}

	HANDLE DLL::GetHeap()
	{
		return heapHandle;
	}

	IFactory* GetMainFactory()
	{
		return new Factory();
	}

	void SetHeap(HANDLE heap)
	{
		DLL::SetHeap(heap);
	}

	//https://stackoverflow.com/questions/3628529/should-c-interfaces-have-a-virtual-destructor
	//https://stackoverflow.com/questions/2691611/destructors-for-c-interface-like-classes
	inline IWindow::~IWindow() { }
	inline IFactory::~IFactory() { }
	inline IMainLoop::~IMainLoop() { }
	inline IMenu::~IMenu() { }
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
			Onyx32::Gui::DLL::SetModule(hModule);
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return true;
}
