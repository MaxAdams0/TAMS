#include "Menu.h"

Menu::Menu(COLORREF defFgColor, COLORREF defBgColor, COLORREF selFgColor,
			COLORREF selBgColor, int offset, std::vector<const wchar_t*> options) {

	this->defFgColor = defFgColor;
	this->defBgColor = defBgColor;
	this->selFgColor = selFgColor;
	this->selBgColor = selBgColor;
	this->offset = offset;
	this->options = options;

	this->rect; // work on sector first
}

Menu::~Menu() {

}