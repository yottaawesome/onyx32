#pragma once
#include "../../include/Onyx32.Gui.h"
#include "../Window/Window.h"
#include "../Button/Button.h"
#include "../TextInput/TextInput.h"

namespace Onyx32::Gui
{
	class Renderer
	{
		public:
			virtual HWND Render(Window* window);
			virtual HWND Render(Window* parent, BaseControl<IButton>* button, const UINT xPos, const UINT yPos);
			virtual HWND Render(Window* parent, BaseControl<ITextInput>* control, const UINT xPos, const UINT yPos);
			virtual void Resize(Button* button, const UINT width, const UINT height);

			template<typename ControlType>
			HWND RenderInternal(Window* parent, BaseControl<ControlType>* control, const UINT xPos, const UINT yPos);

			virtual ~Renderer();

		protected:
	};
}