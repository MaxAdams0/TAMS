#include <iostream>
#include <time.h>
#include <vector>
#include <map>
#include <string>
// Terminal Colors
#include <rang/rang.hpp>

class Engine {
	// ======================================== GLOBAL VARIABLES ========================================
public:
	struct Difficulty {
		std::string name;
		int field_width;
		int field_height;
		int mine_percentage; // in decimal form
	};
	/* -------------------- (libtcod)Colors--------------------
	tcod::ColorRGB MINE_COLOR = { 235, 52, 52 };
	tcod::ColorRGB FLAG_COLOR = { 52, 235, 52 };
	tcod::ColorRGB EMPTY_COLOR = { 36, 36, 36 };
	tcod::ColorRGB BORDER_COLOR = { 245, 244, 228 };

	tcod::ColorRGB ONE_COLOR = { 52, 235, 177 };
	tcod::ColorRGB TWO_COLOR = { 52, 229, 235 };
	tcod::ColorRGB THREE_COLOR = { 52, 153, 235 };
	tcod::ColorRGB FOUR_COLOR = { 52, 64, 235 };
	tcod::ColorRGB FIVE_COLOR = { 104, 52, 235 };
	tcod::ColorRGB SIX_COLOR = { 153, 52, 235 };
	tcod::ColorRGB SEVEN_COLOR = { 217, 52, 235 };
	tcod::ColorRGB EIGHT_COLOR = { 235, 52, 131 };
	*/


	// ----------------- Global field variables -----------------
	int difficulty = 0;
	Difficulty D_easy = { "easy", 10, 10, 12 };
	Difficulty D_medium = { "medium", 15, 15, 15 };
	Difficulty D_hard = { "hard", 30, 30, 15 };
	Difficulty D_extreme = { "extreme", 100, 100, 20 };
	Difficulty D_custom = { "custom", 0, 0, 0 };

	int FIELD_WIDTH;
	int FIELD_HEIGHT;
	int MINE_COUNT;

	// ------------------- Gameplay Variables -------------------
	bool kaboom = false;

	// ---------------------- Global fields ---------------------
	std::vector<std::vector<int>> field_data;
	std::vector<std::vector<int>> field_player;
	const std::vector<std::vector<int>> field_empty;

	// ------------------ Global user variables -----------------
	int FLAG_COUNT;

	// ======================================== GAMEPLAY CHECKS ========================================
public:
	void tileHandler(int x, int y) {
		switch (field_data[x][y]) {
		case -2:
			break;
		case -1:
			kaboom = true;
			break;
		case 0:
			recursiveAdjacentZeros(x, y);
			break;
		default:
			showTile(x, y);
			break;
		}
	}

private:
	// Initial coordinate values = user input for "click"
	void recursiveAdjacentZeros(int x, int y) {
		field_player[x][y] = 1;
		// ---------- north ----------
		int new_y = (y + 1 < FIELD_HEIGHT - 1) ? y + 1 : y;
		if (field_data[x][new_y] == 0 && field_player[x][new_y] == 0) {
			recursiveAdjacentZeros(x, new_y);
		}
		// ---------- east ----------
		int new_x = (x + 1 < FIELD_WIDTH - 1) ? x + 1 : x;
		if (field_data[new_x][y] == 0 && field_player[new_x][y] == 0) {
			recursiveAdjacentZeros(new_x, y);
		}
		// ---------- south ----------
		new_y = (y - 1 >= 0) ? y - 1 : y;
		if (field_data[x][new_y] == 0 && field_player[x][new_y] == 0) {
			recursiveAdjacentZeros(x, new_y);
		}
		// ---------- west ----------
		new_x = (x - 1 >= 0) ? x - 1 : x;
		if (field_data[new_x][y] == 0 && field_player[new_x][y] == 0) {
			recursiveAdjacentZeros(new_x, y);
		}
	}

	// ======================================== FIELD GENERATION ========================================
public:
	// Entirely clear the fields to their default values
	void resetFields() {
		field_data = field_empty;
		field_player = field_empty;
	}

	/**
	* Generate the game board, which is split into the player's field and the background "data" field.
	*/
	void generateBoard() {
		/*
		std::cout << rang::style::bold << "Difficulty: " <<
			rang::fg::green << "Easy (0) " <<
			rang::fg::yellow << "Medium (1) " <<
			rang::fg::red << "Hard (2) " <<
			rang::fg::magenta << "Extreme (3) " <<
			rang::fg::gray << "Custom (4) " <<
			rang::style::reset;
		std::cin >> difficulty;
		*/
		int difficulty = 2;
		switch (difficulty) {
		case 0:
			setDifficulty(D_easy);
			break;
		case 1:
			setDifficulty(D_medium);
			break;
		case 2:
			setDifficulty(D_hard);
			break;
		case 3:
			setDifficulty(D_extreme);
			break;
		case 4:
			setDifficulty(D_custom);
			break;
		}

		FLAG_COUNT = MINE_COUNT;

		field_data = fieldInit<int>(0);
		field_player = fieldInit<int>(0);

		generateMines();
		generateTileValues();
	}

private:
	/**
	* Generate the positions for each of the bombs.
	* TODO: initiate with selection so a bomb cannot be selected on the first click
	* TODO: adjust the algorithm more similar to the minesweeper algorithm
	*		try this: https://tait.tech/2020/09/12/minesweeper/
	*/
	void generateMines() {
		srand(time(0)); // seed based on time for int randomizer
		for (int i = 0; i < MINE_COUNT; i++) {
			int x = rand() % FIELD_HEIGHT;
			int y = rand() % FIELD_WIDTH;
			field_data[x][y] = -1;
		}
	}

