#pragma once

#include <windows.h>
#include "Sector.h"

class Application {
public:
	int WINDOW_BORDER_SIZE;
	int SECTOR_GAP;

private:
	HWND hwnd;

public:
	Application();
	~Application();

	RECT GetWindowSize() {
		HWND hwnd = GetForegroundWindow();  // Get the handle to the current active window
		RECT windowRect;
		GetClientRect(hwnd, &windowRect);
		return windowRect;
	}

	void RenderText(Menu& menu, const wchar_t* text, int x, int y, COLORREF textFgColor, COLORREF textBgColor) {
		HDC hdc = GetDC(hwnd);
		if (hdc) {
			HFONT hOldFont = static_cast<HFONT>( // store old (default) text font
				SelectObject(hdc, menu.GetFont()) // set correct text font
			);
			SetTextColor(hdc, textFgColor); // text (rgb) color
			SetBkColor(hdc, textBgColor); // background color
			SetBkMode(hdc, OPAQUE); // TRANSPARENT breaks stuffs
			TextOutW(hdc, x, y, text, static_cast<int>(wcslen(text))); // draw the text onto the window
			SelectObject(hdc, hOldFont); // set old text font

			ReleaseDC(hwnd, hdc); // \_(-_-)_/
		}
	}
	void RenderBorders(int thickness, COLORREF color) {
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
	void RenderSector(Sector& sector) {
		HDC hdc = GetDC(hwnd);

		if (hdc) {
			if (sector.GetFocused()) {
				RenderRect(sector.GetRect(), sector.GetColors().focusedColor); // focused color is first
			}
			else {
				RenderRect(sector.GetRect(), sector.GetColors().unfocusedColor); // unfocused color is second
			}

			ReleaseDC(hwnd, hdc);
		}
	}
	void RenderMenu(Sector& sector, Menu& menu) {
		int firstPosX = sector.GetRect().left + (SECTOR_GAP * 2);
		int firstPosY = sector.GetRect().top + (SECTOR_GAP * 2);
		for (int i = 0; i < menu.GetOptions().size(); i++) {
			if (menu.GetOptions().at(i).visible == true) {
				if (menu.GetSelected() == i) { // if it is the selected element
					RenderText(
						menu,
						menu.GetOptions().at(i).name, // name
						firstPosX, // posX does not need, it is in a straight column
						firstPosY + (i * menu.GetFontInfo().GAP), // first positionY + size of gap required to get space
						menu.GetColors().selectedFgColor,
						menu.GetColors().selectedBgColor
					);
				}
				else { // if it is not the selected element
					RenderText(
						menu,
						menu.GetOptions().at(i).name,
						firstPosX,
						firstPosY + (i * menu.GetFontInfo().GAP),
						menu.GetColors().defaultFgColor,
						menu.GetColors().defaultBgColor
					);
				}
			}
		}
	}
	void RenderScrollBar(Menu& menu, ScrollBar& bar) {
		for (int i = 0; i < menu.GetOptions().size(); i++) {
			// rectangle of current segment
			RECT newBarRect = {
				bar.GetRect().left + 1,
				bar.GetRect().top + (i * bar.GetSegmentHeight()) + menu.GetOffset(),
				bar.GetRect().right - 1,
				bar.GetRect().top + ((i + 1) * bar.GetSegmentHeight()) + menu.GetOffset(),
			};

			RenderRect(
				newBarRect,
				(menu.GetOptions().at(i).visible) ? bar.GetColors().fgColor : bar.GetColors().bgColor
			);
		}
	}
	void ClearWindow(COLORREF color) {
		RECT windowRect = GetWindowSize();
		RenderRect(windowRect, color);
	}

	void ClampToUsableWindow(RECT* rect) {
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

private:
	/*Draws a rectangle on the screen. This is different from the built-in windows.h 'Rectangle()', 'FillRect()',
		and other functions, as it handles setup for you (creating brush, clipping input, etc.)*/
	void RenderRect(RECT rect, COLORREF color) {
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
};