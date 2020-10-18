#include "pch.hpp"
#include "framework.hpp"
#include "headers/Boring32/Async/Semaphore.hpp"
#include "Onyx32.Core.hpp"

namespace Onyx32::Core
{
	Onyx32::Core::Async::ISemaphore* CreateNamedOnyxSemaphore(
		const std::wstring& name,
		const bool isInheritable,
		const long initialCount,
		const long maxCount
	) noexcept
	{
		return new Boring32::Async::Semaphore(name, isInheritable, initialCount, maxCount);
	}

	Onyx32::Core::Async::ISemaphore* CreateNamedOnyxSemaphoreWithSid(
		std::wstring& name,
		const bool isInheritable,
		const long initialCount,
		const long maxCount,
		const DWORD desiredAccess
	) noexcept
	{
		return new Boring32::Async::Semaphore(name, isInheritable, initialCount, maxCount, desiredAccess);
	}
}
