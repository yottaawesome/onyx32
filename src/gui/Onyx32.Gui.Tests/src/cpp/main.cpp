#include "../h/stdafx.h"
#include "../h/Onyx32.h"
#include "../../../Onyx32.Gui/include/Onyx32.Gui.h"
#include <functional>

using std::wstring;
using std::function;
using Onyx32::Gui::IFormBuilder;
using Onyx32::Gui::IWindow;
using Onyx32::Gui::Factory;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	IFormBuilder* fct = Factory::GetFormBuilder();
	IWindow* wnd = fct->CreateDefaultWindow(L"This is a test", 500, 500);
	
	function<void(void)> clickHandler = []() -> void
	{
		MessageBox(nullptr, L"You rock!", L"Brilliant", MB_OK);
	};

	wnd->Initialize();
	fct->AddButton(
		wnd,
		L"Button",
		100,
		100,
		100,
		100,
		clickHandler);

	auto input = fct->AddTextInput(wnd, L"", 350, 50, 25, 25);
	input->SetText(L"Test input");
	MessageBox(nullptr, input->GetText().c_str(), L"Get input text", MB_OK);

	Onyx32::Gui::Application app;
	int retVal = app.MainLoop();

	delete wnd;

	return retVal;
}
