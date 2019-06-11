#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	template<typename ControlType>
	class BaseControl : public ControlType
	{
		public:
			BaseControl(int id, ControlState state, UINT width, UINT height, UINT xPos, UINT yPos, HWND wndHandle, IWindow* parent);
			virtual ~BaseControl();
			virtual void SetHwnd(HWND hWnd) override;
			virtual HWND GetHwnd() override;
			virtual UINT GetWidth() override;
			virtual UINT GetHeight() override;
			virtual UINT GetXPos() override;
			virtual UINT GetYPos() override;
			virtual UINT GetId() override;
			virtual ControlState GetState();
			virtual void SetParent(IWindow* parent);
			virtual const std::wstring& GetName();
			virtual int GetStyles();
			virtual const std::wstring& GetCreateWindowText() = 0;

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
	BaseControl<ControlType>::BaseControl(int id, ControlState state, UINT width, UINT height, UINT xPos, UINT yPos, HWND wndHandle, IWindow* parent)
		: _controlId(id), _state(state), _width(width), _height(height), _xPos(xPos), _yPos(yPos), _wndHandle(wndHandle), _parent(parent) {}

	template<typename ControlType>
	BaseControl<ControlType>::~BaseControl()
	{
		if (_wndHandle)
		{
			DestroyWindow(_wndHandle);
			_wndHandle = nullptr;
		}
	}

	template<typename ControlType>
	void BaseControl<ControlType>::SetHwnd(HWND hWnd)
	{
		_wndHandle = hWnd;
	}

	template<typename ControlType>
	int BaseControl<ControlType>::GetStyles()
	{
		return BaseControl<ControlType>::Styles;
	}

	template<typename ControlType>
	const std::wstring& BaseControl<ControlType>::GetName()
	{
		return BaseControl<ControlType>::Class;
	}

	template<typename ControlType>
	HWND BaseControl<ControlType>::GetHwnd()
	{
		return _wndHandle;
	}

	template<typename ControlType>
	UINT BaseControl<ControlType>::GetWidth()
	{
		return _width;
	}

	template<typename ControlType>
	UINT BaseControl<ControlType>::GetHeight()
	{
		return _height;
	}

	template<typename ControlType>
	UINT BaseControl<ControlType>::GetXPos()
	{
		return _xPos;
	}

	template<typename ControlType>
	UINT BaseControl<ControlType>::GetYPos()
	{
		return _yPos;
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

}
