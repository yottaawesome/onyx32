export module onyx32.gui;

export namespace Onyx32::GUI
{
	struct __declspec(dllexport) ICoreFactory
	{
		virtual ~ICoreFactory();
		virtual int Blah() = 0;
	};

	using CoreFactorySignature = ICoreFactory* (*)();
	export extern "C" __declspec(dllexport) ICoreFactory* GetCoreFactory();
}
