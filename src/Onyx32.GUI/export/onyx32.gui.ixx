export module onyx32.gui;
export import onyx32.gui.ifactory;

export namespace Onyx32::GUI
{
	using CoreFactorySignature = ICoreFactory* (*)();
	export extern "C" __declspec(dllexport) ICoreFactory* GetCoreFactory();
}
