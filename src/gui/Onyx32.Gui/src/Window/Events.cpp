#include "../h/stdafx.h"
#include "../../include/Onyx32.Gui.h"
#include "Window.h"

namespace Onyx32::Gui
{
	int Window::OnActivate(bool isActive)
	{
		_activateEvtHandler(*this, isActive);
		return 0;
	}

	int Window::OnResizing(WindowResizeState operation)
	{
		return 0;
	}

	int Window::OnBeginUserResize()
	{
		return 0;
	}

	int Window::OnEndUserResize()
	{
		_onResized(*this);
		return 0;
	}

	void Window::SetOnResized(OnWindowResized&& evtHandler)
	{
		_onResized = std::move(evtHandler);
	}

	void Window::SetOnActivate(OnWindowActivateChange&& evtHandler)
	{
		_activateEvtHandler = std::move(evtHandler);
	}
}