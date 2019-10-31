#include "../../h/stdafx.h"
#include "../../h/Win32Callbacks.h"
#include "../../Win32/Win32Window.h"
#include "DateTime.h"

namespace Onyx32::Gui::Controls
{
	OnDateTimeChange DateTime::DefaultDateTimeChangeHandler = 
		[](IDateTime& control, SYSTEMTIME& dt) -> void {};

	//https://docs.microsoft.com/en-us/windows/desktop/Controls/date-and-time-picker-control-reference
	//https://docs.microsoft.com/en-us/windows/desktop/Controls/date-and-time-picker-controls
	//https://docs.microsoft.com/en-us/windows/desktop/Controls/date-and-time-picker-control-styles
	//https://docs.microsoft.com/en-us/windows/desktop/Controls/create-a-date-and-time-picker-control
	const std::wstring Onyx32::Gui::Controls::DateTime::Class = DATETIMEPICK_CLASS;
	const int DateTime::Styles = WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHOWNONE;

	IDateTime* DateTime::Create(IWindow* parent, unsigned int controlId, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos)
	{
		auto control = new DateTime(width, height, xPos, yPos, controlId);
		static bool initCommonControls = true;
		if (initCommonControls)
		{
			INITCOMMONCONTROLSEX icex;

			icex.dwSize = sizeof(icex);
			icex.dwICC = ICC_DATE_CLASSES;

			if (!InitCommonControlsEx(&icex))
				return nullptr;
			initCommonControls = false;
		}

		Win32ChildWindowCreationArgs args(
			0,
			DateTime::Class,
			L"DateTime",
			DateTime::Styles,
			xPos,
			yPos,
			width,
			height,
			parent->GetHwnd(),
			(HMENU)controlId,
			control,
			DefCtrlProc
		);

		if (control->_wndHandle = CreateChildWindow(args))
		{
			control->_state = ControlState::Initialized;
			control->_isVisible = true;
			return control;
		}
		
		delete control;
		return nullptr;
	}

	DateTime::DateTime(
		const unsigned int width,
		const unsigned int height,
		const unsigned int xPos,
		const unsigned int yPos,
		const unsigned int controlId)
			: BaseControl(controlId, ControlState::Uninitialized, width, height, xPos, yPos, nullptr, nullptr),
			_onChange(DateTime::DefaultDateTimeChangeHandler)
	{ }

	DateTime::~DateTime() { }

	void DateTime::SetOnChange(OnDateTimeChange& onChange)
	{
		_onChange = onChange;
	}

	void DateTime::Initialize()
	{
	}

	void DateTime::GetDateTime(SYSTEMTIME& dateTime)
	{
		SYSTEMTIME st;
		LRESULT value = SendMessage(_wndHandle, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
		
		if (value == GDT_VALID)
			dateTime = { st };
		else if (value == GDT_NONE || value == GDT_ERROR)
			dateTime = { 0 };
	}

	LRESULT DateTime::Process(unsigned int message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_NOTIFY:
			{
				NMHDR* nmh = (NMHDR*)lParam;
				switch (nmh->code)
				{
					case DTN_DATETIMECHANGE:
					{
						LPNMDATETIMECHANGE lpChange = (LPNMDATETIMECHANGE)lParam;
						SYSTEMTIME dt;
						if (lpChange->dwFlags == GDT_VALID)
						{
							this->GetDateTime(dt);
							_onChange(*this, dt);
						}
						if (lpChange->dwFlags == GDT_NONE || lpChange->dwFlags == GDT_ERROR)
						{
							dt = { 0 };
							_onChange(*this, dt);

						}
						return 0;
					}
				}

				return BaseControl<IDateTime>::Process(message, wParam, lParam);
			}

			default:
				return BaseControl<IDateTime>::Process(message, wParam, lParam);
		}
	}
}
