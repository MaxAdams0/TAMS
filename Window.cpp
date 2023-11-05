#include "Window.h"
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_CLOSE) {
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
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

	Window::wnd_sectors = {
		{ L"Side", 0  , 0, 250, 600, 10, false },
		{ L"Game", 250, 0, 800, 600, 10, false }
	};
}

Window::~Window() {
	Cleanup();
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
		L"TAMS_window",
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
		this
	);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return true;
}

void Window::Cleanup() {
	if (hwnd) {
		DestroyWindow(hwnd);
		UnregisterClass(L"TAMS_window", GetModuleHandle(NULL));
		hwnd = NULL;
	}
}

void Window::RenderText(const wchar_t* text, short x, short y, COLORREF textFgColor, COLORREF textBgColor) {
	HDC hdc = GetDC(hwnd);
	if (hdc) {
		HFONT hOldFont = static_cast<HFONT>( // store old (default) text font
			SelectObject(hdc, Window::GLOBAL_TEXT_FONT) // set correct text font
		);
		SetTextColor(hdc, textFgColor); // text (rgb) color
		SetBkColor(hdc, textBgColor); // background color
		SetBkMode(hdc, TRANSPARENT); // opaque or transparent
		TextOutW(hdc, x, y, text, wcslen(text)); // draw the text onto the window
		SelectObject(hdc, hOldFont); // set old text font

		ReleaseDC(hwnd, hdc); // \_(-_-)_/
	}
}

void Window::RenderRect(short left, short top, short right, short bottom, COLORREF color) {
	HDC hdc = GetDC(hwnd);
	if (hdc) {
		RECT rect = { left, top, right, bottom };
		HBRUSH hBrush = CreateSolidBrush(color);
		HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush));

		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);

		ReleaseDC(hwnd, hdc);
	}
}

void Window::RenderBorders(COLORREF borderColor) {
	for (const Sector& sect : wnd_sectors) {
		RenderRect( // top border
			sect.left,
			sect.top,
			sect.right,
			sect.top + sect.border_size,
			borderColor
		);
		RenderRect( // left border
			sect.left,
			sect.top,
			sect.left + sect.border_size,
			sect.bottom,
			borderColor
		);
		RenderRect( // bottom border
			sect.left,
			sect.bottom - sect.border_size,
			sect.right,
			sect.bottom,
			borderColor
		);
		RenderRect( // right border
			sect.right - sect.border_size,
			sect.top,
			sect.right,
			sect.bottom,
			borderColor
		);
	}
}
