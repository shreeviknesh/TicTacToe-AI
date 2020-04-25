# pragma once
#include <iostream>
#include <algorithm>
#include <tuple>
#include <time.h>
const int INF = 10000;

// All possible states of each tile of the board of the game
enum State {
	EMPTY,
	PLAYER_ONE,
	PLAYER_TWO
};

// A class that holds (row, col) values
class Move {
public:
	int row, col;
	// Default constructor
	Move() : row(-1), col(-1) {};
	// Parameterized constructor
	Move(int r, int c) : row(r), col(c) {};
	// Copy constructor
	Move(Move& move) : row(move.row), col(move.col) {};
	// A function to get the move input from the user
	void get_input(int** board) {
		while (true) {
			std::cout << "Enter the row [1-3] & col [1-3] for your move: ";
			std::cin >> row >> col;

			if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != State::EMPTY) {
				std::cout << "Enter a valid move - Indices must be in range 1-3 & the spot must be empty" << std::endl;
			}
			else {
				return;
			}
		}
	}
};

// A class that implements TicTacToe game and its minimax AI
class TicTacToe {
private:
	int** board;
	std::string player1, player2;
	int ai, human;

public:
	TicTacToe() {
		// Initializing the "board" (3x3 matrix) of the game
		// Tile::EMPTY - Unoccupied space
		// Tile::PLAYER_ONE - Player 1 has played
		// Tile::PLAYER_TWO - Player 2 has played
		board = new int*[3];
		for (int i = 0; i < 3; i++) {
			board[i] = new int[3];
			for (int j = 0; j < 3; j++) {
				board[i][j] = State::EMPTY;
			}
		}

		player1 = "Player-1";
		player2 = "Player-2";
		ai = State::PLAYER_TWO;
		human = State::PLAYER_ONE;
	}

	// A function to visualize the board as a 3x3 matrix with values.
	void visualize_board() {
		//std::cout << "Visualizing" << std::endl;
		for (int i = 0; i < 3; i++) {
			std::cout << '|';
			for (int j = 0; j < 3; j++) {
				switch (board[i][j]) {
				case State::PLAYER_ONE:
					std::cout << 'X';
					break;
				case State::PLAYER_TWO:
					std::cout << 'O';
					break;
				default:
					std::cout << ' ';
				}
				std::cout << '|';
			}
			std::cout << std::endl;
		}
	}

	// A function to check if any player has won, or game is tied
	int evaluate() {
		int first_player;

		// check all rows
		for (int x = 0; x < 3; x++) {
			first_player = board[x][0];
			if (first_player != State::EMPTY && first_player == board[x][1] && first_player == board[x][2]) {
				return first_player;
			}
		}

		// check all columns
		for (int y = 0; y < 3; y++) {
			first_player = board[0][y];
			if (first_player != State::EMPTY && first_player == board[1][y] && first_player == board[2][y]) {
				return first_player;
			}
		}

		// check diagonals
		first_player = board[0][0];
		if (first_player != State::EMPTY && first_player == board[1][1] && first_player == board[2][2]) {
			return first_player;
		}
		first_player = board[2][0];
		if (first_player != State::EMPTY && first_player == board[1][1] && first_player == board[0][2]) {
			return first_player;
		}

		// check for tie
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// not a terminal state
				if (board[i][j] == State::EMPTY) {
					return -1;
				}
			}
		}

		// game tied
		return 0;
	}

	// A function that gets the minimax value of all moves
	int minimax(int depth, bool toMaximize) {
		int score = evaluate();
			
		// If human has won
		if (score == 1) {
			return -10;
		}

		// If ai has won
		if (score == 2) {
			return 10;
		}

		// If game is tied 
		if (score == 0) {
			return 0;
		}

		if (toMaximize) {
			int best = -INF;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (board[i][j] == State::EMPTY) {
						board[i][j] = ai;
						best = std::max(best, minimax(depth + 1, false));
						board[i][j] = State::EMPTY;
					}
				}
			}
			return best;
		}
		else {
			int best = INF;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (board[i][j] == State::EMPTY) {
						board[i][j] = human;
						best = std::min(best, minimax(depth + 1, true));
						board[i][j] = State::EMPTY;
					}
				}
			}
			return best;
		}
	}

	// A function tot find the best possible move for the computer
	Move find_best_move() {
		int best_val = -INF;
		int move_val = -INF;
		Move best_move;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == State::EMPTY) {
					board[i][j] = ai;
					move_val = minimax(0, false);
					board[i][j] = State::EMPTY;

					if (move_val > best_val) {
						best_move = Move(i, j);
						best_val = move_val;
					}
				}
			}
		}

		return best_move;
	}

	// A function to change the current turn to the other player
	void change_chance(int &current_chance) {
		if (current_chance == State::PLAYER_ONE) {
			current_chance = State::PLAYER_TWO;
		}
		else {
			current_chance = State::PLAYER_ONE;
		}
	}

	// A function to get computer or player choice input
	bool get_if_computer() {
		char player_choice;
		while (true) {
			std::cout << "Do you want to play against computer [y/n]? ";
			std::cin >> player_choice;
			if (player_choice == 'y' || player_choice == 'Y') {
				return true;
			}
			else if (player_choice == 'n' || player_choice == 'N') {
				return false;
			}
			else {
				std::cout << "Invalid choice. ";
			}
		}
	}

	// A function to get player name(s)
	std::pair<std::string, std::string> get_player_names(bool is_computer) {
		std::string a, b;
		std::cout << "Enter first player\'s name: ";
		std::cin >> a;

		if (is_computer) {
			b = "Computer";
		} 
		else {
			std::cout << "Enter second player\'s name: ";
			std::cin >> b;
		}

		return make_pair(a, b);
	}

	// A function to check if the game has ended
	bool check_game_end() {
		int result = evaluate();
		if (result == 0) {
			visualize_board();
			std::cout << "Game tied!" << std::endl;
		}
		else if (result == 1) {
			visualize_board();
			std::cout << player1 << " wins!" << std::endl;
		}
		else if (result == 2) {
			visualize_board();
			std::cout << player2 << " wins!" << std::endl;
		}
		else {
			return false;
		}

		return true;
	}

	// The main loop of the application.
	void play() {
		// Setting random seed
		srand(time(0));

		Move move;
		bool is_computer = get_if_computer();
		std::tie(player1, player2) = get_player_names(is_computer);

		// Randomly deciding who startss
		int current_chance = rand() % 2 + 1;
		std::cout << "By random chance, " << ((current_chance == 1)? player1 : player2) << " is starting." << std::endl;

		while (true) {
			visualize_board();
			std::cout << ((current_chance == State::PLAYER_ONE)? player1 : player2) << "\'s turn: ";

			if (current_chance == State::PLAYER_TWO && is_computer) {
				move = find_best_move();
				std::cout << "Computer plays " << move.row + 1 << " " << move.col + 1 << std::endl;
			}
			else {
				move.get_input(board);
				move.row -= 1;
				move.col -= 1;
			}

			board[move.row][move.col] = current_chance;
			
			if (check_game_end()) {
				std::cout << "Game over!" << std::endl;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Press any key to exit.";
				std::cin.get();
				exit(0);
			}
			else {
				change_chance(current_chance);
			}
		}
	}
};
