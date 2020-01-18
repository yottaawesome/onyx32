#pragma once

namespace Onyx32::Gui
{
	class DLL
	{
		public:
			static void SetModule(HMODULE dllModule);
			static void SetHeap(HANDLE heap);
			static HANDLE GetHeap();
			static HMODULE GetModule();
		protected:
			static HMODULE module;
			static HANDLE heapHandle;
	};
}
