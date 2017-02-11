#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int findMinMoves(int n, int a, int b) {
    vector<vector<bool>> isVisited(n, vector<bool>(n, false));
    vector<array<int, 2>> pD;   // possible directions
    pD.push_back({a, b});
    pD.push_back({b, a});
    pD.push_back({-b, a});
    pD.push_back({a, -b});
    pD.push_back({b, -a});
    pD.push_back({-a, b});
    pD.push_back({-a, -b});
    pD.push_back({-b, -a});
    
    queue<array<int, 3>> queue;
    isVisited[0][0] = true;
    queue.push({0,0,0});
    
    while (!queue.empty()) {
        int x = queue.front()[0];
        int y = queue.front()[1];
        int count = queue.front()[2];
        queue.pop();
        
        if (x == n - 1 && y == n - 1)
            return count;
        
        for (int i = 0; i < 8; i++) {
            int nextX = x + pD[i][0];
            int nextY = y + pD[i][1];
            bool isOnTheBoard = (nextX >= 0) && (nextX < n) && (nextY >= 0) && (nextY < n);
            
            if (isOnTheBoard && !isVisited[nextX][nextY]) {
                isVisited[nextX][nextY] = true;
                queue.push({nextX, nextY, count + 1});
            }
        }        
    }
    
    if (!isVisited[n - 1][n - 1])
        return -1;
    else
        return 0;
}

int main(){
    int n;
    cin >> n;
    
    vector<vector<int>> result;
    result.resize(n-1);
    for (int i = 0; i < result.size(); i++) {
        result[i].resize(n - 1);
    }
    
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            if (result[j][i] > 0) {
                result[i][j] = result[j][i];
            } else {
                result[i][j] = findMinMoves(n, i + 1, j + 1);
            }
        }
    }
    
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
