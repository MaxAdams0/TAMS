/* TODO
* - generate window without a terminal
* - isolate the window class so it can be used in other projects / as a library 
*/


#include "NewEngine.cpp"
#include "Window.h"
#include "Util.h"

using namespace std;

// Required for the program to be counted as a Windows application, 
// so it will not spawn a terminal along side it
int main(void) {
	// =========================== Win32 Windows Creation for TUI Interface ===========================
	Window window;

	// ==================================== Pre-Render UI Elements ====================================
	window.ClearWindow(Util::Color::FG_T); // sets bg color
	///window.RenderBorders(window.WINDOW_BORDER_SIZE, Util::Color::FG_T);
	window.RenderSectors(Util::Color::BG_T);

	for (int i = 0; i < 5; i++) {
		window.RenderText(
			L"XXXXXXXX",
			window.WINDOW_BORDER_SIZE + window.MENU_TEXT_GAP_SIZE,
			window.WINDOW_BORDER_SIZE + window.MENU_TEXT_SIZE * (i + 0) + window.MENU_TEXT_GAP_SIZE,
			Util::Color::primaryColors[i],
			Util::Color::primaryColors[i]
		);
	}
	for (int i = 0; i < 5; i++) {
		window.RenderText(
			L"XXXXXXXX",
			window.WINDOW_BORDER_SIZE + window.MENU_TEXT_GAP_SIZE,
			window.WINDOW_BORDER_SIZE + window.MENU_TEXT_SIZE * (i + 5) + window.MENU_TEXT_GAP_SIZE,
			Util::Color::secondaryColors[i],
			Util::Color::secondaryColors[i]
		);
	}
	for (int i = 0; i < 5; i++) {
		window.RenderText(
			L"XXXXXXXX",
			window.WINDOW_BORDER_SIZE + window.MENU_TEXT_GAP_SIZE,
			window.WINDOW_BORDER_SIZE + window.MENU_TEXT_SIZE * (i + 10) + window.MENU_TEXT_GAP_SIZE,
			Util::Color::tertiaryColors[i],
			Util::Color::tertiaryColors[i]
		);
	}
	for (int i = 0; i < 5; i++) {
		window.RenderText(
			L"XXXXXXXX",
			window.WINDOW_BORDER_SIZE + window.MENU_TEXT_GAP_SIZE,
			window.WINDOW_BORDER_SIZE + window.MENU_TEXT_SIZE * (i + 15) + window.MENU_TEXT_GAP_SIZE,
			Util::Color::complimentaryColors[i],
			Util::Color::complimentaryColors[i]
		);
	}

	// ============================ TAMS Engine and Systems Initialization ============================
	Engine Tams;
	Tams.generateBoard();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}