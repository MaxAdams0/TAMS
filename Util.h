#pragma once

#include <Windows.h>
#include <string>

namespace Util {
	extern COLORREF HexToRGB(const std::string& hexColor);

	namespace Color {
		extern COLORREF BG_P;
		extern COLORREF BG_S;
		extern COLORREF BG_T;
		extern COLORREF BG_C;

		extern COLORREF FG_P;
		extern COLORREF FG_S;
		extern COLORREF FG_T;
		extern COLORREF FG_C;

		extern COLORREF PRIMARY_1; 
		extern COLORREF PRIMARY_2; 
		extern COLORREF PRIMARY_3;
		extern COLORREF PRIMARY_4; 
		extern COLORREF PRIMARY_5; 

		extern COLORREF SECONDARY_1;
		extern COLORREF SECONDARY_2;
		extern COLORREF SECONDARY_3;
		extern COLORREF SECONDARY_4;
		extern COLORREF SECONDARY_5; 

		extern COLORREF TERTIARY_1;
		extern COLORREF TERTIARY_2;
		extern COLORREF TERTIARY_3;
		extern COLORREF TERTIARY_4;
		extern COLORREF TERTIARY_5;

		extern COLORREF COMPLEMENTARY_1;
		extern COLORREF COMPLEMENTARY_2;
		extern COLORREF COMPLEMENTARY_3;
		extern COLORREF COMPLEMENTARY_4;
		extern COLORREF COMPLEMENTARY_5;

		extern COLORREF primaryColors[];
		extern COLORREF secondaryColors[];
		extern COLORREF tertiaryColors[];
		extern COLORREF complimentaryColors[];
	}
}