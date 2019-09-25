#pragma once
#include "../h/Onyx32.Gui.Internal.h"

namespace Onyx32::Gui
{
	class Factory : public IFactory
	{
		public:
			Factory();
			virtual ~Factory();
			virtual IApplication* GetApplication() override;
			virtual IWindow* CreateDefaultWindow(std::wstring_view title, UINT width = 0, UINT height = 0) override;
			virtual IWindow* CreateStyledWindow(std::wstring_view title, const int styles, UINT width = 0, UINT height = 0) override;
			virtual IDateTime* CreateDateTime(UINT controlId, UINT width, UINT height, UINT xPos, UINT yPos) override;
			virtual ITextInput* CreateTextInput(UINT controlId, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos) override;
			virtual IButton* CreateButton(IWindow* parent, UINT controlId, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos) override;
	};
}
