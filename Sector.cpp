#include "Sector.h"

Sector::Sector(COLORREF focusedColor, COLORREF unfocusedColor, RECT rect, bool focused) {

	this->focusedColor = focusedColor;
	this->unfocusedColor = unfocusedColor;
	this->rect = rect;
	this->focused = focused;
}

Sector::~Sector() {

}

