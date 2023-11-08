#pragma once

#include <array>
#include "Application.h"

class Sector : private Application {
private:
	COLORREF focusedColor;
	COLORREF unfocusedColor;

	RECT rect;
	bool focused;

public:
	Sector(COLORREF focusedColor, COLORREF unfocusedColor, RECT rect, bool focused);
	~Sector();

	RECT getRect() const {
		return this->rect;
	};

	std::array<COLORREF, 2> getColors() const {
		return {
			this->focusedColor,
			this->unfocusedColor
		};
	};
};