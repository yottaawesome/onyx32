#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"

using namespace Onyx32::System;

namespace Onyx32::System
{
	Application::Application() { }

	Application::Application(HACCEL accelerators) : accelerators(accelerators) { }

	int Application::MainLoop()
	{
		MSG msg;
		if (this->accelerators == nullptr)
		{
			while (GetMessage(&msg, nullptr, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			while (GetMessage(&msg, nullptr, 0, 0))
			{
				if (!TranslateAccelerator(msg.hwnd, this->accelerators, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
		
		return (int)msg.wParam;
	}
}
