#include "Menu.h"

Menu::Menu(
	COLORREF defaultFgColor,
	COLORREF defaultBgColor,
	COLORREF selectedFgColor,
	COLORREF selectedBgColor,
	int offset,
	std::vector<const wchar_t*> options
) : parentSector(parentSector)
{
	this->defaultFgColor = defaultFgColor;
	this->defaultBgColor = defaultBgColor;
	this->selectedFgColor = selectedFgColor;
	this->selectedBgColor = selectedBgColor;
	this->offset = offset;
	this->options = options;

	RECT parentSectorRect = parentSector.GetRect();
	this->rect = {
		parentSectorRect.left + this->offset,
		parentSectorRect.top + this->offset,
		parentSectorRect.right - this->offset,
		parentSectorRect.bottom - this->offset
	};
}

Menu::~Menu() {

}