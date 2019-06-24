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
	// Forward declarations
	class ONYXWINDOWING_API IWindow;
	class ONYXWINDOWING_API IControl;
	class ONYXWINDOWING_API IDateTime;
	class ONYXWINDOWING_API IButton;
	class ONYXWINDOWING_API ITextInput;
	class ONYXWINDOWING_API IFormBuilder;
	class ONYXWINDOWING_API IFactory;

	// Event signatures
	typedef std::function<void(void)> FunctionHandler;
	typedef std::function<void(
		IDateTime& control, 
		SYSTEMTIME& dateTime)> OnDateTimeChange;
	typedef std::function<void(IWindow& window)> OnWindowResized;
	typedef std::function<void(IWindow& window, bool isActive)> OnWindowActivateChange;

	enum ONYXWINDOWING_API ControlState
	{
		Uninitialized = 1,
		Initialized,
		Destroyed,
		Error
	};

	enum ONYXWINDOWING_API WindowResizeState
	{
		Restored = 0, // Matches SIZE_RESTORED
		Minimized = 1, // Matches SIZE_MINIMIZED
		Maximixed = 2, // Matches SIZE_MAXIMIZED
	};

	class ONYXWINDOWING_API IApplication
	{
		public:
			virtual ~IApplication() = 0;
			//Application();
			//Application(HACCEL accelerators);
			virtual int MainLoop() = 0;
	};

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
			virtual void GetDateTime(SYSTEMTIME& dateTime) = 0;
			virtual void SetOnChange(OnDateTimeChange& onChange) = 0;
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
			virtual ~IWindow() = 0;
			virtual void Initialize() = 0;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) = 0;
			virtual void SetHwnd(HWND hWnd) = 0;
			virtual HWND GetHwnd() = 0;
			virtual void AddControl(IControl& control) = 0;
			virtual void SetTitle(std::wstring_view title) = 0;
			virtual const std::wstring& GetTitle() = 0;
			virtual UINT GetWidth() = 0;
			virtual UINT GetHeight() = 0;
			virtual void Resize(const UINT width, const UINT height) = 0;

			virtual void SetOnActivate(OnWindowActivateChange&& evtHandler) = 0;
			virtual void SetOnResized(OnWindowResized&& evtHandler) = 0;
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

	class ONYXWINDOWING_API IFactory
	{
		public:
			virtual ~IFactory() = 0;
			virtual IFormBuilder* GetFormBuilder() = 0;
			virtual IApplication* GetApplication() = 0;
	};

	#define GETMAINFACTFUNC_NAME GetMainFactory
	typedef IFactory* (*getMainFactory)();
	extern "C" ONYXWINDOWING_API IFactory* GETMAINFACTFUNC_NAME();
}
