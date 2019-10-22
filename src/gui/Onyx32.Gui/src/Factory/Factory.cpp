#include "../h/stdafx.h"
#include "Factory.h"
#include "../Application/Application.h"
#include "../Window/Window.h"
#include "../Controls/Button/Button.h"
#include "../Controls/DateTime/DateTime.h"
#include "../Controls/TextInput/TextInput.h"

namespace Onyx32::Gui
{
	Factory::Factory() { }

	Factory::~Factory() { }

	IApplication* Factory::GetApplication()
	{
		return new Application();
	}

	IWindow* Factory::CreateDefaultWindow(std::wstring_view title, unsigned int width, unsigned int height)
	{
		if (width > 0 && height > 0)
			return new Window(WindowClassManager::GetDefaultWindowClass(), title, width, height);

		return new Window(WindowClassManager::GetDefaultWindowClass(), title);
	}

	IWindow* Factory::CreateStyledWindow(std::wstring_view title, const int styles, unsigned int width, unsigned int height)
	{
		if (width > 0 && height > 0)
			return new Window(WindowClassManager::GetDefaultWindowClass(), title, styles, width, height);

		return new Window(WindowClassManager::GetDefaultWindowClass(), title);
	}

	ITextInput* Factory::CreateTextInput(IWindow* parent, unsigned int controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos)
	{
		auto control = TextInput::Create(parent, controlId, text, width, height, xPos, yPos);
		parent->AddControl(control);
		return control;
	}

	IDateTime* Factory::CreateDateTime(IWindow* parent, unsigned int controlId, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos)
	{
		auto control = DateTime::Create(parent, controlId, width, height, xPos, yPos);
		parent->AddControl(control);
		return control;
	}

	IButton* Factory::CreateButton(IWindow* parent, unsigned int controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos)
	{
		auto control = Button::Create(parent, controlId, text, width, height, xPos, yPos);
		parent->AddControl(control);
		return control;
	}
}
