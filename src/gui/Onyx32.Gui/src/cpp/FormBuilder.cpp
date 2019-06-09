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

	IWindow* FormBuilder::CreateDefaultWindow(std::wstring_view title, UINT width, UINT height)
	{
		if (width > 0 && height > 0)
			return new Window(WindowClassManager::GetDefaultWindowClass(), title, width, height);

		return new Window(WindowClassManager::GetDefaultWindowClass(), title);
	}

	IButton* FormBuilder::AddButton(IWindow* window, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos, std::function<void(void)>& onClick)
	{
		Button* button = new Button(text, width, height, onClick);
		window->AddControl(button, 100, 100);
		return button;
	}

	IInput* FormBuilder::AddTextInput(IWindow* window)
	{
		auto input = new Input();
		window->AddControl(input, 100, 100);
		return input;
	}

	FormBuilder::~FormBuilder() { }
}