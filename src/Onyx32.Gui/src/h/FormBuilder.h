#pragma once
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	class FormBuilder : public IFormBuilder
	{
	public:
		FormBuilder();
		virtual IWindow* CreateMainWindow(std::wstring& title, unsigned int width = 0, unsigned int height = 0) override;
		virtual IWindow* CreateMainWindow(std::wstring&& title, unsigned int width = 0, unsigned int height = 0) override;

		virtual void AddButton(IWindow* window, std::wstring& text, std::function<void(void)>& onClick, unsigned int width = 0, unsigned int height = 0) override;
		virtual void AddButton(IWindow* window, std::wstring&& text, std::function<void(void)>& onClick, unsigned int width = 0, unsigned int height = 0) override;

		virtual IInput* AddTextInput(IWindow* window) override;

		virtual ~FormBuilder();
	};
}
