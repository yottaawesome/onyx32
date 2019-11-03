#pragma once
#include "../BaseControl.h"
#include <string>
#include <unordered_map>

namespace Onyx32::Gui::Controls
{
	class Button : public BaseControl<IButton>
	{
		public:
			Button() = delete;
			virtual ~Button();

			virtual const std::wstring& GetText() const override;

			virtual void SetText(std::wstring_view str) override;
			virtual void Initialize() override;
			virtual LRESULT Process(unsigned int message, WPARAM wParam, LPARAM lParam) override;
			virtual void SetEvent(ButtonEvents evt, OnButtonEvent&& evtHandler) override;

			static IButton* Create(IWindow* parent, uint64_t controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos);

		protected:
			Button(
				std::wstring_view text = L"Default",
				const unsigned int width = 100,
				const unsigned int height = 100,
				const unsigned int xPos = 100,
				const unsigned int yPos = 100,
				const uint64_t controlId = 0);

			std::wstring _text;
			std::unordered_map<ButtonEvents, OnButtonEvent> _buttonEventHandlers;
			virtual void InvokeEvent(const ButtonEvents evt);
	};
}