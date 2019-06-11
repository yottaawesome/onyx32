#pragma once
#include "../h/stdafx.h"
#include "Win32CreationArgs.h"

namespace Onyx32::Gui
{
	Win32CreationArgs::Win32CreationArgs(
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
		const IControl* control,
		const SUBCLASSPROC subclassProc
	)
		: ExtendedStyles(extendedStyles),
		ClassName(className),
		WindowName(windowName),
		Styles(styles),
		X(x),
		Y(y),
		Width(width),
		Height(height),
		Parent(parent),
		MenuOrId(menuOrId),
		Control(control),
		SubclassProc(subclassProc)
	{ }
}