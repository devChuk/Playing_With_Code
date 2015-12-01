#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
	using namespace std;

bool isDistinct(string s) {
	for (int i = 0; i < s.length(); i++) {
		for (int j = i + 1; j < s.length(); j++) {
			if (s[i] == s[j]) {
				return false;
			}
		}
	}
	return true;
}


// int charArray [256];
// 	for (int i = 0; i < sizeof(charArray)/4; i++) {
// 		charArray[i] = 0;
// 		cout << charArray[i] << endl;
// 	}

string compress(string s) {
	string ans = "";
	int index = 0;
	while (index < s.length()) {
		char letter = s.at(index);
		int count = 0;
		while (index < s.length() && s.at(index) == letter) {
			count++;
			index++;
		}
		ans += letter;
		ans += to_string(count);
	}
	return ans;
}

void printMatrix(vector<vector<int>> &matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void FourNMatrix(vector<vector<int>> &matrix) {
	srand(time(NULL));
	for (int i = 0; i < 4; i++) {
		vector<int> test;
		for (int i = 0; i < 4; i++) {
			test.push_back(rand() % 10);
		}
		matrix.push_back(test);
	}
}

struct matrixPointer {
	int x;
	int y;
};

void setZeroes(vector<vector<int>> &matrix) {
	vector<matrixPointer> zeroes;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			if (matrix[i][j] == 0) {
				matrixPointer zero;
				zero.x = i; zero.y = j;
				zeroes.push_back(zero);
			}
		}
	}

	for (int i = 0; i < zeroes.size(); i++) {
		int x = zeroes[i].x;
		int y = zeroes[i].y;

	}
}

void rotate(vector<vector<int>> &matrix) {
	int count = 0;
	while (count <= matrix.size() / 2) {
		matrixPointer topLeft, topRight, botLeft, botRight;
		topLeft.x = count; topLeft.y = count;
		botRight.x = matrix.size() - 1 - count; botRight.y = botRight.x;

		count++;
	}
}

//vector<vector<int>> matrix;

int fib(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}

vector<int> sumP(vector<vector<int>> &matrix) {
	vector<int> ans;
	for (int i = 0; i < matrix.size(); i++) {
		int sum1 = 0;
		int sum2 = 0;
		for (int j = 0; j < matrix[i].size(); j++) {
			sum1 += matrix[i][j];
			sum2 += matrix[j][i];
		}
		ans.push_back(sum1);
		ans.push_back(sum2);
	}

	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
	cout << endl;
	return ans;
}

long sqrt(int n) {
	int low = 0;
	int high = n + 1;
	while (high - low > 1) {
		int mid = (high + low) / 2;
		if (mid * mid <= n)
			low = mid;
		else
			high = mid;
	}
	return low;
}

int main () {
	// vector<vector<int>> matrix;
	// FourNMatrix(matrix);
	// printMatrix(matrix);
	// cout << "\n" << endl;
	// sumP(matrix);

	
}