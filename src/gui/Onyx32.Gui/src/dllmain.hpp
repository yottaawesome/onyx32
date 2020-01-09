#pragma once

namespace Onyx32::Gui
{
	class Dll
	{
		public:
			static void SetModule(HMODULE dllModule);
			static HMODULE GetModule();
		protected:
			static HMODULE module;
	};
}
