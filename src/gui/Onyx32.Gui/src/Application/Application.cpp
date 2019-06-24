#include "../h/stdafx.h"
#include "Application.h"

namespace Onyx32::Gui
{
	Application::Application() : _accelerators(nullptr) { }

	Application::Application(HACCEL accelerators) : _accelerators(accelerators) { }

	Application::~Application() { }

	void Application::SetAccelerators(HACCEL accelerators)
	{
		_accelerators = accelerators;
	}

	int Application::MainLoop()
	{
		MSG msg;
		if (this->_accelerators == nullptr)
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
				if (!TranslateAccelerator(msg.hwnd, _accelerators, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
		
		return (int)msg.wParam;
	}
}
