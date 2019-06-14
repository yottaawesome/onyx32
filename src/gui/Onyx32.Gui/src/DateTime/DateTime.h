#pragma once
#include "../h/Onyx32.Gui.Internal.h"

namespace Onyx32::Gui
{
	class DateTime : public BaseControl<IDateTime>
	{
		public:
			DateTime(
				const UINT width,
				const UINT height,
				const UINT xPos,
				const UINT yPos,
				const unsigned int controlId);
			virtual ~DateTime();

			virtual void Initialize(IWindow* parent) override;
			virtual void GetDateTime(unsigned short& day, unsigned short& month, unsigned short& year) override;
			virtual void SetOnChange(OnDateTimeChangeHandler& onChange) override;
			LRESULT DateTime::Process(UINT message, WPARAM wParam, LPARAM lParam) override;
		private:
			OnDateTimeChangeHandler& _onChange;
			static OnDateTimeChangeHandler DefaultDateTimeChangeHandler;
	};
}