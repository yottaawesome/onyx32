#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include <string>

namespace Onyx32::Gui
{
	class Button : public IButton
	{
	public:
		Button(unsigned int controlId, std::wstring& text, FunctionHandler& onClick, unsigned int width, unsigned int height);

		virtual void Initialize(IWindow* parent) override;
		virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
		virtual void SetHwnd(HWND hWnd) override;
		virtual HWND GetHwnd() override;
		virtual void SetParent(IWindow* parent);
		virtual UINT GetWidth() override;
		virtual UINT GetHeight() override;
		virtual const std::wstring& GetText() override;
		virtual UINT GetId() override;

		virtual ~Button();

	protected:
		HWND hwndButton;
		IWindow* parent;
		std::wstring text;
		unsigned int const controlId;
		unsigned int width;
		unsigned int height;
		//void (*onClick)();
		FunctionHandler& onClick;
	};
}