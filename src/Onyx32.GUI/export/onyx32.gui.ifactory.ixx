export module onyx32.gui.ifactory;

export namespace Onyx32::GUI
{
	struct __declspec(dllexport) ICoreFactory
	{
		virtual ~ICoreFactory();
		virtual int Blah() = 0;
	};
}