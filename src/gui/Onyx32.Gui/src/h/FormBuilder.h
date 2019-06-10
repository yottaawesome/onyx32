#pragma once
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	class FormBuilder : public IFormBuilder
	{
	public:
		FormBuilder();
		virtual IWindow* CreateDefaultWindow(std::wstring_view title, UINT width = 0, UINT height = 0) override;
		virtual IButton* AddButton(IWindow* window, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos, std::function<void(void)>& onClick) override;
		virtual ITextInput* AddTextInput(IWindow* window, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos) override;

		virtual ~FormBuilder();
	};
}
