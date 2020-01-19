#pragma once
#include "../../include/Onyx32.Gui.hpp"

namespace Onyx32::Gui
{
	class MainLoop : public IMainLoop
	{
		public:
			MainLoop();
			MainLoop(HACCEL accelerators);
			virtual ~MainLoop();

			virtual int Enter() override;
			virtual int Enter(IdleCallback callback) override;
			virtual void SetAccelerators(HACCEL accelerators) override;
			virtual void Destroy();

		private:
			HACCEL _accelerators;
	};
}
