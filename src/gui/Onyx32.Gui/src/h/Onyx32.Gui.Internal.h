#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	class Win32ParentWindowCreationArgs
	{
		public:
			Win32ParentWindowCreationArgs(
				const DWORD extendedStyles,
				std::wstring_view windowName,
				const DWORD styles,
				const int x,
				const int y,
				const int width,
				const int height,
				const HWND parentOrOwner,
				const HMENU menu,
				const IWindow* window,
				const WNDCLASSEX& wndClass
			);

			const DWORD ExtendedStyles;
			const std::wstring WindowName;
			const DWORD Styles;
			const int X;
			const int Y;
			const int Width;
			const int Height;
			const HWND ParentOrOwner;
			const HMENU Menu;
			const IWindow* Window;
			const WNDCLASSEX& WndClass;
	};

	class Win32ChildWindowCreationArgs
	{
		public:
			Win32ChildWindowCreationArgs(
				const DWORD extendedStyles,
				std::wstring_view className,
				std::wstring_view windowName,
				const DWORD styles,
				const int x,
				const int y,
				const int width,
				const int height,
				const HWND parent,
				const HMENU menuOrId,
				const IControl* control,
				const SUBCLASSPROC subclassProc
			);

			const DWORD ExtendedStyles;
			const std::wstring ClassName;
			const std::wstring WindowName;
			const DWORD Styles;
			const int X;
			const int Y;
			const int Width;
			const int Height;
			const HWND Parent;
			const HMENU MenuOrId;
			const IControl* Control;
			const SUBCLASSPROC SubclassProc;
	};

	template<typename ControlType>
	class BaseControl : public ControlType
	{
		public:
			BaseControl(int id, ControlState state, UINT width, UINT height, UINT xPos, UINT yPos, HWND wndHandle, IWindow* parent);
			virtual ~BaseControl();

			virtual HWND GetHwnd() override;
			virtual UINT GetId() override;
			virtual ControlState GetState() override;
			virtual int GetStyles() override;
			virtual const std::wstring& GetClass() override;
			virtual void GetDimensions(Dimensions& dimensions) override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;

			virtual void SetParent(IWindow* parent);
			virtual void Resize(const UINT width, const UINT height) override;
			virtual void Move(const UINT xPos, const UINT yPos) override;

		protected:
			HWND _wndHandle;
			IWindow* _parent;
			unsigned int const _controlId;
			UINT _width;
			UINT _height;
			UINT _xPos;
			UINT _yPos;
			ControlState _state;
			static const std::wstring Class;
			static const int Styles;
	};

	template<typename ControlType>
	void BaseControl<ControlType>::Move(const UINT xPos, const UINT yPos)
	{
		if (MoveWindow(_wndHandle, xPos, yPos, _width, _height, true))
		{
			_xPos = xPos;
			_yPos = yPos;
		}
	}

	template<typename ControlType>
	void BaseControl<ControlType>::GetDimensions(Dimensions& dimensions)
	{
		dimensions.xPos = _xPos;
		dimensions.yPos = _yPos;
		dimensions.width = _width;
		dimensions.height = _height;
	}

	template<typename ControlType>
	BaseControl<ControlType>::BaseControl(int id, ControlState state, UINT width, UINT height, UINT xPos, UINT yPos, HWND wndHandle, IWindow* parent)
		: _controlId(id), _state(state), _width(width), _height(height), _xPos(xPos), _yPos(yPos), _wndHandle(wndHandle), _parent(parent) {}

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
	int BaseControl<ControlType>::GetStyles()
	{
		return BaseControl<ControlType>::Styles;
	}

	template<typename ControlType>
	const std::wstring& BaseControl<ControlType>::GetClass()
	{
		return BaseControl<ControlType>::Class;
	}

	template<typename ControlType>
	HWND BaseControl<ControlType>::GetHwnd()
	{
		return _wndHandle;
	}

	template<typename ControlType>
	void BaseControl<ControlType>::SetParent(IWindow* parent)
	{
		_parent = parent;
	}

	template<typename ControlType>
	UINT BaseControl<ControlType>::GetId()
	{
		return _controlId;
	}

	template<typename ControlType>
	ControlState BaseControl<ControlType>::GetState()
	{
		return _state;
	}

	template<typename ControlType>
	void BaseControl<ControlType>::Resize(const UINT width, const UINT height)
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
	LRESULT BaseControl<ControlType>::Process(UINT message, WPARAM wParam, LPARAM lParam)
	{
		return DefSubclassProc(_wndHandle, message, wParam, lParam);
	}
}
