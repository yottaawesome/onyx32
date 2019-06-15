#pragma once
#include <string>
#include "../../include/Onyx32.Gui.h"

using namespace std;

namespace Onyx32::Gui
{
	// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getclassinfoexa
	enum ONYXWINDOWING_API WindowClassTypes
	{
		DEFAULT
	};

	struct WindowClass
	{
		WNDCLASSEX WndClass;
		wstring ClassName;
	};

	class WindowClassManager
	{
		public:
			ONYXWINDOWING_API static WindowClass GetDefaultWindowClass();

		protected:
			static WindowClass DefaultWindowClass;
	};
}
