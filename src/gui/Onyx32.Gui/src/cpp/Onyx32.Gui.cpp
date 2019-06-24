#include "../h/stdafx.h"
#include "../h/Onyx32.Gui.internal.h"
#include "../Window/Window.h"
#include "../Factory/Factory.h"

namespace Onyx32::Gui
{
	//https://stackoverflow.com/questions/3628529/should-c-interfaces-have-a-virtual-destructor
	//https://stackoverflow.com/questions/2691611/destructors-for-c-interface-like-classes
	inline IControl::~IControl() { }
	inline IWindow::~IWindow() { }
	inline IButton::~IButton() { }
	inline ITextInput::~ITextInput() { }
	inline IDateTime::~IDateTime() { }
	inline IFactory::~IFactory() { }
	inline IApplication::~IApplication() { }
	inline IMenu::~IMenu() { }

	IFactory* GETMAINFACTFUNC_NAME()
	{
		return new Factory();
	}
}
