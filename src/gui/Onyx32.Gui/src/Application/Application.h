#pragma once
#include "../shared/Onyx32.Gui.Internal.h"

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
