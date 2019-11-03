#pragma once
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	class Factory : public IFactory
	{
		public:
			Factory();
			virtual ~Factory();
			virtual IApplication* GetApplication() override;
			virtual IWindow* CreateDefaultWindow(std::wstring_view title, unsigned int width = 0, unsigned int height = 0) override;
			virtual IWindow* CreateStyledWindow(std::wstring_view title, const int styles, unsigned int width = 0, unsigned int height = 0) override;
			virtual Onyx32::Gui::Controls::IDateTime* CreateDateTime(IWindow* parent, unsigned int controlId, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos) override;
			virtual Onyx32::Gui::Controls::ITextInput* CreateTextInput(IWindow* parent, unsigned int controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos) override;
			virtual Onyx32::Gui::Controls::IButton* CreateButton(IWindow* parent, unsigned int controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos) override;
	};
}
