module;

#include <format>
#include <stdexcept>
#include <Windows.h>

module onyx32.gui.windows.desktop.impl;
import onyx32.gui.windows.infra;
import onyx32.gui.global;
import onyx32.gui.windows.windowclassregistrationscope;

namespace Onyx32::GUI::Windows::Desktop::Impl
{
	DesktopWindow::~DesktopWindow()
	{
		if (m_hwnd)
			DestroyWindow(m_hwnd);
	}

	DesktopWindow::DesktopWindow()
		: m_hwnd(nullptr)
	{ 
		Construct();
	}

	LRESULT DesktopWindow::Process(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
		}

		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	void DesktopWindow::SetHwnd(HWND hWnd)
	{
		m_hwnd = hWnd;
	}

	WPARAM DesktopWindow::MainLoop()
	{
		MSG msg;
		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return msg.wParam;
	}

	const WNDCLASSEX& DesktopWindow::GetDefaultWindowClass()
	{
		static bool created = false;
		static WNDCLASSEX WndClass
		{
			.cbSize = sizeof(WNDCLASSEX),
			.style = CS_HREDRAW | CS_VREDRAW,
			.lpfnWndProc = Infra::WndProc,
			.cbClsExtra = 0,
			.cbWndExtra = sizeof(LONG_PTR),
			.hInstance = Global::GetHInstance(),
			.hIcon = nullptr,
			.hCursor = LoadCursorW(nullptr, IDC_ARROW),
			.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
			.lpszMenuName = nullptr,
			.lpszClassName = L"Onyx32DefaultWindow",
			.hIconSm = nullptr
		};
		if (created)
			return WndClass;

		static WindowClassRegistrationScope DefaultWindowClassScope(WndClass);
		created = true;

		return WndClass;
	}

	void DesktopWindow::Construct()
	{
		const WNDCLASSEX& wndClass = GetDefaultWindowClass();
		RECT r{ .right = 512, .bottom = 512 };
		AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
		m_hwnd = IsolationAwareCreateWindowExW(
			0,
			L"Onyx32DefaultWindow",
			L"Default Onyx32 Window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			r.right - r.left,
			//static_cast<UINT>(ceil(r.right * dpi / 96.f)),
			r.bottom - r.top,
			//static_cast<UINT>(ceil(r.bottom * dpi / 96.f)),
			nullptr,
			nullptr,
			Global::GetHInstance(), //HINST_THISCOMPONENT,
			static_cast<Infra::IMessageable*>(this)
		);
		if (!m_hwnd)
			throw std::runtime_error(__FUNCSIG__": failed to create window");

		ShowWindow(m_hwnd, SW_SHOWNORMAL);
		UpdateWindow(m_hwnd);
	}
}