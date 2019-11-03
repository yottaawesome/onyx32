#pragma once
#include "../../include/Onyx32.Gui.h"

namespace Onyx32::Gui
{
	class Application : public IApplication
	{
		public:
			Application();
			Application(HACCEL accelerators);
			virtual ~Application();

			virtual int MainLoop() override;
			virtual int MainLoop(IdleCallback callback) override;
			virtual void SetAccelerators(HACCEL accelerators) override;

		private:
			HACCEL _accelerators;
	};
}
