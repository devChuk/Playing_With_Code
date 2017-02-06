#include <iostream>
#include <vector>

class TicTacToe {
	std::vector<int> board;
	enum Player {NONE, PLAYER_ONE, PLAYER_TWO};


	void drawBoard() {

	}

	int checkWinner() {
		Player result = NONE;
		return result;
	}
};


int main() {
	int i;
	std::cin >> i;
	std::cout << i << std::endl;
}