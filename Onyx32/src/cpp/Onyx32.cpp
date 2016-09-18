#include "../h/stdafx.h"
#include "../h/Onyx32.h"
#include "../../../Onyx32.Gui/include/Onyx32.Gui.h"
#include "../../../Onyx32.System/include/Onyx32.System.h"

#define MAX_LOADSTRING 100

using namespace Onyx32::Gui;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	IWindow* wnd = Factory::TestWindowing();
	wnd->Initialize();

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ONYX32));
	Onyx32::System::Application app(hAccelTable);
	int retVal = app.MainLoop();

	delete wnd;

	return retVal;
}
