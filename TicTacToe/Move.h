#pragma once

/* All possible states of each tile of the board of the game */
enum State {
	EMPTY,
	PLAYER_ONE,
	PLAYER_TWO
};

/* A class that holds (row, col) values */
class Move {
public:
	int row, col;
	
	/* Default constructor */
	Move() : row(-1), col(-1) {
	};
	
	/* Parameterized constructor */
	Move(int r, int c) : row(r), col(c) {
	};
	
	/* Copy constructor */
	Move(Move& move) : row(move.row), col(move.col) {
	};

	/* A function to get the move input from the user */
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
