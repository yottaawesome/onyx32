#pragma once
#include <string>

namespace Onyx32::Gui::Win32
{
	class IMessageable
	{
		public:
			virtual LRESULT Process(unsigned int message, WPARAM wParam, LPARAM lParam) = 0;
			virtual void SetHwnd(HWND hWnd) = 0;
			virtual ~IMessageable();
	};

	class ParentWindowDescriptor
	{
		public:
			ParentWindowDescriptor(
				const DWORD extendedStyles,
				std::wstring_view windowName,
				const DWORD styles,
				const int x,
				const int y,
				const int width,
				const int height,
				const HWND parentOrOwner,
				const HMENU menu,
				const IMessageable* window,
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
			const IMessageable* Window;
			const WNDCLASSEX& WndClass;
	};

	class ChildWindowDescriptor
	{
		public:
			ChildWindowDescriptor(
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
				const IMessageable* control
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

	HWND CreateWin32Window(const ParentWindowDescriptor& args);
	HWND CreateWin32Window(const ChildWindowDescriptor& args);
	
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
