#include "Util.h"

namespace Util {
	COLORREF Util::HexToRGB(const std::string& hexColor) {
		if (hexColor.length() != 6) {
			// Ensure that the hex color has 6 characters
			return RGB(0, 0, 0); // Return black as a default color
		}

		// Parse the red, green, and blue components from the hex color
		int red = std::stoi(hexColor.substr(0, 2), 0, 16);
		int green = std::stoi(hexColor.substr(2, 2), 0, 16);
		int blue = std::stoi(hexColor.substr(4, 2), 0, 16);

		return RGB(red, green, blue);
	}

	namespace Color {
		// #####  Color Palette by http://paletton.com
		COLORREF WHITE	= RGB(255, 255, 255);
		COLORREF BLACK	= RGB(0, 0, 0);
		COLORREF RED	= RGB(255, 0, 0);
		COLORREF GREEN	= RGB(0, 255, 0);
		COLORREF BLUE	= RGB(0, 0, 255);
	}
}

