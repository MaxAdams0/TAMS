#pragma once

#pragma once

#include <Windows.h>
#include <string>

namespace Util {
	extern COLORREF HexToRGB(const std::string& hexColor);

	namespace Color {
		extern COLORREF WHITE;
		extern COLORREF BLACK;
		extern COLORREF RED;
		extern COLORREF GREEN;
		extern COLORREF BLUE;
	}
}