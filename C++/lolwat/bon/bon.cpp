//Brian Chuk
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <stack>
#include <math.h>
using namespace std;

void mazeRecurse(vector<vector<char>>& maze, int i, int j) { //The recursive function. It's pretty self explanatory.
	if (maze[i][j] == 'e') {
		cout << "e: " << i << " " << j << endl;
		maze[i][j] = 'x';
	}
	else {
		if (j < maze[i].size() && maze[i][j+1] != 'x') {
			maze[i][j] = 'x';
			mazeRecurse(maze, i, j + 1);
			cout << i << " " << j;
		}
		if (j > 0 && maze[i][j-1] != 'x') {
			maze[i][j] = 'x';
			mazeRecurse(maze, i, j - 1);
			cout << i << " " << j;
		}
		if (i > 0 && maze[i-1][j] != 'x') {
			maze[i][j] = 'x';
			mazeRecurse(maze, i-1, j);
			cout << i << " " << j;
		}
		if (i < maze.size() && maze[i+1][j] != 'x') {
			maze[i][j] = 'x';
			mazeRecurse(maze, i+1, j);
			cout << "|" << i << " " << j;
		}
	}
}

void mazeRecurse(vector<vector<char>>& maze) { //The driver func: searches for the 's' via brute force and starts recursive finder
	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[i].size(); j++) {
			if (maze[i][j] == 's') {
				cout << "s: "<< i << " " << j << endl;
				mazeRecurse(maze, i, j);
				return;
			}
		}
	}
}

struct coords {
	coords(int a, int b) {i = a; b = j;}
	int i, j;
};

void mazeStack(vector<vector<char>>& maze, int i, int j) { //loc_finder with a stack

}

void mazeStack(vector<vector<char>>& maze) { //The driver func: searches for the 's' via brute force and starts stack finder
	int i;
	int j;
	for (int a = 0; a < maze.size(); a++) {
		for (int b = 0; b < maze[a].size(); b++) {
			if (maze[a][b] == 's') {
				i = a; j = b;
			}
		}
	}
	cout << "s: "<< i << " " << j << endl;
	stack<coords> stack;
	// coords yo(4,3);
	// cout << yo.i << endl;
}

/*
This is an example maze
xxxxxxxxxxxxxxxxxx
s.x...x....x...exx
x.x.x.x.xx.x..xxxx
x...x...xx.x..x.xx
xxx.x..xxx...xx.xx
xxx.xx..xx......xx
xxx...x.xxxxxxxxxx
xxxxx.x........xxx
xxxxxxxxxxxxxxxxxx
*/

//6 

int main() {
	vector<vector<char>> maze;

	char a[] = {'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'};
	char b[] = {'s','.','x','.','.','.','x','.','.','.','.','x','.','.','.','e','x','x'};
	char c[] = {'x','.','x','.','x','.','x','.','x','x','.','x','.','.','x','x','x','x'};
	char d[] = {'x','.','.','.','x','.','.','.','x','x','.','x','.','.','x','.','x','x'};
	char e[] = {'x','x','x','.','x','.','.','x','x','x','.','.','.','x','x','.','x','x'};
	char f[] = {'x','x','x','.','x','x','.','.','x','x','.','.','.','.','.','.','x','x'};
	char g[] = {'x','x','x','.','.','.','x','.','x','x','x','x','x','x','x','x','x','x'};
	char h[] = {'x','x','x','x','x','.','x','.','.','.','.','.','.','.','x','x','x','x'};
	char i[] = {'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'}; //it was 4 AM in the morning lolol
	std::vector<char> aa (a, a + sizeof(a) / sizeof(char));maze.push_back(aa);
	std::vector<char> bb (b, b + sizeof(b) / sizeof(char));maze.push_back(bb);
	std::vector<char> cc (c, c + sizeof(c) / sizeof(char));maze.push_back(cc);
	std::vector<char> dd (d, d + sizeof(d) / sizeof(char));maze.push_back(dd);
	std::vector<char> ee (e, e + sizeof(e) / sizeof(char));maze.push_back(ee);
	std::vector<char> ff (f, f + sizeof(f) / sizeof(char));maze.push_back(ff);
	std::vector<char> gg (g, g + sizeof(g) / sizeof(char));maze.push_back(gg);
	std::vector<char> hh (h, h + sizeof(h) / sizeof(char));maze.push_back(hh);
	std::vector<char> ii (i, i + sizeof(i) / sizeof(char));maze.push_back(ii);

	cout << "\n" << endl;

	for (int i = 0; i < maze.size(); i++) {			//prints out the maze
		for (int j = 0; j < maze[i].size(); j++)
			cout << maze[i][j];
		cout << endl;
	}


	// mazeRecurse(maze);							//testFunc for recursive loc_Finder
	mazeStack(maze);								//testFunc for stack loc_Finder
	// mazeQueue(maze);								//testFunc for queue loc_Finder

	for (int i = 0; i < maze.size(); i++) {			//prints out the maze
		for (int j = 0; j < maze[i].size(); j++)
			cout << maze[i][j];
		cout << endl;
	}


}