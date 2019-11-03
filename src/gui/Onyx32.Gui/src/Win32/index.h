#pragma once
#include "../h/stdafx.h"
#include <string>

namespace Onyx32::Gui
{
	class IMessageable
	{
		public:
			virtual LRESULT Process(unsigned int message, WPARAM wParam, LPARAM lParam) = 0;
			virtual void SetHwnd(HWND hWnd) = 0;
			virtual ~IMessageable();
	};

	class Win32ParentWindowCreationArgs
	{
		public:
			Win32ParentWindowCreationArgs(
				const DWORD extendedStyles,
				std::wstring_view windowName,
				const DWORD styles,
				const int x,
				const int y,
				const int width,
				const int height,
				const HWND parentOrOwner,
				const HMENU menu,
				IMessageable* window,
				const WNDCLASSEX& wndClass
			);

			const DWORD ExtendedStyles;
			const std::wstring WindowName;
			const DWORD Styles;
			const int X;
			const int Y;
			const int Width;
			const int Height;
			const HWND ParentOrOwner;
			const HMENU Menu;
			IMessageable* Window;
			const WNDCLASSEX& WndClass;
	};

	class Win32ChildWindowCreationArgs
	{
		public:
			Win32ChildWindowCreationArgs(
				const DWORD extendedStyles,
				std::wstring_view className,
				std::wstring_view windowName,
				const DWORD styles,
				const int x,
				const int y,
				const int width,
				const int height,
				const HWND parent,
				const HMENU menuOrId,
				const IMessageable* control,
				const SUBCLASSPROC subclassProc
			);

			const DWORD ExtendedStyles;
			const std::wstring ClassName;
			const std::wstring WindowName;
			const DWORD Styles;
			const int X;
			const int Y;
			const int Width;
			const int Height;
			const HWND Parent;
			const HMENU MenuOrId;
			const IMessageable* Control;
			const SUBCLASSPROC SubclassProc;
	};

	HWND CreateParentWindow(const Win32ParentWindowCreationArgs& args);

	HWND CreateChildWindow(const Win32ChildWindowCreationArgs& args);

	LRESULT CALLBACK WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK DefCtrlProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
	
	// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getclassinfoexa
	enum WindowClassTypes
	{
		DEFAULT
	};

	struct WindowClass
	{
		WNDCLASSEX WndClass;
	};

	WindowClass GetDefaultWindowClass();
}
