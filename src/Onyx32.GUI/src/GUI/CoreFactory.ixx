export module onyx32.gui.corefactory;
import onyx32.gui.ifactory;
import onyx32.gui.windows.desktop;

export namespace Onyx32::GUI
{
	class TestImplement : public ICoreFactory
	{
		public:
			virtual ~TestImplement();
			virtual int Blah() override;
			virtual Windows::Desktop::IDesktopWindow* CreateDesktopWindow() override;
	};
}