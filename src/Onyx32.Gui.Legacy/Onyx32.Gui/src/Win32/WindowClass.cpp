#include "stdafx.h"
#include "index.internal.hpp"
#include "../Resource.h"
#include "../dllmain.hpp"

namespace Onyx32::Gui::Win32
{
	WindowClass DefaultWindowClass = WindowClass();

	WindowClass GetDefaultWindowClass()
	{
		static bool created = false;
		if (!created)
		{
			DefaultWindowClass.WndClass.cbSize = sizeof(WNDCLASSEX);
			DefaultWindowClass.WndClass.lpszClassName = L"Onyx32DefaultWindow";
			DefaultWindowClass.WndClass.style = CS_HREDRAW | CS_VREDRAW;
			DefaultWindowClass.WndClass.lpfnWndProc = WndProc;
			DefaultWindowClass.WndClass.cbClsExtra = 0;
			DefaultWindowClass.WndClass.cbWndExtra = 0;
			DefaultWindowClass.WndClass.hInstance = DLL::GetModule();
			DefaultWindowClass.WndClass.hIcon = nullptr;
				//(HICON)LoadImage(DLL::GetModule(), MAKEINTRESOURCE(IDI_ONYX32), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
				//LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ONYX32));
			DefaultWindowClass.WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			DefaultWindowClass.WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			DefaultWindowClass.WndClass.lpszMenuName = nullptr;
				// MAKEINTRESOURCE(IDC_ONYX32);
			DefaultWindowClass.WndClass.hIconSm = 
				(HICON)LoadImage(DLL::GetModule(), MAKEINTRESOURCE(IDI_SMALL), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE); 
				//LoadIcon(DLL::GetModule(), MAKEINTRESOURCE(IDI_SMALL));

			RegisterClassEx(&DefaultWindowClass.WndClass);

			created = true;
		}

		return DefaultWindowClass;
	}
}
