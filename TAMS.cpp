#include "NewEngine.cpp"
#include "Window.h"

namespace Color {
	COLORREF TEXT_DEFAULT_COLOR = RGB(255, 220, 217);
	COLORREF BACKGROUND_COLOR = RGB(35, 35, 48);
}

using namespace std;

int main() {
	// ==================== Win32 Windows Creation for TUI Interface ====================
	Window window;
	if (!window.Initialize()) {
		return -1;
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// ==================== TAMS Engine and Systems Initialization ====================
		Engine Tams;
		Tams.generateBoard();

		window.RenderRect(0, 0, 800, 600, Color::BACKGROUND_COLOR);
		window.RenderText(L"TEST", 0, 0, Color::TEXT_DEFAULT_COLOR, Color::BACKGROUND_COLOR);
		window.RenderText(L"TEST", 0, 13, Color::TEXT_DEFAULT_COLOR, Color::BACKGROUND_COLOR);
		window.RenderBorders(Color::TEXT_DEFAULT_COLOR);
	}

	window.Cleanup();

	return 0;
}
/*   ========== TOP PRIORITY FEATURE ==========
* - detect the tiles surrounding the 0's as well
*/

/* To-do:
* Major addition: menu selection library like FXTUI / ImTUI
* - title screen?
* - create game-related message screens
* 
* - create flag system
* - create win/fail states
* - add timer
*/