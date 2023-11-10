#pragma once

#include <Windows.h>

class ScrollBar {
public:
	COLORREF fgColor; // the bar itself
	COLORREF bgColor; // whatever is not a bar
	int barWitdh; // pixels
	bool visible;

public:
	ScrollBar(
		COLORREF fgColor,
		COLORREF bgColor,
		int barWitdh,
		bool visible
	) : fgColor(fgColor),
		bgColor(bgColor),
		barWitdh(barWitdh),
		visible(visible)
	{

	};

	~ScrollBar()
	{

	}
};