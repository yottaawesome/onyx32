#pragma once
#include <string>
#include "../../include/Onyx32.Gui.hpp"
#include "../Win32/index.hpp"
#include <vector>
#include <unordered_map>

namespace Onyx32::Gui::Window
{
	// https://docs.microsoft.com/en-us/windows/desktop/winmsg/windows
	// https://docs.microsoft.com/en-us/windows/desktop/winmsg/about-window-classes
	// https://docs.microsoft.com/en-us/windows/desktop/api/commctrl/nf-commctrl-setwindowsubclass
	// https://docs.microsoft.com/en-us/windows/desktop/winmsg/using-windows
	class Window : public IWindow, public Onyx32::Gui::Win32::IMessageable
	{
		public:
			Window(
				std::wstring_view title,
				const unsigned int width = CW_USEDEFAULT,
				const unsigned int height = CW_USEDEFAULT,
				const unsigned int xPos = CW_USEDEFAULT,
				const unsigned int yPos = CW_USEDEFAULT);
			Window(
				std::wstring_view title,
				const int customStyle,
				const unsigned int width = CW_USEDEFAULT,
				const unsigned int height = CW_USEDEFAULT,
				const unsigned int xPos = CW_USEDEFAULT,
				const unsigned int yPos = CW_USEDEFAULT);
			virtual ~Window();

			virtual HWND GetHwnd() const override;
			virtual WindowDisplayState GetDisplayState() const override;
			virtual int GetStyles() const override;
			virtual const std::wstring& GetTitle() const override;
			virtual bool IsActive() const override;
			virtual void GetDimensions(Dimensions& dimensions) const override;
			virtual bool HasFocus() const override;
			virtual bool IsVisible() const override;
			virtual bool IsEnabled() const override;

			virtual void SetHwnd(HWND hWnd) override;
			virtual void SetTitle(std::wstring_view title) override;
			virtual void SetVisibility(const bool isVisible) override;
			virtual void SetDisplayState(const WindowDisplayState state) override;
			virtual void SetEvent(WindowEvents evt, OnWindowEvent&& evtHandler) override;
			virtual void SetEnabled(const bool isEnabled);

			virtual void Initialize() override;
			virtual LRESULT Process(unsigned int message, WPARAM wParam, LPARAM lParam) override;

			virtual void Resize(const unsigned int width, const unsigned int height) override;
			virtual void AddControl(Onyx32::Gui::Controls::IControl* const control) override;
			virtual void DestroyControl(Onyx32::Gui::Controls::IControl* const control) override;
			virtual void Move(const unsigned int xPos, const unsigned int yPos) override;
			virtual void RequestFocus() override;
			virtual void Destroy();

		protected:
			virtual void InvokeEvent(const WindowEvents evt);

			WindowDisplayState _displayState;

			WindowState _windowState;
			HWND _wndHandle;
			std::wstring _title = L"Default";
			unsigned int _width;
			unsigned int _height;
			unsigned int _xPos;
			unsigned int _yPos;
			bool _isVisible;
			bool _isBeingResized;
			bool _hasFocus;
			bool _isEnabled;
			std::unordered_map<Onyx32::Gui::Controls::IControl*, std::shared_ptr<Onyx32::Gui::Controls::IControl>> _children;
			const int _styles;
			std::unordered_map<WindowEvents, OnWindowEvent> _eventHandlers;
			bool _isActive;
	};

	IWindow* CreateOnyxWindow(
		const Onyx32::Gui::Win32::WindowClass& wndClass,
		const std::wstring_view title,
		const int customStyle,
		const unsigned int width,
		const unsigned int height,
		const unsigned int xPos,
		const unsigned int yPos);
}
