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
	std::vector<bool> segments;
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
		segments(NULL),
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

	void SetSegments(std::vector<bool> segments) {
		this->segments = segments;
	}

	void SetSegmentHeight() {
		int barHeight = this->rect.bottom - this->rect.top;
		this->segmentHeight = barHeight / static_cast<int>(this->segments.size());
	}

	// ======================================== Getters ========================================
	RECT GetRect() const {
		return this->rect;
	}
	
	Colors GetColors() const {
		return this->colors;
	}

	int GetWidth() const {
		return this->width;
	}
};