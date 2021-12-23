module onyx32.gui.corefactory;
import onyx32.gui.windows.desktop;
import onyx32.gui.windows.desktop.impl;

namespace Onyx32::GUI
{
	TestImplement::~TestImplement() {}
	int TestImplement::Blah() { return 1; }

	Windows::Desktop::IDesktopWindow* TestImplement::CreateDesktopWindow()
	{
		return new GUI::Windows::Desktop::Impl::DesktopWindow();
	}
}