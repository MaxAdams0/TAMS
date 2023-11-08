#include "Window.h"
#include <string>
#include <Windows.h>

// ======================================= Window Creation and Setup ========================================

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

/*
Initialize the window with set parameters.
Dev Note: This will eventually be configurable, but that is not a main priority on my list.
*/
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

	MENU_TEXT_SIZE = 16;
	MENU_TEXT_GAP_SIZE = 16;
	WINDOW_BORDER_SIZE = 12;

	RECT wndsize = GetWindowSize();
	windowSectors = {
		{
			{
				0,
				0,
				250 - WINDOW_BORDER_SIZE,
				wndsize.bottom - wndsize.top,
			},
			false
		},
		{
			{
				250,
				0,
				wndsize.right - wndsize.left,
				wndsize.bottom - wndsize.top,
			},
			false
		}
	};
}

Window::~Window() {
	Cleanup();
}

/*
Destroys the current window and completes other processes when closing the window.
*/
void Window::Cleanup() {
	if (hwnd) {
		DestroyWindow(hwnd);
		UnregisterClass(L"TAMS_window", GetModuleHandle(NULL));
		hwnd = NULL;
	}
}

// =================================== Rendering Stuff To The Active Window ===================================

/*
Draws a piece of text on the screen at a given position.
*/
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

/*
Draws a rectangle on the screen. This is different from the built-in windows.h 'Rectangle()', 'FillRect()',
and other functions, as it handles setup for you (creating brush, clipping input, etc.)
*/
void Window::RenderRect(RECT rect, COLORREF color) {
	HDC hdc = GetDC(hwnd);
	if (hdc) {
		HBRUSH hBrush = CreateSolidBrush(color); // create new brush
		HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush)); // set new brush & store old

		// Create rectangle of specified dimensions & draw
		FillRect(hdc, &rect, hBrush);

		SelectObject(hdc, hOldBrush); // set old brush
		DeleteObject(hBrush); // delete new brush

		ReleaseDC(hwnd, hdc);
	}
}

void Window::RenderBorders(int thickness, COLORREF color) {
	RECT windowRect = GetWindowSize();

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

/*
Renders the sectors in the current environment.
*/
void Window::RenderSectors(COLORREF color) {
	HDC hdc = GetDC(hwnd);

	if (hdc) {
		for (const Sector& sector : windowSectors) {
			RECT dupe = sector.rect;
			ClampToUsableWindow(&dupe);
			RenderRect(dupe, color);
		}

		ReleaseDC(hwnd, hdc);
	}
}

// ============================== Utilities and Obfuscations To Simplify Reading ==============================

/*
Clamps the input to the window's size. This is to make sure that it does not render outside
of the view of the window.
Note: you cannot pass 'const RECT's, since this function modifies the given parameter
*/
void Window::ClampToUsableWindow(RECT *rect) {
	RECT windowRect = GetWindowSize(); // get size of window
	// Calculate the clipping area for sectors based on the window's borders
	int clipLeft = WINDOW_BORDER_SIZE;
	int clipTop = WINDOW_BORDER_SIZE;
	int clipRight = (windowRect.right - windowRect.left) - WINDOW_BORDER_SIZE;
	int clipBottom = (windowRect.bottom - windowRect.top) - WINDOW_BORDER_SIZE;
	// Set the rect's values to the clipped values
	rect->left = max(rect->left, clipLeft);
	rect->top = max(rect->top, clipTop);
	rect->right = min(rect->right, clipRight);
	rect->bottom = min(rect->bottom, clipBottom);
}

/*
Sets the entire window to a single color, effectively clearing the screen
Dev Note: I don't think I need to clamp this, right?
*/
void Window::ClearWindow(COLORREF color) {
	RECT windowRect = GetWindowSize();
	RenderRect(windowRect, color);
}

/*
Gets the current active window's visible size in pixels.
*/
RECT Window::GetWindowSize() {
	HWND hwnd = GetForegroundWindow();  // Get the handle to the current active window
	RECT windowRect;
	GetClientRect(hwnd, &windowRect);
	return windowRect;
}