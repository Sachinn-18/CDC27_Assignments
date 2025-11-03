#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool isSafe(vector<int>& board, int currRow,
                                      int currCol) {

    for(int i = 0; i < board.size(); ++i) {
        int placedRow = board[i];
        int placedCol = i + 1;

        if(abs(placedRow - currRow) == abs(placedCol - currCol)) {
            return false;
        }
    }
    return true;
}
void nQueenUtil(int col, int n, vector<int>& board,
  	vector<vector<int>>& res, vector<bool>& visited) {

    if(col > n) {
        res.push_back(board);
        return;
    }
    for(int row = 1; row <= n; ++row) {

        if(!visited[row]) {
            
            
            if(isSafe(board, row, col)) {

                visited[row] = true;

                board.push_back(row);

                nQueenUtil(col + 1, n, board,
                             res, visited);

                board.pop_back();
                
                
                visited[row] = false;
            }
        }
    }
}
vector<vector<int>> nQueen(int n) {
    vector<vector<int>> res;
    vector<int> board;

    vector<bool> visited(n + 1, false);

    nQueenUtil(1, n, board, res, visited);
    return res; 
}

int main() {
    int n = 4; 
    vector<vector<int>> res = nQueen(n); 

    for(int i = 0;i < res.size(); i++) {
        cout << "[";
        for(int j = 0; j < n; ++j) {
            cout << res[i][j]; 
            if(j != n - 1)   cout << " "; 
        }
        cout << "]\n";
    }
    return 0;
}