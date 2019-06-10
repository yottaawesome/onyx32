#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	template<typename ControlType>
	class BaseControl : public ControlType
	{
		public:
			BaseControl(int id, UINT width, UINT height, HWND wndHandle, IWindow* parent);
			virtual ~BaseControl();
			virtual void SetHwnd(HWND hWnd) override;
			virtual HWND GetHwnd() override;
			virtual UINT GetWidth() override;
			virtual UINT GetHeight() override;
			virtual UINT GetId() override;
			virtual void SetParent(IWindow* parent);
			//virtual const std::wstring& GetName() = 0;
			//virtual int GetStyles() = 0;
		protected:
			HWND _wndHandle;
			IWindow* _parent;
			unsigned int const _controlId;
			unsigned int _width;
			unsigned int _height;
	};

	template<typename ControlType>
	BaseControl<ControlType>::BaseControl(int id, UINT width, UINT height, HWND wndHandle, IWindow* parent) 
		: _controlId(id), _width(width), _height(height), _wndHandle(wndHandle), _parent(parent) {}

	template<typename ControlType>
	BaseControl<ControlType>::~BaseControl() {}

	template<typename ControlType>
	void BaseControl<ControlType>::SetHwnd(HWND hWnd)
	{
		_wndHandle = hWnd;
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
	void BaseControl<ControlType>::SetParent(IWindow* parent)
	{
		_parent = parent;
	}

	template<typename ControlType>
	UINT BaseControl<ControlType>::GetId()
	{
		return _controlId;
	}
}
