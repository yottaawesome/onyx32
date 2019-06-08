#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "../h/FormBuilder.h"
#include "../h/Window.h"
#include "../h/Button.h"
#include "../h/Input.h"
#include "../h/DllMain.h"
#include "../h/StaticFunctions.h"

namespace Onyx32::Gui
{
	FormBuilder::FormBuilder() { }

	IWindow* FormBuilder::CreateMainWindow(std::wstring_view title, unsigned int width, unsigned int height)
	{
		if (width > 0 && height > 0)
			return new Window(std::wstring(title), width, height);

		return new Window(std::wstring(title));
	}

	void FormBuilder::AddButton(IWindow* window, std::wstring& text, function<void(void)>& onClick, unsigned int width, unsigned int height)
	{
		Button* button = new Button(0, text, onClick, width, height);
		window->AddControl(button, 100, 100);
	}

	void FormBuilder::AddButton(IWindow* window, std::wstring&& text, function<void(void)>& onClick, unsigned int width, unsigned int height)
	{
		Button* button = new Button(0, text, onClick, width, height);
		window->AddControl(button, 100, 100);
	}

	IInput* FormBuilder::AddTextInput(IWindow* window)
	{
		auto input = new Input();
		window->AddControl(input, 100, 100);
		return input;
	}

	FormBuilder::~FormBuilder() { }
}