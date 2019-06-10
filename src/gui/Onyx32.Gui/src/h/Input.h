#pragma once
#include "stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "Window.h"

namespace Onyx32::Gui
{
	class Input : public IInput
	{
		public:
			Input(
				std::wstring_view text = L"",
				const UINT width = 100,
				const UINT height = 100,
				const unsigned int controlId = 0);
			virtual ~Input();

			virtual void Initialize(IWindow* window) override;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) override;
			virtual void SetHwnd(HWND hWnd) override;
			virtual HWND GetHwnd() override;
			virtual wstring GetText() override;
			virtual void SetText(wstring* str) override;
			virtual void SetText(wstring&& str) override;
			virtual const std::wstring& GetName();
			virtual UINT GetId() override;
			virtual int GetStyles();
			virtual void SetParent(IWindow* parent);
			virtual UINT GetWidth() override;
			virtual UINT GetHeight() override;

		protected:
			wstring text;
			HWND hwndEdit;
			IWindow* _parent;
			unsigned int const _controlId;
			unsigned int _width;
			unsigned int _height;
			static const std::wstring Class;
			static const int Styles = WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL;
	};
}