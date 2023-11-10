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
		COLORREF BG_P = HexToRGB("250000");
		COLORREF BG_S = HexToRGB("100019");
		COLORREF BG_T = HexToRGB("001616");
		COLORREF BG_C = HexToRGB("001D00");

		COLORREF FG_P = HexToRGB("680404");
		COLORREF FG_S = HexToRGB("2F0645");
		COLORREF FG_T = HexToRGB("023E3E");
		COLORREF FG_C = HexToRGB("035303");

		/*
			#####  Color Palette by Paletton.com
			#####  Palette URL: http://paletton.com/#uid=7000u0kllllaFw0g0qFqFg0w0aF
		*/  
		// red
		COLORREF PRIMARY_1 = HexToRGB("FFAAAA");
		COLORREF PRIMARY_2 = HexToRGB("D46A6A");
		COLORREF PRIMARY_3 = HexToRGB("AA3939");
		COLORREF PRIMARY_4 = HexToRGB("801515");
		COLORREF PRIMARY_5 = HexToRGB("550000");
		// purple
		COLORREF SECONDARY_1 = HexToRGB("9775AA");
		COLORREF SECONDARY_2 = HexToRGB("764B8E");
		COLORREF SECONDARY_3 = HexToRGB("582A72");
		COLORREF SECONDARY_4 = HexToRGB("3D1255");
		COLORREF SECONDARY_5 = HexToRGB("260339");
		// blue
		COLORREF TERTIARY_1 = HexToRGB("669999");
		COLORREF TERTIARY_2 = HexToRGB("407F7F");
		COLORREF TERTIARY_3 = HexToRGB("226666");
		COLORREF TERTIARY_4 = HexToRGB("0D4D4D");
		COLORREF TERTIARY_5 = HexToRGB("003333");
		// green
		COLORREF COMPLEMENTARY_1 = HexToRGB("88CC88");
		COLORREF COMPLEMENTARY_2 = HexToRGB("55AA55");
		COLORREF COMPLEMENTARY_3 = HexToRGB("2D882D");
		COLORREF COMPLEMENTARY_4 = HexToRGB("116611");
		COLORREF COMPLEMENTARY_5 = HexToRGB("004400");

		// groups
		COLORREF primaryColors[] = {
			PRIMARY_1,
			PRIMARY_2,
			PRIMARY_3,
			PRIMARY_4,
			PRIMARY_5
		};
		COLORREF secondaryColors[] = {
			SECONDARY_1,
			SECONDARY_2,
			SECONDARY_3,
			SECONDARY_4,
			SECONDARY_5
		};
		COLORREF tertiaryColors[] = {
			TERTIARY_1,
			TERTIARY_2,
			TERTIARY_3,
			TERTIARY_4,
			TERTIARY_5
		};
		COLORREF complimentaryColors[] = { 
			COMPLEMENTARY_1,
			COMPLEMENTARY_2,
			COMPLEMENTARY_3,
			COMPLEMENTARY_4,
			COMPLEMENTARY_5
		};
	}
}

