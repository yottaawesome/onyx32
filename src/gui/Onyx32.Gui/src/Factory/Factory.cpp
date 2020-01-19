#include "../stdafx.h"
#include "Factory.hpp"
#include "../MainLoop/MainLoop.hpp"
#include "../Window/Window.hpp"
#include "../Controls/index.hpp"

namespace Onyx32::Gui
{
	Factory::Factory() { }

	Factory::~Factory() { }

	IMainLoop* Factory::CreateMainLoop()
	{
		return new MainLoop();
	}

	IWindow* Factory::CreateDefaultWindow(std::wstring_view title, unsigned int width, unsigned int height)
	{
		if (width > 0 && height > 0)
			return new Window(Onyx32::Gui::Win32::GetDefaultWindowClass(), title, width, height);

		return new Window(Onyx32::Gui::Win32::GetDefaultWindowClass(), title);
	}

	IWindow* Factory::CreateStyledWindow(std::wstring_view title, const int styles, unsigned int width, unsigned int height)
	{
		if (width > 0 && height > 0)
			return new Window(Onyx32::Gui::Win32::GetDefaultWindowClass(), title, styles, width, height);

		return new Window(Onyx32::Gui::Win32::GetDefaultWindowClass(), title);
	}

	Onyx32::Gui::Controls::ITextInput* Factory::CreateTextInput(IWindow* parent, unsigned int controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos)
	{
		auto control = Onyx32::Gui::Controls::TextInput::Create(parent, controlId, text, width, height, xPos, yPos);
		parent->AddControl(control);
		return control;
	}

	Onyx32::Gui::Controls::IDateTime* Factory::CreateDateTime(IWindow* parent, unsigned int controlId, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos)
	{
		auto control = Onyx32::Gui::Controls::DateTime::Create(parent, controlId, width, height, xPos, yPos);
		parent->AddControl(control);
		return control;
	}

	Onyx32::Gui::Controls::IButton* Factory::CreateButton(IWindow* parent, unsigned int controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos)
	{
		auto control = Onyx32::Gui::Controls::Button::Create(parent, controlId, text, width, height, xPos, yPos);
		parent->AddControl(control);
		return control;
	}

	void Factory::Destroy()
	{
		delete this;
	}
}
