#pragma once
#include "../../h/Onyx32.Gui.Internal.h"

namespace Onyx32::Gui
{
	class DateTime : public BaseControl<IDateTime>
	{
		public:
			DateTime(
				const unsigned int width,
				const unsigned int height,
				const unsigned int xPos,
				const unsigned int yPos,
				const unsigned int controlId);
			virtual ~DateTime();

			virtual void Initialize(IWindow* parent) override;
			virtual void GetDateTime(SYSTEMTIME& dateTime) override;
			virtual void SetOnChange(OnDateTimeChange& onChange) override;
			LRESULT DateTime::Process(unsigned int message, WPARAM wParam, LPARAM lParam) override;

			static IDateTime* Create(IWindow* parent, unsigned int controlId, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos);
		
		protected:
			OnDateTimeChange& _onChange;
			static OnDateTimeChange DefaultDateTimeChangeHandler;
	};
}