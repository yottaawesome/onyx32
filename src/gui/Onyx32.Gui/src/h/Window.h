#pragma once
#include <string>
#include "../../include/Onyx32.Gui.h"
#include "../h/WindowClassManager.h"

using namespace std;

namespace Onyx32::Gui
{
	class Window : public IWindow
	{
		public:
			Window(wstring& title, unsigned int width = CW_USEDEFAULT, unsigned int height = 0);
			Window(wstring&& title, unsigned int width = CW_USEDEFAULT, unsigned int height = 0);

			virtual void Initialize() override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			virtual void SetHwnd(HWND hWnd) override;
			virtual HWND GetHwnd() override;

			virtual void SetTitle(wstring&& title) override;
			virtual void SetTitle(wstring& title) override;
			virtual wstring& GetTitle() override;
			
			virtual UINT GetWidth() override;
			virtual UINT GetHeight() override;

			virtual void AddControl(IControl* control, unsigned int xPos, unsigned int yPos) override;

			virtual WindowClass GetWndClass();

		private:
			HWND hWnd;
			wstring title = L"Default";
			unsigned int width;
			unsigned int height;
			WindowClass wcex;
	};
}
