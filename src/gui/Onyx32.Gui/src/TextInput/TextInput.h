#pragma once
#include "../h/Onyx32.Gui.internal.h"
#include "../Window/Window.h"
#include <string>

namespace Onyx32::Gui
{
	class TextInput : public BaseControl<ITextInput>
	{
		public:
			TextInput(
				std::wstring_view text = L"",
				const UINT width = 100,
				const UINT height = 100,
				const UINT xPos = 100,
				const UINT yPos = 100,
				const unsigned int controlId = 0);
			virtual ~TextInput();

			virtual void Initialize(IWindow* window) override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			virtual const std::wstring GetText() override;
			virtual void SetText(std::wstring_view str) override;

		protected:
			std::wstring _text;
	};
}