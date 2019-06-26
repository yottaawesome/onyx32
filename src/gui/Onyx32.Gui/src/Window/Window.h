#pragma once
#include <string>
#include "../h/Onyx32.Gui.internal.h"
#include "../WindowClassManager/WindowClassManager.h"
#include <vector>
#include "../h/ControlInfo.h"
#include <unordered_map>

namespace Onyx32::Gui
{
	// https://docs.microsoft.com/en-us/windows/desktop/winmsg/windows
	// https://docs.microsoft.com/en-us/windows/desktop/winmsg/about-window-classes
	// https://docs.microsoft.com/en-us/windows/desktop/api/commctrl/nf-commctrl-setwindowsubclass
	// https://docs.microsoft.com/en-us/windows/desktop/winmsg/using-windows
	class Window : public IWindow
	{
		public:
			Window(
				const WindowClass& wcex,
				std::wstring_view title,
				UINT width = CW_USEDEFAULT,
				UINT height = CW_USEDEFAULT,
				UINT xPos = CW_USEDEFAULT,
				UINT yPos = CW_USEDEFAULT);
			Window(
				const WindowClass& wcex, 
				std::wstring_view title,
				const int customStyle,
				UINT width = CW_USEDEFAULT, 
				UINT height = CW_USEDEFAULT,
				UINT xPos = CW_USEDEFAULT,
				UINT yPos = CW_USEDEFAULT);
			virtual ~Window();

			virtual void Initialize() override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			virtual void SetHwnd(HWND hWnd);
			virtual HWND GetHwnd() override;

			virtual void SetTitle(std::wstring_view title) override;
			virtual const std::wstring& GetTitle() override;
			
			virtual UINT GetWidth() override;
			virtual UINT GetHeight() override;
			virtual void Resize(const UINT width, const UINT height) override;
			virtual void AddControl(IControl* control) override;
			virtual void DestroyControl(IControl* control) override;

			virtual void SetOnActivate(OnWindowActivateChange&& evtHandler) override;
			virtual void SetOnResized(OnWindowResized&& evtHandler) override;

		protected:
			const WindowClass WndClass;

			OnWindowActivateChange _activateEvtHandler;
			int OnActivate(bool isActive);
			OnWindowResized _onResized;
			int OnResizing(WindowResizeState operation);
			int OnBeginUserResize();
			int OnEndUserResize();

			//WindowResizeOperation _current
			HWND _wndHandle;
			std::wstring _title = L"Default";
			UINT _width;
			UINT _height;
			UINT _xPos;
			UINT _yPos;
			std::unordered_map<IControl*, std::shared_ptr<IControl>> _children;
			const int _styles;
	};
}
