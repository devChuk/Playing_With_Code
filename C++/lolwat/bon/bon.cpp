//Brian Chuk
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <math.h>
using namespace std;

void mazeRecurse(vector<vector<char>>& maze, int i, int j) {
	if (maze[i][j] == 'e') {
		return true;
		cout << "e: " << i << " " << j << endl;
	}
	if (j < maze[i].size() && maze[i][j+1] != 'x') {
		maze[i][j] = 'x';
		mazeRecurse(maze, i, j + 1);
		mazeRecurse(maze, i, j);
	}
	if (j >= 0 && maze[i][j-1] != 'x') {
		maze[i][j] = 'x';
		mazeRecurse(maze, i, j - 1);	
		mazeRecurse(maze, i, j);
	}
	if (i >= 0 && maze[i-1][j] != 'x') {
		maze[i][j] = 'x';
		mazeRecurse(maze, i-1, j);	
		mazeRecurse(maze, i, j);
	}
	if (i < maze.size() && maze[i+1][j] != 'x') {
		maze[i][j] = 'x';
		mazeRecurse(maze, i+1, j);	
		mazeRecurse(maze, i, j);
	}
}

void mazeRecurse(vector<vector<char>>& maze) {
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

void mazeStack(vector<vector<char>>& maze) {
	std::stack<int> mystack;	
}

/*
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
	// string thing = "xxxxxxxxxxxxxxxxxx\ns.x...x....x...exx\nx.x.x.x.xx.x..xxxx\nx...x...xx.x..x.xx\nxxx.x..xxx...xx.xx\nxxx.xx..xx......xx\nxxx...x.xxxxxxxxxx\nxxxxx.x........xxx\nxxxxxxxxxxxxxxxxxx";
	// cout << thing << endl;
	vector<vector<char>> maze;

	char a[] = {'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'};
	char b[] = {'s','.','x','.','.','.','x','.','.','.','.','x','.','.','.','e','x','x'};
	char c[] = {'x','.','x','.','x','.','x','.','x','x','.','x','.','.','x','x','x','x'};
	char d[] = {'x','.','.','.','x','.','.','.','x','x','.','x','.','.','x','.','x','x'};
	char e[] = {'x','x','x','.','x','.','.','x','x','x','.','.','.','x','x','.','x','x'};
	char f[] = {'x','x','x','.','x','x','.','.','x','x','.','.','.','.','.','.','x','x'};
	char g[] = {'x','x','x','.','.','.','x','.','x','x','x','x','x','x','x','x','x','x'};
	char h[] = {'x','x','x','x','x','.','x','.','.','.','.','.','.','.','.','x','x','x'};
	char i[] = {'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'};
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

	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[i].size(); j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}

	mazeRecurse(maze);

	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[i].size(); j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}


}