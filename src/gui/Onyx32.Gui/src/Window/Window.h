#pragma once
#include <string>
#include "../h/Onyx32.Gui.internal.h"
#include "../WindowClassManager/WindowClassManager.h"
#include <vector>
#include "../h/ControlInfo.h"
#include <map>

namespace Onyx32::Gui
{
	class Window : public IWindow
	{
		public:
			Window(const WindowClass& wcex, wstring_view title, unsigned int width = CW_USEDEFAULT, unsigned int height = 0);
			virtual ~Window();

			virtual void Initialize() override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			virtual void SetHwnd(HWND hWnd) override;
			virtual HWND GetHwnd() override;

			virtual void SetTitle(wstring_view title) override;
			virtual wstring& GetTitle() override;
			
			virtual UINT GetWidth() override;
			virtual UINT GetHeight() override;

			virtual void AddControl(IControl& control, UINT xPos, UINT yPos) override;

			const WindowClass WndClass;

		protected:
			HWND _hWnd;
			wstring _title = L"Default";
			unsigned int _width;
			unsigned int _height;
			std::map<IControl*, ControlInfo*> _children;
	};
}
