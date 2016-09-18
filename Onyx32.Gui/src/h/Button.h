#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	class Button : public IButton
	{
	public:
		ONYXWINDOWING_API Button(unsigned int controlId, wstring& text, FunctionHandler& onClick, unsigned int width, unsigned int height);

		ONYXWINDOWING_API virtual void Initialize(IWindow* parent) override;
		ONYXWINDOWING_API virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
		ONYXWINDOWING_API virtual void SetHwnd(HWND hWnd) override;
		ONYXWINDOWING_API virtual HWND GetHwnd() override;

		ONYXWINDOWING_API virtual ~Button();

	protected:
		HWND hwndButton;
		IWindow* parent;
		wstring text;
		unsigned int const controlId;
		unsigned int width;
		unsigned int height;
		//void (*onClick)();
		FunctionHandler& onClick;
	};
}