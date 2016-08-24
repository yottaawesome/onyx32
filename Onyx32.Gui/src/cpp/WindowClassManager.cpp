#include "../h/WindowClassManager.h"
#include "../h/StaticFunctions.h"
#include "../h/Resource.h"

using namespace Onyx32::Windows;

WindowClass WindowClassManager::DefaultWindowClass = WindowClass();

WindowClass WindowClassManager::GetDefaultWindowClass()
{
	static bool created = false;
	if (!created)
	{
		DefaultWindowClass.ClassName = L"Win32FrameworkDefault";
		DefaultWindowClass.WndClass.cbSize = sizeof(WNDCLASSEX);
		DefaultWindowClass.WndClass.lpszClassName = DefaultWindowClass.ClassName.c_str();
		DefaultWindowClass.WndClass.style = CS_HREDRAW | CS_VREDRAW;
		DefaultWindowClass.WndClass.lpfnWndProc = Static::WndProc;
		DefaultWindowClass.WndClass.cbClsExtra = 0;
		DefaultWindowClass.WndClass.cbWndExtra = 0;
		DefaultWindowClass.WndClass.hInstance = GetModuleHandle(nullptr);
		DefaultWindowClass.WndClass.hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ONYX32));
		DefaultWindowClass.WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		DefaultWindowClass.WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		DefaultWindowClass.WndClass.lpszMenuName = MAKEINTRESOURCE(IDC_ONYX32);
		DefaultWindowClass.WndClass.hIconSm = LoadIcon(DefaultWindowClass.WndClass.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		RegisterClassEx(&DefaultWindowClass.WndClass);

		created = true;
	}

	return DefaultWindowClass;
}
