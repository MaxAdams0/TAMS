#include "Application.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}
/*Initialize the window with set parameters.
	Dev Note: This will eventually be configurable, but that is not a main priority on my list.*/
Application::Application() : hwnd(NULL) {
	SECTOR_GAP = 6;
	WINDOW_BORDER_SIZE = 12;

	// Create a window
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0L,
		0L,
		GetModuleHandle(NULL),
		NULL,
		NULL,
		NULL,
		NULL,
		L"TAMS",
		NULL
	};
	RegisterClassEx(&wc);
	hwnd = CreateWindow(
		wc.lpszClassName,
		L"Totally Accurate MineSweeper",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		800,
		600,
		NULL,
		NULL,
		wc.hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}


Application::~Application() {
	if (hwnd) {
		DestroyWindow(hwnd);
		UnregisterClass(L"TAMS_window", GetModuleHandle(NULL));
		hwnd = NULL;
	}
}