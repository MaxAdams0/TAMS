#pragma once

#include <windows.h>
#include <string>
#include <vector>

class Application {
public:
	int WINDOW_BORDER_SIZE;

	struct Menu
	{
		COLORREF defaultFgColor;
		COLORREF defaultBgColor;
		COLORREF selectedFgColor;
		COLORREF selectedBgColor;

		std::vector<const wchar_t*> options;
		int selected;
	};

	struct Sector
	{
		COLORREF focusedColor;
		COLORREF unfocusedColor;

		RECT rect;
		bool focused;
	};

private:
	HWND hwnd;
	HFONT FONT;

	int MENU_TEXT_SIZE;
	int MENU_TEXT_GAP_SIZE;

public:
	Application();
	~Application();

	void RenderText(const wchar_t* text, int x, int y, COLORREF textFgColor, COLORREF textBgColor);
	void RenderBorders(int thickness, COLORREF color);
	void RenderSector(Sector* sector);
	void RenderMenu(Sector* sector, Menu* menu);

	void ClearWindow(COLORREF color);
	void setOptionSelected(Menu* menu, int optNum);
	RECT GetWindowSize();

private:
	void RenderRect(RECT rect, COLORREF color);
	void ClampToUsableWindow(RECT* rect);
	void Cleanup();
};