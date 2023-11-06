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
		int left;
		int top;
		int right;
		int bottom;
		bool focused;
	};

	struct WindowSize {
		int width;
		int height;
	};

	HWND hwnd;
	HFONT GLOBAL_TEXT_FONT;
	std::vector<Sector> windowSectors;

public:
	Window();
	~Window();

	bool Initialize();

	void RenderText(const wchar_t* text, int x, int y, COLORREF textFgColor, COLORREF textBgColor);
	void RenderRect(int left, int top, int right, int bottom, COLORREF color);
	void RenderBorders(int thickness, COLORREF color);
	void ClearWindow(COLORREF color);
	COLORREF HexToRGB(const std::string& hexColor);

private:
	WindowSize GetWindowSize();
	void Cleanup();
};