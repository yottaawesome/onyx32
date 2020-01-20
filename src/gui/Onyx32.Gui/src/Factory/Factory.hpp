#pragma once
#include "../../include/Onyx32.Gui.hpp"

namespace Onyx32::Gui
{
	class Factory : public IFactory
	{
		public:
			Factory();
			virtual ~Factory();
			virtual IMainLoop* CreateMainLoop() override;
			virtual IWindow* CreateOnyxWindow(std::wstring_view title, const int styles, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos) override;
			virtual Controls::IDateTime* CreateDateTime(IWindow* parent, unsigned int controlId, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos) override;
			virtual Controls::ITextInput* CreateTextInput(IWindow* parent, unsigned int controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos) override;
			virtual Controls::IButton* CreateButton(IWindow* parent, unsigned int controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos) override;
			virtual void Destroy();
	};
}
