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

	int Application::MainLoop(IdleCallback callback)
	{
		unsigned long long int counter = 0;
		bool continueLoop = true;
		MSG msg = { 0 };

		// If there are Window messages then process them.
		while (msg.message != WM_QUIT && continueLoop)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				if (this->_accelerators == nullptr)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else if (!TranslateAccelerator(msg.hwnd, _accelerators, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{
				continueLoop = callback(counter);
			}
			counter++;
		}

		return (int)msg.wParam;
	}
}
