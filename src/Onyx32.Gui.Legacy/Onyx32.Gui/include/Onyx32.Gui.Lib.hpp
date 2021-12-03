#pragma once
#include "Onyx32.Gui.hpp"
#include <Windows.h>
#include <stdexcept>

namespace Onyx32::Gui
{
	template<typename T>
	auto OnyxFree = [](T* t) -> void { t->Destroy(); };

	template<typename T>
	std::shared_ptr<T> Make(T* ptr)
	{
		return std::shared_ptr<T>(ptr, OnyxFree<T>);
	}

	class FactoryProxy
	{
		public:
			FactoryProxy(IFactory* factory)
				: m_factory(factory)
			{ }

			virtual ~FactoryProxy()
			{
				m_factory->Destroy();
				m_factory = nullptr;
			}

			[[nodiscard]]
			virtual std::shared_ptr<Onyx32::Gui::IWindow> CreateOnyxWindow(
				std::wstring_view title, 
				const int styles, 
				unsigned int width, 
				unsigned int height, 
				unsigned int xPos, 
				unsigned int yPos
			)
			{
				return std::shared_ptr<Onyx32::Gui::IWindow>(
					m_factory->CreateOnyxWindow(
						title,
						styles,
						width,
						height,
						xPos,
						yPos),
					Onyx32::Gui::OnyxFree<Onyx32::Gui::IWindow>
				);
			}
			
			[[nodiscard]]
			virtual Onyx32::Gui::Controls::IDateTime* CreateDateTime
			(
				IWindow* parent, 
				unsigned int controlId, 
				unsigned int width, 
				unsigned int height, 
				unsigned int xPos, 
				unsigned int yPos
			)
			{
				return m_factory->CreateDateTime(parent, controlId, width, height, xPos, yPos);
			}
			
			[[nodiscard]]
			virtual Onyx32::Gui::Controls::ITextInput* CreateTextInput
			(
				IWindow* parent,
				unsigned int controlId,
				std::wstring_view text,
				unsigned int width,
				unsigned int height,
				unsigned int xPos,
				unsigned int yPos
			)
			{
				return m_factory->CreateTextInput(parent, controlId, text, width, height, xPos, yPos);
			}
			
			[[nodiscard]]
			virtual Onyx32::Gui::Controls::IButton* CreateButton
			(
				IWindow* parent,
				unsigned int controlId,
				std::wstring_view text,
				unsigned int width,
				unsigned int height,
				unsigned int xPos,
				unsigned int yPos
			)
			{
				return m_factory->CreateButton(parent, controlId, text, width, height, xPos, yPos);
			}
			
			[[nodiscard]]
			virtual std::shared_ptr<Onyx32::Gui::IMainLoop> CreateMainLoop()
			{
				return std::shared_ptr<Onyx32::Gui::IMainLoop>(m_factory->CreateMainLoop(), OnyxFree<Onyx32::Gui::IMainLoop>);
			}

		protected:
			IFactory* m_factory;
	};

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
			Onyx32::Gui::MainFactory factFunc;
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
		factFunc = (Onyx32::Gui::MainFactory) this->Resolve("GetMainFactory");
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
