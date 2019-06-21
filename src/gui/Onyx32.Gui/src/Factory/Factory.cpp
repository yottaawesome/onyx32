#include "../h/stdafx.h"
#include "Factory.h"
#include "../FormBuilder/FormBuilder.h"
#include "../Application/Application.h"

namespace Onyx32::Gui
{
	Factory::Factory()
	{

	}

	Factory::~Factory()
	{

	}

	IFormBuilder* Factory::GetFormBuilder()
	{
		return new FormBuilder();
	}

	IApplication* Factory::GetApplication()
	{
		return new Application();
	}
}
