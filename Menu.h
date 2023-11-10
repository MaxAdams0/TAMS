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
	
	struct FontInfo {
		int SIZE;
		int GAP;
	};

	struct Option {
		const wchar_t* name;
		bool visible;
	};

	HFONT FONT;
	FontInfo FONT_INFO;

	std::vector<Option> options;
	RECT rect;
	Colors colors;
	int offset; // the positional/size difference from the parent sector
	int selected;

public:
	Menu(
		FontInfo FONT_INFO,
		std::vector<const wchar_t*> optionNames,
		Colors colors,
		int offset,
		int selected
	) : rect({0,0,0,0}), // there is no NULL option for RECT type, so initialize with all zeroes
		colors(colors),
		offset(offset),
		selected(selected)
	{
		// --------------------- Sets the Options Without Visibiliy ---------------------
		std::vector<Option> options;
		for (const wchar_t* name : optionNames) {
			Option newOption = {
				name,
				false
			};
			options.emplace_back(newOption);
		}
		this->options = options;

		// ------------------------- Sets the Font and FontInfo -------------------------
		this->FONT_INFO = {
			FONT_INFO.SIZE,
			FONT_INFO.SIZE + FONT_INFO.GAP
		};

		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createfonta
		this->FONT = CreateFontA(
			this->FONT_INFO.SIZE, // height
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
	}

	~Menu()
	{

	}

	// ======================================== Setters ========================================
	void SetBarRect(ScrollBar& bar) {
		bar.SetRect(
			{
				this->rect.right - bar.GetWidth(),
				this->rect.top,
				this->rect.right,
				this->rect.bottom
			}
		);
	}
	
	void SetOptionVisibilities() {
		for (int i = 0; i < this->options.size() - 1; i++) {
			// true if the text's pos is less than the bottom pos of the menu
			bool isInMenu = (((i + 1) * this->FONT_INFO.GAP) + this->rect.top) < this->rect.bottom;
			Option newOption = {
					options.at(i).name,
					// text's space/position < the menu's bottom
					isInMenu
			};
			this->options.at(i) = newOption;
		}
	}

	void SetRect(RECT rect) {
		this->rect = rect;
	}

	void SetSelected(int optNum) {
		int max_size = static_cast<int>(this->options.size() - 1);
		optNum = max(0, min(optNum, max_size)); // clamp between 0 and the # of options
		this->selected = optNum;
	}

	// ======================================== Getters ========================================
	HFONT GetFont() const {
		return this->FONT;
	}

	FontInfo GetFontInfo() const {
		return this->FONT_INFO;
	}
	
	std::vector<Option> GetOptions() const {
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