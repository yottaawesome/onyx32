#include "../h/stdafx.h"
#include "../h/Onyx32.h"
#include "../../../Onyx32.Gui/include/Onyx32.Gui.h"
#include <functional>

#define MAX_LOADSTRING 100
using namespace std;

using namespace Onyx32::Gui;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	IFormBuilder* fct = Factory::GetFormBuilder();
	IWindow* wnd = fct->CreateMainWindow(L"This is a test", 500, 500);
	
	function<void(void)> a = []() -> void
	{
		MessageBox(nullptr, L"You rock!", L"Brilliant", MB_OK);
	};

	wnd->Initialize();
	fct->AddButton(
		wnd,
		L"blah",
		a,
		200,
		200);
	auto x = fct->AddTextInput(wnd);
	wstring s = L"DURRR";
	x->SetText(L"DURRRRR");
	MessageBox(nullptr, x->GetText().c_str(), L"HURR", MB_OK);

	//HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ONYX32));
	Onyx32::System::Application app;
	int retVal = app.MainLoop();

	delete wnd;

	return retVal;
}
