#pragma once
#include "../stdafx.h"
#include "index.h"

namespace Onyx32::Gui
{
	ParentWindowDescriptor::ParentWindowDescriptor(
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
	)
		: ExtendedStyles(extendedStyles),
		WindowName(windowName),
		Styles(styles),
		X(x),
		Y(y),
		Width(width),
		Height(height),
		ParentOrOwner(parentOrOwner),
		Menu(menu),
		Window(window),
		WndClass(wndClass)
	{ }

	ChildWindowDescriptor::ChildWindowDescriptor(
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