#pragma once
#include "../h/Onyx32.Gui.Internal.h"

namespace Onyx32::Gui
{
	class Application : public IApplication
	{
		public:
			Application();
			Application(HACCEL accelerators);
			virtual ~Application();

			virtual int MainLoop() override;
			virtual void SetAccelerators(HACCEL accelerators) override;

		private:
			HACCEL _accelerators;
	};
}
