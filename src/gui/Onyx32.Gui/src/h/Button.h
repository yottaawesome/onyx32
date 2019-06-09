#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include <string>

namespace Onyx32::Gui
{
	class Button : public IButton
	{
		public:
			Button(
				std::wstring_view text = L"Default",
				const UINT width = 100,
				const UINT height = 100,
				FunctionHandler& onClick = Button::DefaultClickHandler,
				const unsigned int controlId = 0);

			virtual void Initialize(IWindow* parent) override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			virtual void SetHwnd(HWND hWnd) override;
			virtual HWND GetHwnd() override;
			virtual void SetParent(IWindow* parent);
			virtual UINT GetWidth() override;
			virtual UINT GetHeight() override;
			virtual const std::wstring& GetText() override;
			virtual UINT GetId() override;
			virtual void SetClickHandler(FunctionHandler& onClick);
			//virtual void Resize(const UINT);

			virtual ~Button();

		protected:
			HWND _wndHandle;
			IWindow* _parent;
			std::wstring _text;
			unsigned int const _controlId;
			unsigned int _width;
			unsigned int _height;
			//void (*onClick)();
			FunctionHandler& _onClick;
			static FunctionHandler DefaultClickHandler;
	};
}