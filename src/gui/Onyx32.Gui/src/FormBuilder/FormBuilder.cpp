#include "../h/stdafx.h"
#include "FormBuilder.h"
#include "../Window/Window.h"
#include "../Button/Button.h"
#include "../DateTime/DateTime.h"
#include "../TextInput/TextInput.h"
#include "../h/DllMain.h"
#include "../h/StaticFunctions.h"

namespace Onyx32::Gui
{
	FormBuilder::FormBuilder() { }
	FormBuilder::~FormBuilder() { }

	IWindow* FormBuilder::CreateDefaultWindow(std::wstring_view title, UINT width, UINT height)
	{
		if (width > 0 && height > 0)
			return new Window(WindowClassManager::GetDefaultWindowClass(), title, width, height);

		return new Window(WindowClassManager::GetDefaultWindowClass(), title);
	}

	IButton* FormBuilder::AddButton(IWindow& window, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos)
	{
		Button* button = new Button(text, width, height, xPos, yPos);
		window.AddControl(*button);
		return button;
	}

	ITextInput* FormBuilder::AddTextInput(IWindow& window, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos)
	{
		ITextInput* input = new TextInput(text, width, height, xPos, yPos, 100);
		window.AddControl(*input);
		return input;
	}

	IDateTime* FormBuilder::AddDateTime(IWindow& window, UINT width, UINT height, UINT xPos, UINT yPos)
	{
		IDateTime* input = new DateTime(width, height, xPos, yPos, 110);
		window.AddControl(*input);
		return input;
	}
}