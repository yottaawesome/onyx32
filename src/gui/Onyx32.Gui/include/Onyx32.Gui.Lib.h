#pragma once
#include "Onyx32.Gui.h"
#include <Windows.h>
#include <stdexcept>

namespace Onyx32::Gui
{
	class Onyx32Lib
	{
		public:
			Onyx32Lib();
			Onyx32Lib(const std::wstring& path);
			virtual ~Onyx32Lib();
			virtual const std::wstring& GetPath();
			virtual const HMODULE GetHandle();
			virtual IFactory* GetMainFactory();

		protected:
			getMainFactory factFunc;
			const std::wstring path;
			HMODULE libraryHandle;
			virtual void* Resolve(std::string_view path);
	};

	Onyx32Lib::Onyx32Lib()
		: path(L"Onyx32.Gui.dll"), libraryHandle(nullptr), factFunc(nullptr)
	{
		libraryHandle = LoadLibrary(path.c_str());
		if (libraryHandle == nullptr)
			throw std::runtime_error("Failed to load library");
		factFunc = (getMainFactory) this->Resolve("GetMainFactory");
		if (factFunc == nullptr)
			throw std::runtime_error("Failed to load main factory function");
	}

	Onyx32Lib::Onyx32Lib(const std::wstring& path)
		: path(path), libraryHandle(nullptr), factFunc(nullptr)
	{
		libraryHandle = LoadLibrary(path.c_str());
		if (libraryHandle == nullptr)
			throw std::runtime_error("Failed to load library");
	}

	Onyx32Lib::~Onyx32Lib()
	{
		if(libraryHandle)
			FreeLibrary(libraryHandle);
	}

	const std::wstring& Onyx32Lib::GetPath()
	{
		return path;
	}

	const HMODULE Onyx32Lib::GetHandle()
	{
		return this->libraryHandle;
	}

	void* Onyx32Lib::Resolve(std::string_view path)
	{
		return GetProcAddress(this->libraryHandle, std::string(path).c_str());
	}

	IFactory* Onyx32Lib::GetMainFactory()
	{
		return this->factFunc();
	}
}
