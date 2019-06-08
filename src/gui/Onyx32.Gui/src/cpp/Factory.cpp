#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "../h/Window.h"
#include "../h/WindowClassManager.h"
#include "../h/FormBuilder.h"
#include "../h/Resource.h"
#include "../h/dllmain.h"

using namespace Onyx32::Gui;

namespace Onyx32::Gui
{
	IFormBuilder* Factory::GetFormBuilder()
	{
		return new FormBuilder();
	}
}
