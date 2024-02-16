/* TODO
* - figure out a way to switch focused sectors
*		- this will likely result in another major restructuring .-.
* - isolate the window class so it can be used in other projects / as a library 
*/

// Custom UI Library (I need a name)
#include "Application.h"
#include "Util.h"
// Minesweeper Game Engine
//#include "NewEngine.cpp"

// conda activate base
// python class_view.py "C:\dev\C++\TAMS" "C:\dev\C++\TAMS\class_hierarchy"

using namespace std;

// Required for the program to be counted as a Windows application, 
// so it will not spawn a terminal along side it
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	// =========================== Win32 Windows Creation for TUI Interface ===========================
	Application app; // Creates default window and initializes variables to their default values
	RECT wndsize = app.GetWindowSize();
	// Creates the left section of the screen, which will be used for the game menu
	Sector leftSector(
		{ // rect
			0,
			0,
			250 - app.WINDOW_BORDER_SIZE,
			wndsize.bottom - wndsize.top,
		},
		{ // colors
				Util::Color::BLACK,
				Util::Color::BLACK
		},
		true
	);
	RECT leftSectorRect = leftSector.GetRect();
	app.ClampToUsableWindow(&leftSectorRect);
	leftSector.SetRect(leftSectorRect);

	// Creates the right section of the screen, which will be used for the game itself
	// Please note that this will not render anything, and by itself will do nothing
	// It simply just creates the variables necissary for creating the ui's functionality and looks
	Sector gameSector(
		{ // rect
			250,
			0,
			wndsize.right - wndsize.left,
			wndsize.bottom - wndsize.top,
		},
		{ // colors
				Util::Color::BLACK,
				Util::Color::BLACK
		},
		false
	);
	RECT gameSectorRect = gameSector.GetRect();
	app.ClampToUsableWindow(&gameSectorRect);
	gameSector.SetRect(gameSectorRect);

	Menu sideMenu(
		{ // font info
			24,
			6
		},
		{ // options
			L"Option 1",
			L"Option 2",
			L"Option 3",
			L"Option 4",
			L"Option 5",
			L"Option 6",
			L"Option 7",
			L"Option 8",
			L"Option 9",
			L"Option 10",
			L"Option 11",
			L"Option 12",
			L"Option 13",
			L"Option 14",
			L"Option 15",
			L"Option 16",
			L"Option 17",
			L"Option 18",
			L"Option 19",
			L"Option 20",
		},
		{ // colors
			Util::Color::GREEN,
			Util::Color::BLACK,
			Util::Color::BLACK,
			Util::Color::GREEN
		},
		app.SECTOR_GAP,
		0
	);
	leftSector.SetMenuRect(sideMenu);

	ScrollBar scrollBar(
		{ // colors
			Util::Color::WHITE,
			Util::Color::BLUE
		},
		12,
		true
	);
	
	sideMenu.SetBarRect(scrollBar);
	//scrollBar.SetSegmentHeight();

	// ==================================== Pre-Render UI Elements ====================================
	app.ClearWindow(Util::Color::RED); // sets bg color
	///window.RenderBorders(window.WINDOW_BORDER_SIZE, Util::Color::FG_T);
	app.RenderSector(leftSector);
	app.RenderSector(gameSector);

	// ============================ TAMS Engine and Systems Initialization ============================
	//Engine Tams;
	//Tams.GenerateBoard();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		sideMenu.SetOptionVisibilities();
		sideMenu.SetBarSegmentHeight(scrollBar);
		app.RenderMenu(leftSector, sideMenu);
		app.RenderScrollBar(sideMenu, scrollBar);

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_KEYDOWN)
		{
			int key = static_cast<int>(msg.wParam);
			switch (key) {
			case VK_UP:
				sideMenu.SetSelected(sideMenu.GetSelected() - 1);
				break;
			case VK_DOWN:
				sideMenu.SetSelected(sideMenu.GetSelected() + 1);
				break;
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
		}
	}

	return 0;
}


/*
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
*/