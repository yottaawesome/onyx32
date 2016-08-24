#pragma once
#include "stdafx.h"
#include <string>
#include "../../include/Onyx32.Gui.h"

using namespace std;

namespace Onyx32::Windows
{
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
