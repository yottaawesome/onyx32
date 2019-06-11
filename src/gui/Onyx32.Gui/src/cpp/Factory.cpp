#include "../h/stdafx.h"
#include "../FormBuilder/FormBuilder.h"

namespace Onyx32::Gui
{
	IFormBuilder* Factory::GetFormBuilder()
	{
		return new FormBuilder();
	}
}
