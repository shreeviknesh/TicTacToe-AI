# pragma once
#include <iostream>
#include <algorithm>
#include <tuple>
#include <time.h>

#include "Move.h"

constexpr int INF = 10000;


/* A class that implements TicTacToe game and its minimax AI */ 
class TicTacToe {
private:
	int** board;
	std::string player1, player2;
	int ai, human;

public:
	TicTacToe();

	/* A function to visualize the board as a 3x3 matrix with values. */
	void visualize_board();

	/* A function to check if any player has won, or game is tied */
	int evaluate();

	/* A function that gets the minimax value of all moves */
	int minimax(int depth, bool toMaximize);

	/* A function to find the best possible move for the computer */
	Move find_best_move();

	/* A function to change the current turn to the other player */
	void change_chance(int& current_chance);

	/* A function to get computer or player choice input */
	bool get_if_computer();

	/* A function to get player name(s) */
	std::pair<std::string, std::string> get_player_names(bool is_computer);

	/* A function to check if the game has ended */
	bool check_game_end();

	/* The main loop of the application. */
	void play();
};
