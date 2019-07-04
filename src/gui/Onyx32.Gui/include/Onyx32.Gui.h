#pragma once
#pragma warning(disable: 5030)

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
	class ONYXWINDOWING_API IMenu;
	
	enum struct ONYXWINDOWING_API WindowEvents
	{
		OnResized,
		/// This event double fires when the user minimizes the Window by clicking its Task Bar button.
		OnActivateChange,
		OnClose,
		OnMoving,
		OnMoved,
		OnGainedFocus,
		OnLosingFocus
	};

	enum struct ONYXWINDOWING_API WindowState
	{
		Uninitialized = 1,
		Initialized,
		Destroyed,
		Error
	};

	enum struct ONYXWINDOWING_API ControlState
	{
		Uninitialized = 1,
		Initialized,
		Destroyed,
		Error
	};

	enum struct ONYXWINDOWING_API WindowDisplayState
	{
		Restored = 0, // Matches SIZE_RESTORED
		Minimized = 1, // Matches SIZE_MINIMIZED
		Maximized = 2, // Matches SIZE_MAXIMIZED
	};

	struct ONYXWINDOWING_API Dimensions
	{
		UINT xPos;
		UINT yPos;
		UINT width;
		UINT height;
	};
	
	struct ONYXWINDOWING_API WindowClass
	{
		WNDCLASSEX WndClass;
	};

	// Event signatures
	typedef std::function<void(IButton& button)> OnClick;
	typedef std::function<void(
		IDateTime& control, 
		SYSTEMTIME& dateTime)> OnDateTimeChange;
	typedef std::function<void(WindowEvents eventType, IWindow& window)> OnWindowEvent;
	typedef std::function<bool(unsigned long long int counter)> IdleCallback;

	class ONYXWINDOWING_API IMenu
	{
		public:
			virtual ~IMenu() = 0;
	};

	class ONYXWINDOWING_API IApplication
	{
		public:
			virtual ~IApplication() = 0;
			virtual int MainLoop() = 0;
			virtual int MainLoop(IdleCallback callback) = 0;
			virtual void SetAccelerators(HACCEL accelerators) = 0;
	};

	class ONYXWINDOWING_API IControl
	{
		public:
			virtual ~IControl() = 0;

			virtual HWND GetHwnd() = 0;
			virtual void GetDimensions(Dimensions& dimensions) = 0;
			virtual UINT GetId() = 0;
			virtual const std::wstring& GetClass() = 0;
			virtual ControlState GetState() = 0;
			virtual int GetStyles() = 0;

			virtual void Initialize(IWindow* window) = 0;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) = 0;
			virtual void Resize(const UINT width, const UINT height) = 0;
			virtual void Move(const UINT xPos, const UINT yPos) = 0;
	};

	class ONYXWINDOWING_API IButton : public IControl
	{
		public:
			virtual ~IButton() = 0;
			virtual const std::wstring& GetText() = 0;
			virtual void SetOnClick(OnClick&& onClick) = 0;
			virtual void SetOnDoubleClick(OnClick&& onDblClick) = 0;
			virtual void SetText(std::wstring_view str) = 0;
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
			virtual HWND GetHwnd() const = 0;
			virtual const std::wstring& GetTitle() const = 0;
			virtual UINT GetWidth() const = 0;
			virtual UINT GetHeight() const = 0;
			virtual int GetStyles() const = 0;
			virtual WindowDisplayState GetDisplayState() const = 0;
			virtual bool IsActive() const = 0;

			virtual void SetTitle(std::wstring_view title) = 0;
			virtual void SetVisibility(const bool isVisible) = 0;
			virtual void SetDisplayState(const WindowDisplayState state) = 0;
			virtual void SetWindowEvent(WindowEvents evt, OnWindowEvent&& evtHandler) = 0;

			/// <summary>
			/// Adds the Control to the Window. The Window assumes ownership of the Control's lifetime.
			/// </summary>
			/// <param name="control">The Control to add to the Window. Cannot be null.</param>
			virtual void AddControl([[notnull]] IControl* const control) = 0;
			/// <summary>
			/// Destroys the Control and removes it from the Window. This function has no effect if the Control does not belong to the Window.
			/// </summary>
			/// <param name="control">The Control to destroy. Cannot be null.</param>
			virtual void DestroyControl([[notnull]] IControl* const control) = 0;
			virtual void Move(const UINT xPos, const UINT yPos) = 0;
			virtual void Resize(const UINT width, const UINT height) = 0;
			virtual void RequestFocus() = 0;

			virtual void Initialize() = 0;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	};

	class ONYXWINDOWING_API IFactory
	{
		public:
			virtual ~IFactory() = 0;
			[[nodiscard]] virtual IWindow* CreateDefaultWindow(std::wstring_view title, UINT width = 0, UINT height = 0) = 0;
			[[nodiscard]] virtual IWindow* CreateStyledWindow(std::wstring_view title, const int styles, UINT width = 0, UINT height = 0) = 0;
			[[nodiscard]] virtual IDateTime* CreateDateTime(UINT controlId, UINT width, UINT height, UINT xPos, UINT yPos) = 0;
			[[nodiscard]] virtual ITextInput* CreateTextInput(UINT controlId, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos) = 0;
			[[nodiscard]] virtual IButton* CreateButton(UINT controlId, std::wstring_view text, UINT width, UINT height, UINT xPos, UINT yPos) = 0;
			[[nodiscard]] virtual IApplication* GetApplication() = 0;
	};

	#define GETMAINFACTFUNC_NAME GetMainFactory
	typedef IFactory* (*getMainFactory)();
	extern "C" ONYXWINDOWING_API [[nodiscard]] IFactory* GETMAINFACTFUNC_NAME();
}
