#pragma once
#include "../../h/Onyx32.Gui.Internal.h"

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
			virtual void GetDateTime(SYSTEMTIME& dateTime) override;
			virtual void SetOnChange(OnDateTimeChange& onChange) override;
			LRESULT DateTime::Process(UINT message, WPARAM wParam, LPARAM lParam) override;

			static IDateTime* Create(IWindow* parent, UINT controlId, UINT width, UINT height, UINT xPos, UINT yPos);
		
		protected:
			OnDateTimeChange& _onChange;
			static OnDateTimeChange DefaultDateTimeChangeHandler;
	};
}