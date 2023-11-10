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
	MENU_TEXT_SIZE = 24;
	MENU_TEXT_GAP_SIZE = MENU_TEXT_SIZE + 8;
	SECTOR_GAP = 6;
	WINDOW_BORDER_SIZE = 12;

	// More Info
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createfonta
	Application::FONT = CreateFontA(
		MENU_TEXT_SIZE, // height
		0, // width, 0 = auto match closest balue
		0,
		0,
		FW_NORMAL, // weight, 400 = normal, 700 = bold
		FALSE, // italic
		FALSE, // underline
		FALSE, // strikeout
		ANSI_CHARSET, // charset
		OUT_DEFAULT_PRECIS, // how accurate is the text on screen vs. expected?
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FF_SWISS, // sans serif
		"Verdana"
	);

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