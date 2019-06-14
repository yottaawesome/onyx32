#pragma once

#ifdef ONYXWINDOWING_EXPORTS
#define ONYXWINDOWING_API __declspec(dllexport)
#else
#define ONYXWINDOWING_API __declspec(dllimport)
#endif

#include <string>
#include <functional>

namespace Onyx32::Gui
{
	typedef std::function<void(void)> FunctionHandler;

	enum ONYXWINDOWING_API ControlState
	{
		Uninitialized = 1,
		Initialized,
		Destroyed,
		Error
	};

	class ONYXWINDOWING_API Application
	{
		public:
			Application();
			Application(HACCEL accelerators);
			virtual int MainLoop();

		private:
			HACCEL accelerators;
	};

	class ONYXWINDOWING_API IWindow;

	class ONYXWINDOWING_API IControl
	{
		public:
			virtual ~IControl() = 0;
			virtual void Initialize(IWindow* window) = 0;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) = 0;
			virtual void SetHwnd(HWND hWnd) = 0;
			virtual HWND GetHwnd() = 0;
			virtual UINT GetWidth() = 0;
			virtual UINT GetHeight() = 0;
			virtual UINT GetXPos() = 0;
			virtual UINT GetYPos() = 0;
			virtual UINT GetId() = 0;
			virtual const std::wstring& GetName() = 0;
			virtual ControlState GetState() = 0;
			virtual int GetStyles() = 0;
			virtual void Resize(const UINT width, const UINT height) = 0;
	};

	class ONYXWINDOWING_API IButton : public IControl
	{
		public:
			virtual ~IButton() = 0;
			virtual const std::wstring& GetText() = 0;
	};

	class ONYXWINDOWING_API IDateTime : public IControl
	{
		public:
			virtual ~IDateTime() = 0;
	};

	class ONYXWINDOWING_API ITextInput : public IControl
	{
		public:
			virtual ~ITextInput() = 0;
			virtual const std::wstring GetText() = 0;
			virtual void SetText(std::wstring_view str) = 0;
	};

	class ONYXWINDOWING_API IWindow 
	{
		public: 
			virtual void Initialize() = 0;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) = 0;
			virtual void SetHwnd(HWND hWnd) = 0;
			virtual HWND GetHwnd() = 0;
			virtual void AddControl(IControl& control) = 0;
			virtual void SetTitle(std::wstring_view title) = 0;
			virtual const std::wstring& GetTitle() = 0;
			virtual UINT GetWidth() = 0;
			virtual UINT GetHeight() = 0;

			virtual ~IWindow() = 0;
	};

	class ONYXWINDOWING_API IFormBuilder
	{
		public:
			virtual IWindow* CreateDefaultWindow(std::wstring_view title, unsigned int width = 0, unsigned int height = 0) = 0;

			virtual IButton* AddButton(IWindow& window, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos, std::function<void(void)>& onClick) = 0;
			virtual ITextInput* AddTextInput(IWindow& window, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos) = 0;
			virtual IDateTime* AddDateTime(IWindow& window, UINT width, UINT height, UINT xPos, UINT yPos) = 0;

			virtual ~IFormBuilder() = 0;
	};

	class ONYXWINDOWING_API Factory
	{
		public:
			static IFormBuilder* GetFormBuilder();
	};
}
