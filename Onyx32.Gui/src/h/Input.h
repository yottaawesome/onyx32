#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "Window.h"

namespace Onyx32::Gui
{
	class Input : public IInput
	{
		public:
			virtual void Initialize(IWindow* window) override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			virtual void SetHwnd(HWND hWnd) override;
			virtual HWND GetHwnd() override;
			virtual ~Input() override;
			virtual wstring GetText() override;
			virtual void SetText(wstring* str) override;
			virtual void SetText(wstring&& str) override;
		
		protected:
			wstring text;
			HWND hwndEdit;
			IWindow* parent;
	};
}