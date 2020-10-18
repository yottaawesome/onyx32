#ifdef ONYX32CORE_EXPORTS
#define ONYX32CORE_API __declspec(dllexport)
#else
#define ONYX32CORE_API __declspec(dllimport)
#endif

#include "headers/Onyx32/Async/ISemaphore.hpp"

namespace Onyx32::Core
{
	extern "C" ONYX32CORE_API Onyx32::Core::Async::ISemaphore* CreateNamedOnyxSemaphore(
		const std::wstring& name,
		const bool isInheritable,
		const long initialCount,
		const long maxCount
	) noexcept;

	extern "C" ONYX32CORE_API Onyx32::Core::Async::ISemaphore* CreateNamedOnyxSemaphoreWithSid(
		std::wstring& name,
		const bool isInheritable,
		const long initialCount,
		const long maxCount,
		const DWORD desiredAccess
	) noexcept;
}