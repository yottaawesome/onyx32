#pragma once

#ifdef ONYXWINDOWING_EXPORTS
#define ONYXWINDOWING_API __declspec(dllexport)
#else
#define ONYXWINDOWING_API __declspec(dllimport)
#endif
#include <string>

using namespace std;

namespace Onyx::Windows
{
	class ONYXWINDOWING_API IWindow;

	struct ONYXWINDOWING_API CreateWindowArgs
	{
		
	};

	class ONYXWINDOWING_API IControl
	{
		public:
			virtual void Initialize(IWindow* window) = 0;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) = 0;
			virtual void SetHwnd(HWND hWnd) = 0;
			virtual HWND GetHwnd() = 0;
			virtual ~IControl() = 0;
	};

	class ONYXWINDOWING_API IWindow 
	{
		public: 
			virtual void Initialize() = 0;
			virtual LRESULT Process(UINT message, WPARAM wParam, LPARAM lParam) = 0;
			virtual void SetHwnd(HWND hWnd) = 0;
			virtual HWND GetHwnd() = 0;
			virtual void AddControl(IControl* control) = 0;
			virtual void SetTitle(wstring& title) = 0;
			virtual void SetTitle(wstring&& title) = 0;
			virtual ~IWindow() = 0;
	};

	class ONYXWINDOWING_API Factory
	{
		public:
			static IWindow* TestWindowing();
	};
}
