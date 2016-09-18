#include "../h/stdafx.h"
#include "../h/Onyx32.h"
#include "../../../Onyx32.Gui/include/Onyx32.Gui.h"

#define MAX_LOADSTRING 100

using namespace Onyx32::Gui;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	IWindow* wnd = Factory::TestWindowing();
	wnd->Initialize();

	MSG msg;
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ONYX32));
	while (GetMessage(&msg, nullptr, 0, 0))
	{
	    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	    {
	        TranslateMessage(&msg);
	        DispatchMessage(&msg);
	    }
	}

	delete wnd;

	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
