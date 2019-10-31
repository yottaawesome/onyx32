#pragma once
#include <string>
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getclassinfoexa
	enum WindowClassTypes
	{
		DEFAULT
	};

	WindowClass GetDefaultWindowClass();
}
