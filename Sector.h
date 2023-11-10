#pragma once

#include <Windows.h>

#include "Menu.h"

class Sector {
private:
	struct Colors {
		COLORREF focusedColor;
		COLORREF unfocusedColor;
	};

	RECT rect;
	Colors colors;
	bool focused;

public:
	Sector(
		RECT rect,
		Colors colors,
		bool focused
	) : rect(rect),
		colors(colors),
		focused(focused)
	{
		
	}

	~Sector()
	{

	}

	// Set the child menu's rect based off of the sector's dimensions
	void SetMenuRect(Menu& menu) {
		RECT newRect{
			this->rect.left + menu.GetOffset(),
			this->rect.top + menu.GetOffset(),
			this->rect.right - menu.GetOffset(),
			this->rect.bottom - menu.GetOffset()
		};
		menu.SetRect(newRect);
	}

	// ======================================== Setters ========================================
	void SetRect(RECT rect) {
		this->rect = rect;
	}

	// ======================================== Getters ========================================
	
	RECT GetRect() const {
		return this->rect;
	}

	Colors GetColors() const {
		return this->colors;
	}
	
	bool GetFocused() const {
		return this->focused;
	}
};