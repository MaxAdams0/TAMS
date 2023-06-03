#include "Engine.cpp"

using namespace std;

int main() {
	Engine Tams;
	cout << rang::style::reset;

	Tams.generateBoard();
	
	Tams.fieldDisplayData();

	while (Tams.kaboom == false) {
		int sel_x, sel_y;
		cout << rang::fg::green << "// down first the over" << rang::style::reset << endl;
		cout << rang::fg::cyan << rang::style::bold << "Selection (x): " << rang::style::reset;
		cin >> sel_x;
		cout << rang::fg::cyan << rang::style::bold << "Selection (y): " << rang::style::reset;
		cin >> sel_y;

		system("cls");

		Tams.tileHandler(sel_x, sel_y);

		Tams.fieldDisplayPlayer();
	}
	system("pause");
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