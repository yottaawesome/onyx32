// defined with this macro as being exported.
#ifdef ONYX32SYSTEM_EXPORTS
#define ONYX32SYSTEM_API __declspec(dllexport)
#else
#define ONYX32SYSTEM_API __declspec(dllimport)
#endif

namespace Onyx32::System
{
	class ONYX32SYSTEM_API Application
	{
		public:
			Application();
			Application(HACCEL accelerators);
			virtual int MainLoop();

		private:
			HACCEL accelerators;
	};
}

