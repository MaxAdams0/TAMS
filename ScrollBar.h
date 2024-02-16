#pragma once

#include <Windows.h>

class ScrollBar {
private:
	struct Colors {
		COLORREF fgColor; // the bar itself
		COLORREF bgColor; // whatever is not a bar
	};
	
	RECT rect;
	Colors colors;
	int width; // pixels
	int segmentHeight; // pixels
	bool visible;

public:
	ScrollBar(
		Colors colors,
		int width,
		bool visible
	) : rect({ 0,0,0,0 }),
		colors(colors),
		width(width),
		segmentHeight(0),
		visible(visible)
	{
		
	};

	~ScrollBar()
	{

	}

	// ======================================== Setters ========================================
	void SetRect(RECT rect) {
		this->rect = rect;
	}

	void SetSegmentHeight(int height) {
		this->segmentHeight = height;
	}

	// ======================================== Getters ========================================
	RECT GetRect() const {
		return this->rect;
	}

	int GetSegmentHeight() const {
		return this->segmentHeight;
	}
	
	Colors GetColors() const {
		return this->colors;
	}

	int GetWidth() const {
		return this->width;
	}
};