/* TODO
* - figure out a way to switch focused sectors
*		- this will likely result in another major restructuring .-.
* - isolate the window class so it can be used in other projects / as a library 
*/


#include "NewEngine.cpp"
#include "Application.h"
#include "Util.h"

using namespace std;

// Required for the program to be counted as a Windows application, 
// so it will not spawn a terminal along side it
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	// =========================== Win32 Windows Creation for TUI Interface ===========================
	Application app;
	Application::Menu sideMenu = {
		Util::Color::PRIMARY_1,
		Util::Color::BG_T,
		Util::Color::BG_T,
		Util::Color::PRIMARY_1,
		app.SECTOR_GAP,
		NULL,
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
		0
	};

	RECT wndsize = app.GetWindowSize();
	Application::Sector sideSector = {
		Util::Color::BG_T,
		Util::Color::BG_S,
		{
			0,
			0,
			250 - app.WINDOW_BORDER_SIZE,
			wndsize.bottom - wndsize.top,
		},
		true
	};
	Application::Sector gameSector = {
		Util::Color::BG_T,
		Util::Color::BG_S,
		{
			250,
			0,
			wndsize.right - wndsize.left,
			wndsize.bottom - wndsize.top,
		},
		false
	};

	// ==================================== Pre-Render UI Elements ====================================
	app.ClearWindow(Util::Color::FG_T); // sets bg color
	///window.RenderBorders(window.WINDOW_BORDER_SIZE, Util::Color::FG_T);
	app.RenderSector(&sideSector);
	app.RenderSector(&gameSector);

	// ============================ TAMS Engine and Systems Initialization ============================
	Engine Tams;
	Tams.generateBoard();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		app.RenderMenu(&sideSector, &sideMenu);

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_KEYDOWN)
		{
			int key = static_cast<int>(msg.wParam);
			switch (key) {
			case VK_UP:
				app.setOptionSelected(&sideMenu, --sideMenu.selected);
				break;
			case VK_DOWN:
				app.setOptionSelected(&sideMenu, ++sideMenu.selected);
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