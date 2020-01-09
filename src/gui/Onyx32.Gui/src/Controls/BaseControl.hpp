#pragma once
#include "../../include/Onyx32.Gui.hpp"
#include "../Win32/index.hpp"
#include <unordered_map>

namespace Onyx32::Gui::Controls
{
	template<typename ControlType>
	class BaseControl : public ControlType, public IMessageable
	{
		public:
			BaseControl(uint64_t id, ControlState state, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos, HWND wndHandle, IWindow* parent);
			virtual ~BaseControl();

			virtual HWND GetHwnd() const override;
			virtual uint64_t GetId() const override;
			virtual ControlState GetState() const override;
			virtual int GetStyles() const override;
			virtual const std::wstring& GetClass() const override;
			virtual void GetDimensions(Dimensions& dimensions) const override;
			virtual bool IsVisible() const override;

			virtual void SetEvent(ControlEvents evt, OnControlEvent&& evtHandler) override;
			virtual void SetVisibility(const bool isVisible) override;
			virtual void Resize(const unsigned int width, const unsigned int height) override;
			virtual void Move(const unsigned int xPos, const unsigned int yPos) override;

			virtual LRESULT Process(unsigned int message, WPARAM wParam, LPARAM lParam) override;

		protected:
			HWND _wndHandle;
			uint64_t const _controlId;
			unsigned int _width;
			unsigned int _height;
			unsigned int _xPos;
			unsigned int _yPos;
			bool _isVisible;
			bool _isEnabled;
			bool _hasFocus;
			ControlState _state;
			static const std::wstring Class;
			static const int Styles;
			std::unordered_map<ControlEvents, OnControlEvent> _eventHandlers;
			virtual void InvokeEvent(const ControlEvents evt);
			virtual void SetHwnd(HWND hWnd) override;
	};

	template<typename ControlType>
	BaseControl<ControlType>::BaseControl(uint64_t id, ControlState state, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos, HWND wndHandle, IWindow* parent)
		: _controlId(id), 
		_state(state), 
		_width(width), 
		_height(height), 
		_xPos(xPos), 
		_yPos(yPos), 
		_wndHandle(wndHandle),
		_isVisible(false),
		_isEnabled(false),
		_hasFocus(false)
	{}

	template<typename ControlType>
	void BaseControl<ControlType>::SetHwnd(HWND hWnd)
	{
		this->_wndHandle = hWnd;
		_state = ControlState::Initialized;
		_isVisible = true;
	}

	template<typename ControlType>
	BaseControl<ControlType>::~BaseControl()
	{
		if (_wndHandle && _state == ControlState::Initialized)
		{
			DestroyWindow(_wndHandle);
			_wndHandle = nullptr;
		}
	}

	template<typename ControlType>
	void BaseControl<ControlType>::InvokeEvent(const ControlEvents evt)
	{
		if (_state == ControlState::Initialized && _eventHandlers.count(evt))
			_eventHandlers[evt](evt, *this);
	}

	template<typename ControlType>
	void BaseControl<ControlType>::SetEvent(ControlEvents evt, OnControlEvent&& evtHandler)
	{
		_eventHandlers[evt] = std::move(evtHandler);
	}

	template<typename ControlType>
	void BaseControl<ControlType>::Move(const unsigned int xPos, const unsigned int yPos)
	{
		if (MoveWindow(_wndHandle, xPos, yPos, _width, _height, true))
		{
			_xPos = xPos;
			_yPos = yPos;
		}
	}

	template<typename ControlType>
	void BaseControl<ControlType>::GetDimensions(Dimensions& dimensions) const
	{
		dimensions.xPos = _xPos;
		dimensions.yPos = _yPos;
		dimensions.width = _width;
		dimensions.height = _height;
	}

	template<typename ControlType>
	bool BaseControl<ControlType>::IsVisible() const { return _isVisible; }

	template<typename ControlType>
	int BaseControl<ControlType>::GetStyles() const { return BaseControl<ControlType>::Styles; }

	template<typename ControlType>
	const std::wstring& BaseControl<ControlType>::GetClass() const { return BaseControl<ControlType>::Class; }

	template<typename ControlType>
	HWND BaseControl<ControlType>::GetHwnd() const { return _wndHandle; }

	template<typename ControlType>
	uint64_t BaseControl<ControlType>::GetId() const { return _controlId; }

	template<typename ControlType>
	ControlState BaseControl<ControlType>::GetState() const { return _state; }

	template<typename ControlType>
	void BaseControl<ControlType>::SetVisibility(const bool isVisible)
	{
		if (_state == ControlState::Initialized)
		{
			int value = isVisible ? SW_SHOW : SW_HIDE;
			ShowWindow(_wndHandle, value);
		}
	}

	template<typename ControlType>
	void BaseControl<ControlType>::Resize(const unsigned int width, const unsigned int height)
	{
		if (_state != ControlState::Initialized)
			return;

		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-movewindow
		if (MoveWindow(_wndHandle, _xPos, _yPos, width, height, true))
		{
			_width = width;
			_height = height;
		}
	}

	// This function is required because as the window is destroyed, WM_DESTROY and WM_NCDESTROY
	// are sent to the window and need to be processed. Because the call to DestroyWindow happens
	// at this class' level (see the destructor), Process() must be defined here as the subclass 
	// C++ object where Process is normally overridden has already been destructed.
	template<typename ControlType>
	LRESULT BaseControl<ControlType>::Process(unsigned int message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			// Sent to a window when the window is about to be hidden or shown.
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-showwindow
			case WM_SHOWWINDOW:
			{
				_isVisible = wParam;
				InvokeEvent(ControlEvents::OnVisibilityChanged);
				return 0;
			}

			// Window is being destroyed
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-destroy
			case WM_DESTROY:
			{
				InvokeEvent(ControlEvents::OnDestroy);
				return 0;
			}

			// Window has been moved
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-move
			case WM_MOVE:
			{
				_xPos = (int)(short)LOWORD(lParam);   // horizontal position 
				_yPos = (int)(short)HIWORD(lParam);   // vertical position 
				InvokeEvent(ControlEvents::OnMoved);
				return 0;
			}

			// Window has gained focus
			// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-setfocus
			case WM_SETFOCUS:
			{
				_hasFocus = true;
				InvokeEvent(ControlEvents::OnFocusChange);
				return 0;
			}

			// Window is about to lose focus
			// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-killfocus
			case WM_KILLFOCUS:
			{
				_hasFocus = false;
				InvokeEvent(ControlEvents::OnFocusChange);
				return 0;
			}

			// Window is being enabled or disabled
			// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-enable
			case WM_ENABLE:
			{
				_isEnabled = wParam;
				InvokeEvent(ControlEvents::OnEnabledChange);
				return 0;
			}

			default:
				return DefSubclassProc(_wndHandle, message, wParam, lParam);
		}
	}
}
