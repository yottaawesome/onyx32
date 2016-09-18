#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "../h/FormBuilder.h"
#include "../h/Window.h"
#include "../h/Button.h"
#include "../h/StaticFunctions.h"

namespace Onyx32::Gui
{
	FormBuilder::FormBuilder() { }

	IWindow* FormBuilder::CreateMainWindow(wstring& title, unsigned int width, unsigned int height)
	{
		if (width > 0 && height > 0)
			return new Window(title, GetModuleHandle(nullptr), width, height);

		return new Window(title, GetModuleHandle(nullptr));
	}

	IWindow* FormBuilder::CreateMainWindow(wstring&& title, unsigned int width, unsigned int height)
	{
		if (width > 0 && height > 0)
			return new Window(title, GetModuleHandle(nullptr), width, height);

		return new Window(title, GetModuleHandle(nullptr));
	}

	void FormBuilder::AddButton(IWindow* window, wstring& text, function<void(void)>& onClick, unsigned int width, unsigned int height)
	{
		Button* button = new Button(0, text, onClick, width, height);
		window->AddControl(button);
	}

	void FormBuilder::AddButton(IWindow* window, wstring&& text, function<void(void)>& onClick, unsigned int width, unsigned int height)
	{
		Button* button = new Button(0, text, onClick, width, height);
		window->AddControl(button);
	}

	FormBuilder::~FormBuilder() { }
}