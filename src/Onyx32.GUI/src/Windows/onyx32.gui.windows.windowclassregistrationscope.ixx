module;

#include <Windows.h>

export module onyx32.gui.windows.windowclassregistrationscope;

export namespace Onyx32::GUI::Windows::Desktop
{
	class WindowClassRegistrationScope
	{
		public:
			virtual ~WindowClassRegistrationScope();
			WindowClassRegistrationScope(const WNDCLASSEX& wndClass);

		public:
			const WNDCLASSEX& GetClass() const noexcept;

		protected:
			WNDCLASSEX m_class;
	};
}