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
	class ONYXWINDOWING_API IFormBuilder;
	class ONYXWINDOWING_API IFactory;
	class ONYXWINDOWING_API IMenu;
}

namespace Onyx32::Gui::Controls
{
	// Forward declarations
	class ONYXWINDOWING_API IControl;
	class ONYXWINDOWING_API IDateTime;
	class ONYXWINDOWING_API IButton;
	class ONYXWINDOWING_API ITextInput;
}

namespace Onyx32::Gui
{
	enum struct ONYXWINDOWING_API WindowEvents
	{
		OnBeginResize,
		OnResizing,
		OnResized,
		OnDisplayStateChanged,
		OnVisibilityChanged,
		/// This event double fires when the user minimizes the Window by clicking its Task Bar button.
		OnActivateChange,
		OnClose,
		OnDestroy,
		OnMoving,
		OnMoved,
		OnFocusChange,
		OnEnabledChange
	};

	enum struct ONYXWINDOWING_API ControlEvents
	{
		OnVisibilityChanged,
		OnDestroy,
		OnMoved,
		OnFocusChange,
		OnEnabledChange
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
		unsigned int xPos;
		unsigned int yPos;
		unsigned int width;
		unsigned int height;
	};

	// Event signatures
	typedef std::function<void(Onyx32::Gui::Controls::IButton & button)> OnClick;
	typedef std::function<void(
		Onyx32::Gui::Controls::IDateTime& control,
		SYSTEMTIME & dateTime)> OnDateTimeChange;
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

}

namespace Onyx32::Gui::Controls
{
	typedef std::function<void(ControlEvents eventType, IControl & control)> OnControlEvent;
	class ONYXWINDOWING_API IControl
	{
		public:
			virtual ~IControl() = 0;

			virtual HWND GetHwnd() const = 0;
			virtual void GetDimensions(Dimensions& dimensions) const = 0;
			virtual uint64_t GetId() const = 0;
			virtual const std::wstring& GetClass() const = 0;
			virtual ControlState GetState() const = 0;
			virtual int GetStyles() const = 0;
			virtual bool IsVisible() const = 0;

			virtual void SetEvent(ControlEvents evt, OnControlEvent&& evtHandler) = 0;
			virtual void Resize(const unsigned int width, const unsigned int height) = 0;
			virtual void Move(const unsigned int xPos, const unsigned int yPos) = 0;
			virtual void SetVisibility(const bool isVisible) = 0;

			virtual void Initialize() = 0;
	};

	enum struct ONYXWINDOWING_API ButtonEvents
	{
		OnClick,
		OnDoubleClick
	};
	typedef std::function<void(ButtonEvents eventType, IButton & button)> OnButtonEvent;
	class ONYXWINDOWING_API IButton : public IControl
	{
		public:
			virtual ~IButton() = 0;
			virtual const std::wstring& GetText() const = 0;
			using IControl::SetEvent;
			virtual void SetEvent(ButtonEvents evt, OnButtonEvent&& evtHandler) = 0;
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
}

namespace Onyx32::Gui
{
	typedef std::function<void(WindowEvents eventType, IWindow& window)> OnWindowEvent;
	class ONYXWINDOWING_API IWindow
	{
		public: 
			virtual ~IWindow() = 0;
			virtual HWND GetHwnd() const = 0;
			virtual const std::wstring& GetTitle() const = 0;
			virtual void GetDimensions(Dimensions& dimensions) const = 0;
			virtual int GetStyles() const = 0;
			virtual WindowDisplayState GetDisplayState() const = 0;
			virtual bool IsActive() const = 0;
			virtual bool HasFocus() const = 0;
			virtual bool IsVisible() const = 0;
			virtual bool IsEnabled() const = 0;

			virtual void SetTitle(std::wstring_view title) = 0;
			virtual void SetVisibility(const bool isVisible) = 0;
			virtual void SetDisplayState(const WindowDisplayState state) = 0;
			virtual void SetEvent(WindowEvents evt, OnWindowEvent&& evtHandler) = 0;
			virtual void SetEnabled(const bool isEnabled) = 0;

			/// <summary>
			/// Adds the Control to the Window. The Window assumes ownership of the Control's lifetime.
			/// </summary>
			/// <param name="control">The Control to add to the Window. Cannot be null.</param>
			virtual void AddControl([[notnull]] Onyx32::Gui::Controls::IControl* const control) = 0;
			/// <summary>
			/// Destroys the Control and removes it from the Window. This function has no effect if the Control does not belong to the Window.
			/// </summary>
			/// <param name="control">The Control to destroy. Cannot be null.</param>
			virtual void DestroyControl([[notnull]] Onyx32::Gui::Controls::IControl* const control) = 0;
			virtual void Move(const unsigned int xPos, const unsigned int yPos) = 0;
			virtual void Resize(const unsigned int width, const unsigned int height) = 0;
			virtual void RequestFocus() = 0;

			virtual void Initialize() = 0;
	};

	class ONYXWINDOWING_API IFactory
	{
		public:
			virtual ~IFactory() = 0;
			[[nodiscard]] virtual IWindow* CreateDefaultWindow(std::wstring_view title, unsigned int width = 0, unsigned int height = 0) = 0;
			[[nodiscard]] virtual IWindow* CreateStyledWindow(std::wstring_view title, const int styles, unsigned int width = 0, unsigned int height = 0) = 0;
			[[nodiscard]] virtual Onyx32::Gui::Controls::IDateTime* CreateDateTime(IWindow* parent, unsigned int controlId, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos) = 0;
			[[nodiscard]] virtual Onyx32::Gui::Controls::ITextInput* CreateTextInput(IWindow* parent, unsigned int controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos) = 0;
			[[nodiscard]] virtual Onyx32::Gui::Controls::IButton* CreateButton(IWindow* parent, unsigned int controlId, std::wstring_view text, unsigned int width, unsigned int height, unsigned int xPos, unsigned int yPos) = 0;
			[[nodiscard]] virtual IApplication* GetApplication() = 0;
	};

	typedef IFactory* (*getMainFactory)();
	extern "C" ONYXWINDOWING_API [[nodiscard]] IFactory* GetMainFactory();
}
