#pragma once
#include "../../include/Onyx32.Gui.h"
#include "../Window/Window.h"
#include "../Button/Button.h"
#include "../TextInput/TextInput.h"

namespace Onyx32::Gui
{
	class Win32Renderer
	{
		public:
			virtual HWND Render(Window* window);
			virtual HWND Render(Window* parent, Button* button, const UINT xPos, const UINT yPos);
			virtual HWND Render(Window* parent, TextInput* control, const UINT xPos, const UINT yPos);
			virtual void Resize(Button* button, const UINT width, const UINT height);

			virtual ~Win32Renderer();

		protected:
	};
}