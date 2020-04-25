# pragma once
#include <iostream>
#include <algorithm>
#include <tuple>
const int INF = 10000;

enum State {
	EMPTY,
	PLAYER_ONE,
	PLAYER_TWO
};

class Move {
public:
	int row, col;
	Move() : row(-1), col(-1) {};
	Move(int r, int c) : row(r), col(c) {};
	Move(Move& move) : row(move.row), col(move.col) {};
	void get_input() {
		std::cout << "Enter the row (1..3) & col (1..3) for your move: ";
		std::cin >> row >> col;
	}
};

class TicTacToe {
private:
	int** board;

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
	}

	int check_if_same(int x, int y, int dx, int dy) {
		int first_field = board[x][y];

		// If that first field is empty, it means that the row/col/diagonal cannot form a winner
		if (first_field == State::EMPTY) {
			return 0;
		}

		int i, cur_x, cur_y;
		for (i = 0; i < 3; i++) {
			cur_x = x + (i * dx);
			cur_y = y + (i * dy);

			if (board[cur_x][cur_y] != first_field) {
				return 0;
			}
		}

		// winner
		return first_field;
	}

	// A function to check if any player has won, or game is tied
	int evaluate() {
		int result = 0;

		// check all rows
		for (int x = 0; x < 3; x++) {
			result = check_if_same(x, 0, 0, 1);
			if (result != 0) {
				return result;
			}
		}

		// check all columns
		for (int y = 0; y < 3; y++) {
			result = check_if_same(0, y, 1, 0);
			if (result != 0) {
				return result;
			}
		}

		// check diagonals
		result = check_if_same(0, 0, 1, 1);
		if (result != 0) {
			return result;
		}
		result = check_if_same(2, 0, -1, 1);
		if (result != 0) {
			return result;
		}

		// check for tie
		result = -1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == State::EMPTY) {
					result = 0;
					break;
				}
			}
		}

		// either tied (result = -1) or not terminal state (result = 0)
		return result;
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

	// A function that gets the minimax value of all moves
	int minimax(int depth, bool toMaximize, int player, int opponent) {
		int score = evaluate();

		// If player-1 has won
		if (score == 1) {
			return score;
		}

		// If player-2 has won
		if (score == 2) {
			return score;
		}

		// If game is tied 
		if (score == -1) {
			return score;
		}

		if (toMaximize) {
			int best = -INF;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (board[i][j] == State::EMPTY) {
						board[i][j] = player;
						best = std::max(best, minimax(depth + 1, !toMaximize, player, opponent));
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
						board[i][j] = opponent;
						best = std::max(best, minimax(depth + 1, !toMaximize, player, opponent));
						board[i][j] = State::EMPTY;
					}
				}
			}
			return best;
		}
	}

	Move find_best_move() {
		int player = State::PLAYER_TWO;
		int opponent = State::PLAYER_ONE;
		int best_val = -INF, move_val;
		Move best_move;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == State::EMPTY) {
					board[i][j] = player;
					move_val = minimax(0, false, player, opponent);
					board[i][j] = State::EMPTY;

					if (move_val > best_val) {
						best_move = Move(i+1, j+1);
						best_val = move_val;
					}
				}
			}
		}
		return best_move;
	}

	void change_chance(int &current_chance) {
		if (current_chance == State::PLAYER_ONE) {
			current_chance = State::PLAYER_TWO;
		}
		else {
			current_chance = State::PLAYER_ONE;
		}
	}

	// Get computer or player choice input
	bool get_if_computer() {
		char player_choice;
		std::cout << "Do you want to play against computer [y/n]? ";
		while (true) {
			std::cin >> player_choice;
			if (player_choice == 'y' || player_choice == 'Y') {
				return true;
			}
			else if (player_choice == 'n' || player_choice == 'N') {
				return false;
			}
			else {
				std::cout << "Invalid choice.";
			}
		}
	}

	// Get player name(s)
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

	// The main loop of the application.
	void play() {
		int result = 0;
		int current_chance;
		std::string player1, player2;
		Move move, temp;

		bool is_computer = get_if_computer();
		std::tie(player1, player2) = get_player_names(is_computer);

		int random_choice = rand() % 2 + 1;
		if (random_choice == 1) {
			current_chance = State::PLAYER_ONE;
			std::cout << "By random chance, " << player1 << " is starting." << std::endl;
		} 
		else {
			current_chance = State::PLAYER_TWO;
			std::cout << "By random chance, " << player2 << " is starting." << std::endl;
		}

		while (result == 0) {
			visualize_board();
			if (current_chance == State::PLAYER_ONE) {
				std::cout << player1;
			}
			else {
				std::cout << player2;
			}
			std::cout << "\'s turn: ";

			if (current_chance == State::PLAYER_TWO && is_computer) {
				temp = find_best_move();
				move = Move(temp.row + 1, temp.col + 1);
				std::cout << "Computer plays " << move.row << " " << move.col << std::endl;
			}
			else {
				move.get_input();
				if (move.row < 1 || move.row > 3 || move.col < 1 || move.col > 3 || board[move.row - 1][move.col - 1] != State::EMPTY) {
					std::cout << "Enter a valid move - Indices must be in range 1-3 & the spot must be empty" << std::endl;
					continue;
				}
			}

			board[move.row - 1][move.col - 1] = current_chance;

			result = evaluate();
			if (result == -1) {
				visualize_board();
				std::cout << "Game tied!" << std::endl;
			}
			else if (result == 1) {
				visualize_board();
				std::cout << player1 << " wins!!" << std::endl;
			}
			else if (result == 2) {
				visualize_board();
				std::cout << player2 << " wins!!" << std::endl;
			}
			else {
				change_chance(current_chance);
			}			
		}
	}
};
