#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "../h/Window.h"
#include "../h/Button.h"

namespace Onyx32::Gui
{
	class Win32Renderer
	{
		public:
			virtual HWND Render(Window* window);
			virtual HWND Render(Window* parent, Button* button, const UINT xPos, const UINT yPos);

			virtual ~Win32Renderer();

		protected:
	};
}