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
				const UINT width = CW_USEDEFAULT,
				const UINT height = CW_USEDEFAULT,
				const UINT xPos = CW_USEDEFAULT,
				const UINT yPos = CW_USEDEFAULT);
			Window(
				const WindowClass& wcex, 
				std::wstring_view title,
				const int customStyle,
				const UINT width = CW_USEDEFAULT,
				const UINT height = CW_USEDEFAULT,
				const UINT xPos = CW_USEDEFAULT,
				const UINT yPos = CW_USEDEFAULT);
			virtual ~Window();

			virtual HWND GetHwnd() const override;
			virtual WindowDisplayState GetDisplayState() const override;
			virtual int GetStyles() const override;
			virtual const std::wstring& GetTitle() const override;
			virtual bool IsActive() const override;
			virtual void GetDimensions(Dimensions& dimensions) const override;

			virtual void SetHwnd(HWND hWnd);
			virtual void SetTitle(std::wstring_view title) override;
			virtual void SetVisibility(const bool isVisible) override;
			virtual void SetDisplayState(const WindowDisplayState state) override;
			virtual void SetWindowEvent(WindowEvents evt, OnWindowEvent&& evtHandler) override;

			virtual void Initialize() override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;

			virtual void Resize(const UINT width, const UINT height) override;
			virtual void AddControl(IControl* const control) override;
			virtual void DestroyControl(IControl* const control) override;
			virtual void Move(const UINT xPos, const UINT yPos) override;
			virtual void RequestFocus() override;

		protected:
			void InvokeEvent(const WindowEvents evt);

			const WindowClass _windowClass;
			WindowDisplayState _displayState;

			WindowState _windowState;
			HWND _wndHandle;
			std::wstring _title = L"Default";
			UINT _width;
			UINT _height;
			UINT _xPos;
			UINT _yPos;
			bool _isVisible;
			std::unordered_map<IControl*, std::shared_ptr<IControl>> _children;
			const int _styles;
			std::unordered_map<WindowEvents, OnWindowEvent> _eventHandlers;
			bool _isActive;
	};
}
