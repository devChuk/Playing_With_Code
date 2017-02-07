/*
Tic Tac Toe game
*/
#include <iostream>
#include <vector>
#include <string>
#include <limits>

class TicTacToe {
private:
	std::vector<char> board;
	char currTurn;

public:
	TicTacToe() {
		board = std::vector<char>(9,' ');
		currTurn = 'X';
	}

	void drawBoard() {
		std::cout << "\n\n\nKEY:\n" << "012\n" << "345\n" << "678\n" << std::endl;

		std::cout << currTurn << " Turn" << std::endl;
		std::cout << board[0] << " │ " << board[1] << " │ " << board[2]
                << "\n──┼───┼──\n"
                << board[3] << " │ " << board[4] << " │ " << board[5]
                << "\n──┼───┼──\n"
                << board[6] << " │ " << board[7] << " │ " << board[8]
                << std::endl;
	}

	bool makeMove(const int index) {
		if (board[index] == ' ') {
			board[index] = currTurn;
			switch(currTurn) {
				case 'X':
					currTurn = 'O';
					break;
				case 'O':
					currTurn = 'X';
					break;
			}
			return true;
		} else {
			return false;
		}
	}

	bool isFull() {
		bool result = true;
		for (int i = 0; i < board.size(); i++) {
			if (board[i] == ' ') {
				result = false;
			}
		}
		return result;
	}

	char checkWinner() {
		char result = ' ';	

		int plays[8][3] = {{0,1,2},
						   {3,4,5},
						   {6,7,8},
						   {0,3,6},
						   {1,4,7},
						   {2,5,8},
						   {0,4,8},
						   {2,4,6}};
		for (int i = 0; i < 8; i++) {
			if (board[plays[i][0]] != ' ' &&
				board[plays[i][0]] == board[plays[i][1]] &&
				board[plays[i][1]] == board[plays[i][2]]) {
				result = board[plays[i][0]];
				break;
			}
		}

		if (result == ' ' && isFull()) {
			result = 'D';
		}

		return result;
	}
};


int main() {
	char winner = ' ';
	TicTacToe game = TicTacToe();
	std::cout << "Tic Tac Toe" << std::endl;
	std::cout << "Ctrl+C to exit" << std::endl;
	game.drawBoard();

	while (winner == ' ') {
		int index;
		std::cin >> index;

		while (std::cin.fail() || index > 8 || index < 0 || !game.makeMove(index)) {
			std::cout << "INVALID INPUT! Please try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> index;
		}

		winner = game.checkWinner();
		game.drawBoard();
	}

	if (winner == 'D') {
		std::cout << "DRAW" << std::endl;
	} else {
		std::cout << "WINNER: " << winner << std::endl;
	}
}