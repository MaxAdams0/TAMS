#pragma once

#include <Windows.h>
#include <vector>

#include "ScrollBar.h"

class Menu {
private:
	struct Colors {
		COLORREF defaultFgColor;
		COLORREF defaultBgColor;
		COLORREF selectedFgColor;
		COLORREF selectedBgColor;
	};
	
	std::vector<const wchar_t*> options;
	RECT rect;
	Colors colors;
	int offset; // the positional/size difference from the parent sector
	int selected;

public:
	Menu(
		std::vector<const wchar_t*> options,
		Colors colors,
		int offset,
		int selected
	) : options(options),
		rect({0,0,0,0}), // there is no NULL option for RECT type, so initialize with all zeroes
		colors(colors),
		offset(offset),
		selected(selected)
	{

	}

	~Menu()
	{

	}

	// ======================================== Setters ========================================
	void SetRect(RECT rect) {
		this->rect = rect;
	}

	void SetSelected(int optNum) {
		int max_size = this->options.size() - 1;
		optNum = max(0, min(optNum, max_size)); // clamp between 0 and the # of options
		this->selected = optNum;
	}

	// ======================================== Getters ========================================
	std::vector<const wchar_t*> GetOptions() const {
		return this->options;
	}

	RECT GetRect() const {
		return this->rect;
	}
	
	Colors GetColors() const {
		return this->colors;
	}
	
	int GetOffset() const {
		return this->offset;
	}

	int GetSelected() const {
		return this->selected;
	}

};