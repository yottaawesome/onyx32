#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "../Window/Window.h"
#include "../WindowClassManager/WindowClassManager.h"
#include "../FormBuilder/FormBuilder.h"
#include "../h/Resource.h"
#include "../h/dllmain.h"

namespace Onyx32::Gui
{
	IFormBuilder* Factory::GetFormBuilder()
	{
		return new FormBuilder();
	}
}
