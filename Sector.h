#pragma once

#include <windows.h>
#include <array>

class Sector {
public:
	COLORREF focusedColor;
	COLORREF unfocusedColor;

	RECT rect;
	bool focused;

public:
	Sector(COLORREF focusedColor, COLORREF unfocusedColor, RECT rect, bool focused);
	~Sector();

	RECT GetRect() const {
		return this->rect;
	}
};