#include "../h/stdafx.h"
#include "../h/StaticFunctions.h"
#include "../Win32/Win32Window.h"
#include "DateTime.h"

namespace Onyx32::Gui
{
	OnDateTimeChangeHandler DateTime::DefaultDateTimeChangeHandler = [](IDateTime& control, unsigned short day, unsigned short month, unsigned short year) -> void {};

	//https://docs.microsoft.com/en-us/windows/desktop/Controls/date-and-time-picker-control-reference
	//https://docs.microsoft.com/en-us/windows/desktop/Controls/date-and-time-picker-controls
	//https://docs.microsoft.com/en-us/windows/desktop/Controls/date-and-time-picker-control-styles
	//https://docs.microsoft.com/en-us/windows/desktop/Controls/create-a-date-and-time-picker-control
	const std::wstring DateTime::Class = DATETIMEPICK_CLASS;
	const int DateTime::Styles = WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHOWNONE;

	DateTime::DateTime(
		const UINT width,
		const UINT height,
		const UINT xPos,
		const UINT yPos,
		const unsigned int controlId)
			: BaseControl(controlId, ControlState::Uninitialized, width, height, xPos, yPos, nullptr, nullptr),
			_onChange(DateTime::DefaultDateTimeChangeHandler)
	{ }

	DateTime::~DateTime() { }

	void DateTime::SetOnChange(OnDateTimeChangeHandler& onChange)
	{
		_onChange = onChange;
	}

	void DateTime::Initialize(IWindow* parent)
	{
		if (_state == ControlState::Uninitialized)
		{
			static bool initCommonControls = true;
			if (initCommonControls)
			{
				INITCOMMONCONTROLSEX icex;

				icex.dwSize = sizeof(icex);
				icex.dwICC = ICC_DATE_CLASSES;

				if (InitCommonControlsEx(&icex))
					initCommonControls = false;
			}

			_parent = parent;

			Win32ChildWindowCreationArgs args(
				0,
				DateTime::Class,
				L"DateTime",
				DateTime::Styles,
				_xPos,
				_yPos,
				_width,
				_height,
				_parent->GetHwnd(),
				(HMENU)_controlId,
				this,
				Static::DefCtrlProc
			);
			_wndHandle = Win32Window::CreateChildWindow(args);
			_state = _wndHandle
				? ControlState::Initialized
				: ControlState::Error;
		}
	}

	void DateTime::GetDateTime(unsigned short& day, unsigned short& month, unsigned short& year)
	{
		SYSTEMTIME st;
		LRESULT value = SendMessage(_wndHandle, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
		
		if (value == GDT_VALID)
		{
			day = st.wDay;
			month = st.wMonth;
			year = st.wYear;
		}
		if (value == GDT_NONE || value == GDT_ERROR)
		{
			day = 0;
			month = 0;
			year = 0;
		}
	}

	LRESULT DateTime::Process(UINT message, WPARAM wParam, LPARAM lParam)
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
						if (lpChange->dwFlags == GDT_VALID)
						{
							unsigned short day; 
							unsigned short month; 
							unsigned short year;
							this->GetDateTime(day, month, year);
							_onChange(*this, day, month, year);
						}
						if (lpChange->dwFlags == GDT_NONE)
						{

						}
						if (lpChange->dwFlags == GDT_ERROR)
						{

						}
						return 0;
					}
				}

				return DefSubclassProc(_wndHandle, message, wParam, lParam);
			}

			default:
				return DefSubclassProc(_wndHandle, message, wParam, lParam);
		}
	}
}
