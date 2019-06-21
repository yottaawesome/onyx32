#pragma once
#include "../h/Onyx32.Gui.Internal.h"

namespace Onyx32::Gui
{
	class Factory : public IFactory
	{
		public:
			Factory();
			virtual ~Factory();
			virtual IFormBuilder* GetFormBuilder() override;
			virtual IApplication* GetApplication() override;
	};
}
