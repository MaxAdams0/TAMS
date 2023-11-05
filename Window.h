#pragma once

#include <windows.h>
#include <vector>

class Window {
public:
	Window();
	~Window();

	bool Initialize();
	void RenderText(const wchar_t* text, short x, short y, COLORREF textFgColor, COLORREF textBgColor);
	void RenderRect(short left, short top, short right, short bottom, COLORREF color);
	void RenderBorders(COLORREF borderColor);
	void Cleanup();

private:
	struct Sector {
		const wchar_t* name;
		short left;
		short top;
		short right;
		short bottom;
		short border_size;
		bool focused;
	};

	HWND hwnd;
	HFONT GLOBAL_TEXT_FONT;
	std::vector<Sector> wnd_sectors;
};
