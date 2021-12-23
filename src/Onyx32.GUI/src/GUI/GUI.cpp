module;

#include <stdexcept>
#include <iostream>

module onyx32.gui;
import onyx32.gui.corefactory;

namespace Onyx32::GUI
{
	ICoreFactory* GetCoreFactory()
	{
		return new TestImplement();
	}
}