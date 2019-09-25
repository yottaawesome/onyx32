#include "../../h/stdafx.h"
#include "../../h/StaticFunctions.h"
#include "../../Win32/Win32Window.h"
#include "DateTime.h"

namespace Onyx32::Gui
{
	OnDateTimeChange DateTime::DefaultDateTimeChangeHandler = 
		[](IDateTime& control, SYSTEMTIME& dt) -> void {};

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

	void DateTime::SetOnChange(OnDateTimeChange& onChange)
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
				{
					initCommonControls = false;
				}
				else
				{
					_state = ControlState::Error;
					return;
				}
			}

			Win32ChildWindowCreationArgs args(
				0,
				DateTime::Class,
				L"DateTime",
				DateTime::Styles,
				_xPos,
				_yPos,
				_width,
				_height,
				parent->GetHwnd(),
				(HMENU)_controlId,
				this,
				Static::DefCtrlProc
			);

			if (_wndHandle = CreateChildWindow(args))
			{
				_state = ControlState::Initialized;
				_isVisible = true;
			}
			else
			{
				_state = ControlState::Error;
			}
		}
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
