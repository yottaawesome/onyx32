#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	class Win32Renderer
	{
		public:
			virtual HWND Render(IWindow& window) = 0;

			virtual ~Win32Renderer();

		protected:
	};
}