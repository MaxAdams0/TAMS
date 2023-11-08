#pragma once

#include "Sector.h"
#include <array>

class Menu : private Sector {
private:
	COLORREF defFgColor; // default forground color (rgb)
	COLORREF defBgColor; // default background color (rgb)
	COLORREF selFgColor; // selected forground color (rgb)
	COLORREF selBgColor; // selected background color (rgb)
	int offset; // the positional/size difference from the parent sector
	RECT rect;

	std::vector<const wchar_t*> options;
	int selected;

public:
	Menu(COLORREF defFgColor, COLORREF defBgColor, COLORREF selFgColor, 
		COLORREF selBgColor, int offset, std::vector<const wchar_t*> options);
	~Menu();

	void setOptionSelected(int optNum);

	void SetRect(Sector& sector) {
		RECT menuRect = sector.getRect();
		this->rect.left = menuRect.left + this->offset;
		this->rect.top = menuRect.top + this->offset;
		this->rect.right = menuRect.right + this->offset;
		this->rect.bottom = menuRect.bottom + this->offset;
	};

	std::array<COLORREF, 4> getColors() const {
		return {
			this->defFgColor,
			this->defBgColor,
			this->selFgColor,
			this->selBgColor,
		};
	};
};