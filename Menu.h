#pragma once

#include "Sector.h"
#include <vector>

class Menu {
public:
	COLORREF defaultFgColor;
	COLORREF defaultBgColor;
	COLORREF selectedFgColor;
	COLORREF selectedBgColor;
	int offset; // the positional/size difference from the parent sector
	RECT rect;

	std::vector<const wchar_t*> options;
	int selected;

private:
	Sector& parentSector;

public:
	Menu(
		COLORREF defaultFgColor,
		COLORREF defaultBgColor,
		COLORREF selectedFgColor,
		COLORREF selectedBgColor,
		int offset,
		std::vector<const wchar_t*> options
	);
	~Menu();

	int GetSelected() const {
		return this->selected;
	}

	void SetSelected(int optNum) {
		int max_size = this->options.size() - 1;
		optNum = max(0, min(optNum, max_size)); // clamp between 0 and the # of options
		this->selected = optNum;
	}
};