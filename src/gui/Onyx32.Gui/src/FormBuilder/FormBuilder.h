#pragma once
#include "../h/Onyx32.Gui.internal.h"

namespace Onyx32::Gui
{
	class FormBuilder : public IFormBuilder
	{
		public:
			FormBuilder();
			virtual ~FormBuilder();

			virtual IWindow* CreateDefaultWindow(std::wstring_view title, UINT width = 0, UINT height = 0) override;
			virtual IDateTime* CreateDateTime(UINT controlId, UINT width, UINT height, UINT xPos, UINT yPos) override;
			virtual ITextInput* CreateTextInput(UINT controlId, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos) override;
			virtual IButton* CreateButton(UINT controlId, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos) override;
	};
}
