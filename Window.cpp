#include "Window.h"
#include <string>
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// Set the background color
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // Replace RGB values with your desired color
			FillRect(hdc, &ps.rcPaint, hBrush);
			DeleteObject(hBrush);

			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

Window::Window() : hwnd(NULL) {
	// More Info
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createfonta
	Window::GLOBAL_TEXT_FONT = CreateFontA(
		16, // height
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
}

Window::~Window() {
	Cleanup();
}

Window::WindowSize Window::GetWindowSize() {
	HWND hwnd = GetForegroundWindow();  // Get the handle to the current active window
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);
	WindowSize wsize;
	wsize.width = windowRect.right - windowRect.left;
	wsize.height = windowRect.bottom - windowRect.top;
	return wsize;
}

bool Window::Initialize() {
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

	WindowSize wndsize = GetWindowSize();

	Window::windowSectors = {
		{ 
			0,
			0,
			250,
			wndsize.height,
			false 
		},
		{ 
			250,
			0,
			wndsize.width,
			wndsize.height,
			false
		}
	};

	MENU_TEXT_SIZE = 16;
	MENU_TEXT_GAP_SIZE = 8;
	WINDOW_BORDER_SIZE = 8;

	return true;
}

void Window::Cleanup() {
	if (hwnd) {
		DestroyWindow(hwnd);
		UnregisterClass(L"TAMS_window", GetModuleHandle(NULL));
		hwnd = NULL;
	}
}

void Window::RenderText(const wchar_t* text, int x, int y, COLORREF textFgColor, COLORREF textBgColor) {
	HDC hdc = GetDC(hwnd);
	if (hdc) {
		HFONT hOldFont = static_cast<HFONT>( // store old (default) text font
			SelectObject(hdc, Window::GLOBAL_TEXT_FONT) // set correct text font
		);
		SetTextColor(hdc, textFgColor); // text (rgb) color
		SetBkColor(hdc, textBgColor); // background color
		SetBkMode(hdc, OPAQUE); // opaque or transparent
		TextOutW(hdc, x, y, text, wcslen(text)); // draw the text onto the window
		SelectObject(hdc, hOldFont); // set old text font

		ReleaseDC(hwnd, hdc); // \_(-_-)_/
	}
}

void Window::RenderRect(int left, int top, int right, int bottom, COLORREF color) {
	HDC hdc = GetDC(hwnd);
	if (hdc) {
		HBRUSH hBrush = CreateSolidBrush(color); // create new brush
		HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush)); // set new brush & store old

		// Create rectangle of specified dimensions & draw
		RECT rect = { left, top, right, bottom };
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		SelectObject(hdc, hOldBrush); // set old brush
		DeleteObject(hBrush); // delete new brush

		ReleaseDC(hwnd, hdc);
	}
}

void Window::RenderBorders(int thickness, COLORREF color) {
	RECT windowRect;
	GetClientRect(hwnd, &windowRect);

	HWND hwnd = GetForegroundWindow();
	HDC hdc = GetDC(hwnd);

	// Create a solid brush with the border color
	HBRUSH hbrBorder = CreateSolidBrush(color);

	// Calculate the coordinates and dimensions of the border rectangles
	RECT topRect = { 0, 0, windowRect.right - windowRect.left, thickness };
	RECT bottomRect = { 0, windowRect.bottom - windowRect.top - thickness, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };
	RECT leftRect = { 0, 0, thickness, windowRect.bottom - windowRect.top };
	RECT rightRect = { windowRect.right - windowRect.left - thickness, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };

	// Draw the border rectangles
	FillRect(hdc, &topRect, hbrBorder);
	FillRect(hdc, &bottomRect, hbrBorder);
	FillRect(hdc, &leftRect, hbrBorder);
	FillRect(hdc, &rightRect, hbrBorder);

	// Release resources
	DeleteObject(hbrBorder);
	ReleaseDC(hwnd, hdc);
}

void Window::ClearWindow(COLORREF color) {
	RECT windowRect;
	GetClientRect(hwnd, &windowRect);

	RenderRect(windowRect.left, windowRect.top, windowRect.right, windowRect.bottom, color);
}