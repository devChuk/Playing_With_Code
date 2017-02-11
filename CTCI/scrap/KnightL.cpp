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


int findMinMoves(int n, int a, int b ) {
    int goal = n - 1;
    
    if (goal % (a + b) == 0) {
        return 2 * (n - 1)/(a + b);
    } else if (a == b) {
        return -1;
    }
    
    int L = max(a,b);
    int S = min(a,b);
    
    vector<array<int, 2>> pD;   // possible directions
    pD.push_back({L, S});
    pD.push_back({S, L});
    pD.push_back({-S, L});
    pD.push_back({L, -S});
    pD.push_back({S, -L});
    pD.push_back({-L, S});
    // in theory this gives the order with the closest move first. May need to do Pythagorean theorem tho

    vector<vector<bool>> isVisited(n, vector<bool>(n, false));
    stack<array<int, 2>> history;
    history.push({0, 0});
    int x = a;
    int y = b;
    int count = 1;
    
    for (int i = goal - 1; i > goal / 2; i--) {
        isVisited[i][i] = true;
    }

    while (x != goal || y != goal) {
        //cout << "befor: " << history.top()[0] << " " << history.top()[1] << " " << x << " " << y << endl;
        // (x,y) is current position. history.top() is previous position
        // generate all possible moves
            // avoid going backwards            check
            // avoid going to banned spots      
            // avoid going off the board
            // avoid going to history
        int nextX = 0;   // possible moves
        int nextY = 0;
        bool newMoveIsPossible = false;
        for (int i = 0; i < 6; i++) {
            nextX = x + pD[i][0];
            nextY = y + pD[i][1];
            
            bool isNotPreviousMove = (nextX != history.top()[0]) || (nextY != history.top()[1]);
            bool isOnTheBoard = (nextX >= 0) && (nextX <= goal) && (nextY >= 0) && (nextY <= goal);
            bool isNotBannedMove = false;
            if (isOnTheBoard)
                isNotBannedMove = !isVisited[nextX][nextY];
            //cout << "(" << nextX << "," << nextY << ")" << isNotPreviousMove << isOnTheBoard <<  isNotBannedMove << endl;
                        
            if (isNotPreviousMove && isNotBannedMove) {
                newMoveIsPossible = true;
                break;
            }
        }
    
        if (newMoveIsPossible) {
            history.push({x, y});
            x = nextX;
            y = nextY;
            count++;
        } else {
            isVisited[x][y] = true;
            x = history.top()[0];
            y = history.top()[1];
            history.pop();
            if (history.empty())
                return -1;
            count--;
        }
        //cout << "after: " << history.top()[0] << " " << history.top()[1] << " " << x << " " << y << "\n"<< endl;

        // sort by closest to goal point        already sorted hopefully
        
        // if a move is possible
            // add x,y move to stack
            // set x,y to best move
            // increment count
        
        // if a move is not possible
            // ban x,y
            // set x,y to stack.top()
            // pop stack
            // decrement count
        
    }
    
    
    return count;
    //return 0;
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
            //cout << "BEHAVIOR:" << i+1 << " " << j+1 << endl;
            if (i == 0 && j ==0) {
                cout << n-1 << " ";
            } else if(i+1 == n-1 && j+1 == n-1) {
                cout << "1 ";
            } else if(i+1 > n/2 && j+1 > n/2) {
                cout << "-1 ";
            } else {
                cout << findMinMoves(n, i + 1, j + 1) << " ";
            }
            
            //cout <<  "\nEND\n" << endl;
        }
        cout << endl;
    }
    
    return 0;
}
/*
            else if (i + j + 2 >= n) {
                cout << "-1 ";
            } 
*/