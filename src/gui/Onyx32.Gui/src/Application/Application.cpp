#include "../h/stdafx.h"
#include "Application.h"

namespace Onyx32::Gui
{
	Application::Application() : accelerators(nullptr) { }

	Application::Application(HACCEL accelerators) : accelerators(accelerators) { }

	Application::~Application() { }

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
