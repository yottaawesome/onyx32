#pragma once
#include "../../h/Onyx32.Gui.internal.h"
#include <string>
#include <unordered_map>

namespace Onyx32::Gui
{
	class Button : public BaseControl<IButton>
	{
		public:
			Button(
				std::wstring_view text = L"Default",
				const UINT width = 100,
				const UINT height = 100,
				const UINT xPos = 100,
				const UINT yPos = 100,
				const unsigned int controlId = 0);
			virtual ~Button();

			virtual const std::wstring& GetText() const override;

			virtual void SetText(std::wstring_view str) override;
			virtual void Initialize(IWindow* parent) override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			virtual void SetEvent(ButtonEvents evt, OnButtonEvent&& evtHandler) override;

		protected:
			std::wstring _text;
			std::unordered_map<ButtonEvents, OnButtonEvent> _buttonEventHandlers;
			virtual void InvokeEvent(const ButtonEvents evt);
	};
}