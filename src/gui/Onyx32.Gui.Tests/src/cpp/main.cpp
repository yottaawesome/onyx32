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
using Onyx32::Gui::IApplication;

// https://docs.microsoft.com/en-us/windows/desktop/learnwin32/learn-to-program-for-windows--sample-code

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	Onyx32Lib lib;
	std::shared_ptr<IFactory> factory(lib.GetMainFactory());
	std::shared_ptr<IFormBuilder> fct(factory->GetFormBuilder());
	std::shared_ptr<IWindow> wnd(fct->CreateDefaultWindow(L"This is a test", 500, 500));
	std::shared_ptr<IApplication> app(factory->GetApplication());

	wnd->Initialize();

	// Ownership of controls is done by the parent window, so do not use shared_ptr
	IButton* button = fct->CreateButton(100, L"Button", 100, 100, 10, 10);
	ITextInput* input = fct->CreateTextInput(101, L"", 350, 50, 25, 125);
	IDateTime* dateTime = fct->CreateDateTime(102, 220, 20, 120, 100);
	wnd->AddControl(*button);
	wnd->AddControl(*input);
	wnd->AddControl(*dateTime);

	button->SetOnClick(
		[](IButton& button) -> void
		{
			MessageBox(nullptr, L"Let's resize the button you clicked, no?", L"Resize!", MB_OK);
			button.Resize(75, 75);
		});
	wnd->SetOnActivate([](IWindow& window, bool isActive) -> void { OutputDebugStringA(isActive ? "\nWindow focus: active" : "\nWindow focus: inactive"); });
	wnd->SetOnResized([](IWindow& window) -> void { OutputDebugStringA("\nWindow resized"); });

	Onyx32::Gui::OnDateTimeChange changeHandler = [&dateTime](IDateTime& control, SYSTEMTIME& dt) -> void
	{
		char box[150];
		sprintf_s(box, 150, "%u/%u/%u", dt.wDay, dt.wMonth, dt.wYear);
		MessageBoxA(nullptr, box, "Changed!", MB_OK);
	};
	dateTime->SetOnChange(changeHandler);

	input->SetText(L"Test input");
	MessageBox(nullptr, input->GetText().c_str(), L"Get input text", MB_OK);

	int retVal = app->MainLoop();

	return retVal;
}
