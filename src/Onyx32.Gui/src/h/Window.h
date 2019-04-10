#pragma once
#include <string>
#include "../../include/Onyx32.Gui.h"

using namespace std;

namespace Onyx32::Gui
{
	class Window : public IWindow
	{
		public:
			Window(wstring& title, HINSTANCE hInstance, unsigned int width = CW_USEDEFAULT, unsigned int height = 0);
			Window(wstring&& title, HINSTANCE hInstance, unsigned int width = CW_USEDEFAULT, unsigned int height = 0);

			virtual void Initialize() override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			virtual void SetHwnd(HWND hWnd) override;
			virtual HWND GetHwnd() override;

			virtual void SetTitle(wstring&& title) override;
			virtual void SetTitle(wstring& title) override;

			virtual void AddControl(IControl* control) override;

		private:
			HWND hWnd;
			HINSTANCE hInstance;
			wstring title = L"Default";
			unsigned int width;
			unsigned int height;
	};
}
