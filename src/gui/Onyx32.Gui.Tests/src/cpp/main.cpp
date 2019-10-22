#include "../h/stdafx.h"
#include "../h/Onyx32.h"
#include "../../../Onyx32.Gui/include/Onyx32.Gui.h"
#include "../../../Onyx32.Gui/include/Onyx32.Gui.Lib.h"
#include <functional>

using std::wstring;
using std::function;
using Onyx32::Gui::IWindow;
using Onyx32::Gui::IFactory;
using Onyx32::Gui::Controls::ITextInput;
using Onyx32::Gui::Controls::IButton;
using Onyx32::Gui::Controls::IDateTime;
using Onyx32::Gui::Onyx32Lib;
using Onyx32::Gui::IApplication;
using Onyx32::Gui::WindowEvents;
using Onyx32::Gui::ControlEvents;
using Onyx32::Gui::Controls::ButtonEvents;
using Onyx32::Gui::WindowDisplayState;
using Onyx32::Gui::Controls::IControl;

// https://docs.microsoft.com/en-us/windows/desktop/learnwin32/learn-to-program-for-windows--sample-code
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	Onyx32Lib lib;
	std::shared_ptr<IFactory> factory(lib.GetMainFactory());
	std::shared_ptr<IWindow> wnd(factory->CreateDefaultWindow(L"This is a test", 500, 500));
	std::shared_ptr<IWindow> wnd2(factory->CreateStyledWindow(L"This is a second window", WS_CAPTION | WS_POPUPWINDOW, 500, 500));
	std::shared_ptr<IApplication> app(factory->GetApplication());

	wnd->Initialize();
	wnd2->Initialize();
	
	// Ownership of controls is done by the parent window, so do not use shared_ptr
	IButton* button = factory->CreateButton(wnd.get(), 100, L"Button", 100, 100, 10, 10);
	ITextInput* input = factory->CreateTextInput(wnd.get(), 101, L"", 350, 50, 25, 125);
	IDateTime* dateTime = factory->CreateDateTime(wnd.get(), 102, 220, 20, 120, 100);

	button->SetEvent(
		ButtonEvents::OnClick,
		[](ButtonEvents evt, IButton& button) -> void { button.Resize(75, 75); });
	button->SetEvent(
		ButtonEvents::OnDoubleClick,
		[wnd](ButtonEvents evt, IButton& button) -> void { wnd->SetDisplayState(WindowDisplayState::Minimized); });

	button->SetEvent(
		ControlEvents::OnVisibilityChanged,
		[](ControlEvents evt, IControl& control) -> void { OutputDebugStringA("\nA button's visibility was changed"); }
	);

	IButton* changeButton = factory->CreateButton(wnd2.get(), 100, L"Show/Hide", 100, 100, 10, 10);
	wnd2->SetEvent(
		WindowEvents::OnClose,
		[](WindowEvents evt, IWindow& window) -> void { window.SetVisibility(false); });
	changeButton->SetEvent(
		ButtonEvents::OnClick,
		[button](ButtonEvents evt, IButton& internalButton) -> void { button->SetVisibility(!button->IsVisible()); });

	wnd->SetEvent(
		WindowEvents::OnActivateChange, 
		[](WindowEvents evt, IWindow& window) -> void
		{ 
			if(window.IsActive())
				OutputDebugStringA("\nWindow activated"); 
			else
				OutputDebugStringA("\nWindow deactivated");
		});
	wnd->SetEvent(
		WindowEvents::OnResized,
		[](WindowEvents evt, IWindow& window) -> void { OutputDebugStringA("\nWindow resized"); });
	wnd->SetEvent(
		WindowEvents::OnClose,
		[](WindowEvents evt, IWindow& window) -> void { PostQuitMessage(0); });
	wnd->SetEvent(
		WindowEvents::OnVisibilityChanged,
		[](WindowEvents evt, IWindow& window) -> void { OutputDebugStringA("\nWindow visibility changed"); });
	wnd->SetEvent(
		WindowEvents::OnDisplayStateChanged,
		[](WindowEvents evt, IWindow& window) -> void { OutputDebugStringA("\nDisplay state changed"); });

	Onyx32::Gui::OnDateTimeChange changeHandler = [&dateTime](IDateTime& control, SYSTEMTIME& dt) -> void
	{
		char box[150];
		sprintf_s(box, 150, "%u/%u/%u", dt.wDay, dt.wMonth, dt.wYear);
		MessageBoxA(nullptr, box, "Changed!", MB_OK);
	};
	dateTime->SetOnChange(changeHandler);

	input->SetText(L"Test input");
	
	int retVal = app->MainLoop();

	return retVal;
}
