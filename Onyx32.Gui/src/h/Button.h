#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	class Button : public IButton
	{
	public:
		Button(unsigned int controlId, wstring& text, FunctionHandler& onClick, unsigned int width, unsigned int height);

		virtual void Initialize(IWindow* parent) override;
		 virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
		 virtual void SetHwnd(HWND hWnd) override;
		 virtual HWND GetHwnd() override;

		 virtual ~Button();

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