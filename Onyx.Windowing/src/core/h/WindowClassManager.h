#pragma once
#include "stdafx.h"
#include <string>
#include "../../../include/Onyx.Gui.h"

enum ONYXWINDOWING_API WindowClassTypes
{
	DEFAULT
};
using namespace std;
struct WindowClass 
{
	WNDCLASSEX WndClass;
	wstring ClassName;
};

class WindowClassManager 
{
public:
	ONYXWINDOWING_API static WindowClass GetDefaultWindowClass();

protected:
	static WindowClass DefaultWindowClass;
};