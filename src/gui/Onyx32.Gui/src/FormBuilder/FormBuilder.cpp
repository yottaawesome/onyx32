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

	ITextInput* FormBuilder::CreateTextInput(UINT controlId, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos)
	{
		return new TextInput(text, width, height, xPos, yPos, controlId);
	}

	IDateTime* FormBuilder::CreateDateTime(UINT controlId, UINT width, UINT height, UINT xPos, UINT yPos)
	{
		return new DateTime(width, height, xPos, yPos, controlId);
	}

	IButton* FormBuilder::CreateButton(UINT controlId, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos)
	{
		return new Button(text, width, height, xPos, yPos, controlId);
	}
}