	/**
	* Set the difficulty of the game, which determines the amount of mines in addition to the field size.
	*/
	void setDifficulty(Difficulty dif) {
		if (dif.name == "custom") {
			std::cout << rang::fg::cyan << rang::style::bold << "Field Width: " << rang::style::reset;
			std::cin >> dif.field_width;
			std::cout << rang::fg::cyan << rang::style::bold << "Field Hieght: " << rang::style::reset;
			std::cin >> dif.field_height;
			std::cout << rang::fg::red << rang::style::bold << "Mine Percentage: " << rang::style::reset;
			std::cin >> dif.mine_percentage;
		}
		FIELD_WIDTH = dif.field_width;
		FIELD_HEIGHT = dif.field_height;
		MINE_COUNT = (FIELD_WIDTH * FIELD_HEIGHT) * ((float)dif.mine_percentage / 100);
	}

	/**
	* Generates the field_data values based off of the previously generated mine values.
	* Note: This algorithm is hell. Please do not touch unless you are ABSOLUTELY SURE of what you're doing.
	*		This algorithm took me over weeks, working on it multiple times a week for a couple months
	*/
	void generateTileValues() {
		int adjacent_mines;
		// Iterate through the field tile-by-tile
		for (int x = 0; x < FIELD_WIDTH; x++) {
			for (int y = 0; y < FIELD_HEIGHT; y++) {
				adjacent_mines = 0;
				// search surrounding boxes for mines w/out OOB errors
				for (int dx = (x > 0 ? -1 : 0); dx <= (x < FIELD_WIDTH - 1 ? 1 : 0); ++dx) {
					for (int dy = (y > 0 ? -1 : 0); dy <= (y < FIELD_HEIGHT - 1 ? 1 : 0); ++dy) {
						// forgot what this did
						if (dx != 0 || dy != 0) {
							if (field_data[x + dx][y + dy] == -1) {
								adjacent_mines++;
							}
						}
					}
				}
				// negate the mine itself from the numbering process
				if (field_data[x][y] != -1) {
					field_data[x][y] = adjacent_mines;
				}
			}
		}
	}

	/**
	* Initializes a new field, based upon the type provided.
	* TODO?: Consider utilizing pointers for efficiency. Don't make this a priority
	*/
	template <typename T>
	std::vector<std::vector<T>> fieldInit(T type_default) {
		std::vector<std::vector<T>> new_field(FIELD_WIDTH, std::vector<T>(FIELD_HEIGHT, type_default));
		return new_field;
	}


	// ======================================== DISPLAY ========================================
	// NOTE: dont bother commenting, this will be replaced with a custom ui
	//		i wanted to use a previously made library, but they all suck
public:
	void fieldDisplayPlayer() {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			for (int y = 0; y < FIELD_HEIGHT; y++) {
				if (field_player[x][y] == 1) {
					printTile(field_data[x][y]);
				}
				else {
					printTile(0);
				}
			}
			std::cout << '\n';
		}
		
	}

	void fieldDisplayData() {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			for (int y = 0; y < FIELD_HEIGHT; y++) {
				printTile(field_data[x][y]);
			}
			std::cout << '\n';
		}
	}

	void printTile(int tile) {
		switch (tile) {
		case -1: // mine
			std::cout << " " << rang::bgB::red << " ";
			break;
		case -2: // flag
			std::cout << " " << rang::bgB::green << " ";
			break;
		case 0:
			std::cout << " " << rang::style::dim << "-";
			break;
		case 1:
			std::cout << " " << rang::fgB::blue << tile;
			break;
		case 2:
			std::cout << " " << rang::fgB::cyan << tile;
			break;
		case 3:
			std::cout << " " << rang::fgB::green << tile;
			break;
		case 4:
			std::cout << " " << rang::fgB::yellow  << tile;
			break;
		case 5:
			std::cout << " " << rang::fgB::red << tile;
			break;
		case 6:
			std::cout << " " << rang::fgB::magenta << tile;
			break;
		case 7:
			std::cout << " " << rang::fgB::cyan << rang::bg::gray << tile;
			break;
		case 8:
			std::cout << " " << rang::fgB::yellow << rang::bg::gray << tile;
			break;
		default:
			std::cout << " " << rang::style::bold << tile;
			break;
		}
		std::cout << rang::style::reset;
	}

private:
	void showTile(int x, int y) {
		field_player[x][y] = field_data[x][y];
	}
};