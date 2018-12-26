#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	class Window2 : public IWindow2
	{
	
	};

	class Win32Renderer
	{
		public:
			virtual HWND Render(IWindow2& window) = 0;

			virtual ~Win32Renderer();

		protected:
	};
}