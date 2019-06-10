#pragma once
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	class ControlInfo
	{
		public:
			ControlInfo(const IControl& control, UINT xPos, UINT yPos)
				: control(control), xPos(xPos), yPos(yPos) {}

			const IControl& control;
			UINT xPos;
			UINT yPos;
	};
}