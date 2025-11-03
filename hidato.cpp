#include <bits/stdc++.h>
#include <iomanip>   // For setw()

using namespace std;

int R, C;
vector<vector<int>> grid;

// Directions for 8 adjacent cells
int dr[8] = {-1,-1,-1,0,0,1,1,1};
int dc[8] = {-1,0,1,-1,1,-1,0,1};

bool inBounds(int r, int c) {
    return (r >= 0 && c >= 0 && r < R && c < C);
}

bool solve(int num, int maxNum) {
    if (num == maxNum) return true;

    int r = -1, c = -1;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == num) {
                r = i; c = j;
                break;
            }
        }
        if (r != -1) break;
    }

    if (r == -1) return false;

    for (int k = 0; k < 8; k++) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        if (!inBounds(nr, nc) || grid[nr][nc] == -1) continue;

        if (grid[nr][nc] == num + 1) {
            if (solve(num + 1, maxNum)) return true;
        } 
        else if (grid[nr][nc] == 0) {
            grid[nr][nc] = num + 1;
            if (solve(num + 1, maxNum)) return true;
            grid[nr][nc] = 0;
        }
    }

    return false;
}

int main() {
    vector<vector<int>> input = {
        {  0, 44, 41,  0,  0,  0,  0 },
        {  0, 43,  0, 28, 29,  0,  0 },
        {  0,  1,  0,  0,  0, 33,  0 },
        {  0,  2, 25,  4, 34, 36,  0 },
        { 49, 16, 23,  0,  0,  0,  0 },
        {  0, 19,  0, 12,  7,  0,  0 },
        {  0,  0, 14,  0,  0,  0,  0 }
    };

    grid = input;
    R = grid.size();
    C = grid[0].size();

    int maxNum = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (grid[i][j] > maxNum) maxNum = grid[i][j];

    if (solve(1, maxNum)) {
        cout << "✅ Solved Hidato:\n\n";
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == -1) cout << " XX";
                else cout << setw(3) << grid[i][j];
            }
            cout << "\n";
        }
    } else {
        cout << "❌ No solution found.\n";
    }

    return 0;
}
