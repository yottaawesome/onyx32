#pragma once
#include <string>
#include "../../include/Onyx32.Gui.h"

using namespace std;

namespace Onyx32::Gui
{
	class Window : public IWindow
	{
		public:
			ONYXWINDOWING_API Window(wstring& title, HINSTANCE hInstance, unsigned int width = CW_USEDEFAULT, unsigned int height = 0);
			ONYXWINDOWING_API Window(wstring&& title, HINSTANCE hInstance, unsigned int width = CW_USEDEFAULT, unsigned int height = 0);

			ONYXWINDOWING_API virtual void Initialize() override;
			ONYXWINDOWING_API virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			ONYXWINDOWING_API virtual void SetHwnd(HWND hWnd) override;
			ONYXWINDOWING_API virtual HWND GetHwnd() override;

			ONYXWINDOWING_API virtual void SetTitle(wstring&& title) override;
			ONYXWINDOWING_API virtual void SetTitle(wstring& title) override;

			ONYXWINDOWING_API virtual void AddControl(IControl* control) override;

		private:
			HWND hWnd;
			HINSTANCE hInstance;
			//IWin32Application* application;
			//TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
			//TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
			wstring title = L"Default";
			unsigned int width;
			unsigned int height;
	};
}
