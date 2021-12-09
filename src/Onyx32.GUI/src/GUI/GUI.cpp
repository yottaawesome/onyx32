module;

#include <stdexcept>
#include <iostream>

module onyx32.gui;

import onyx32.gui.infra;
import onyx32.gui.windows.desktop.impl;

namespace Onyx32::GUI
{
	class TestImplement : public ICoreFactory
	{
		public:
			virtual ~TestImplement();
			virtual int Blah() override;
	};

	TestImplement::~TestImplement() {}
	int TestImplement::Blah() { return 1; }

	ICoreFactory* GetCoreFactory()
	{
		try
		{
			Onyx32::GUI::Windows::Desktop::Impl::GetDefaultWindowClass();
		}
		catch (const std::exception& ex)
		{
			std::wcout << ex.what() << std::endl;
		}

		return new TestImplement();
	}
}