#pragma once
#include "../h/stdafx.h"
#include "../h/Onyx32.Gui.internal.h"
#include <string>

namespace Onyx32::Gui
{
	class Button : public BaseControl<IButton>
	{
		public:
			Button(
				std::wstring_view text = L"Default",
				const UINT width = 100,
				const UINT height = 100,
				FunctionHandler& onClick = Button::DefaultClickHandler,
				const unsigned int controlId = 0);
			virtual ~Button();

			virtual void Initialize(IWindow* parent) override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			virtual const std::wstring& GetText() override;
			virtual void SetClickHandler(FunctionHandler& onClick);
			virtual void Resize(const UINT width, const UINT height);
			
		protected:
			std::wstring _text;
			//void (*onClick)();
			FunctionHandler& _onClick;
			static FunctionHandler DefaultClickHandler;
	};
}