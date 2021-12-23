export module onyx32.gui.ifactory;
import onyx32.gui.windows.desktop;

export namespace Onyx32::GUI
{
	struct __declspec(dllexport) ICoreFactory
	{
		virtual ~ICoreFactory();
		virtual int Blah() = 0;
		virtual Windows::Desktop::IDesktopWindow* CreateDesktopWindow() = 0;
	};
}