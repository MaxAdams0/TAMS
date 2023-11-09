#pragma once

#include <windows.h>
#include <string>
#include <vector>

#include "Sector.h"
#include "Menu.h"

class Application {
public:
	int WINDOW_BORDER_SIZE;
	int SECTOR_GAP;
	int MENU_TEXT_SIZE;
	int MENU_TEXT_GAP_SIZE;

	struct ScrollBar {
		COLORREF barFgColor;
		COLORREF barBgColor;

		int width;
		bool visible;
	};

private:
	HWND hwnd;
	HFONT FONT;

public:
	Application();
	~Application();

	RECT GetWindowSize();

	void RenderText(const wchar_t* text, int x, int y, COLORREF textFgColor, COLORREF textBgColor);
	void RenderBorders(int thickness, COLORREF color);
	void RenderSector(Sector& sector);
	void RenderMenu(Sector& sector, Menu& menu);
	//void RenderScollBar(Menu& menu, ScrollBar& bar);

	void ClearWindow(COLORREF color);

private:
	void RenderRect(RECT rect, COLORREF color);
	void ClampToUsableWindow(RECT* rect);
};