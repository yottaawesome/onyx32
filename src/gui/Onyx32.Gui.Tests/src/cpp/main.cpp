#include "../h/stdafx.h"
#include "../h/Onyx32.h"
#include "../../../Onyx32.Gui/include/Onyx32.Gui.h"
#include "../../../Onyx32.Gui/include/Onyx32.Gui.Lib.h"
#include <functional>

using std::wstring;
using std::function;
using Onyx32::Gui::IFormBuilder;
using Onyx32::Gui::IWindow;
using Onyx32::Gui::IFactory;
using Onyx32::Gui::ITextInput;
using Onyx32::Gui::IButton;
using Onyx32::Gui::IDateTime;
using Onyx32::Gui::Onyx32Lib;

// https://docs.microsoft.com/en-us/windows/desktop/learnwin32/learn-to-program-for-windows--sample-code

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	Onyx32Lib lib;
	IFactory* factory = lib.GetMainFactory();
	IFormBuilder* fct = factory->GetFormBuilder();
	IWindow* wnd = fct->CreateDefaultWindow(L"This is a test", 500, 500);
	
	IButton* button = nullptr;
	function<void(void)> clickHandler = [&button]() -> void
	{
		MessageBox(nullptr, L"Let's resize the button you clicked, no?", L"Resize!", MB_OK);
		button->Resize(75, 75);
	};

	wnd->Initialize();
	button = fct->AddButton(
		*wnd,
		L"Button",
		100,
		100,
		10,
		10,
		clickHandler);

	IDateTime* dateTime = fct->AddDateTime(*wnd, 220, 20, 120, 100);
	Onyx32::Gui::OnDateTimeChangeHandler changeHandler = [&dateTime](IDateTime& control, SYSTEMTIME& dt) -> void
	{
		char box[150];
		sprintf_s(box, 150, "%u/%u/%u", dt.wDay, dt.wMonth, dt.wYear);
		MessageBoxA(nullptr, box, "Changed!", MB_OK);
	};
	dateTime->SetOnChange(changeHandler);

	//ITextInput* input = fct->AddTextInput(*wnd, L"", 350, 50, 25, 25);
	//input->SetText(L"Test input");
	//MessageBox(nullptr, input->GetText().c_str(), L"Get input text", MB_OK);

	Onyx32::Gui::IApplication* app = factory->GetApplication();
	int retVal = app->MainLoop();

	delete wnd;
	delete app;
	delete factory;

	return retVal;
}
