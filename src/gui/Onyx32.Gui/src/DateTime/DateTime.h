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
			virtual void DateTime::Initialize(IWindow* parent) override;
			LRESULT DateTime::Process(UINT message, WPARAM wParam, LPARAM lParam) override;
	};
}