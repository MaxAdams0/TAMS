#pragma once

#include <windows.h>
#include <string>
#include <vector>

class Window {
public:
	int MENU_TEXT_SIZE;
	int MENU_TEXT_GAP_SIZE;
	int WINDOW_BORDER_SIZE;

private:
	struct Sector {
		RECT rect;
		bool focused;
	};


	HWND hwnd;
	HFONT GLOBAL_TEXT_FONT;
	std::vector<Sector> windowSectors;

public:
	Window();
	~Window();

	bool Initialize();

	void RenderText(const wchar_t* text, int x, int y, COLORREF textFgColor, COLORREF textBgColor);
	void RenderRect(RECT rect, COLORREF color);
	void RenderBorders(int thickness, COLORREF color);
	void RenderSectors(COLORREF color);
	void ClearWindow(COLORREF color);
	void ClampToUsableWindow(RECT *rect);

private:
	RECT GetWindowSize();
	void Cleanup();
};