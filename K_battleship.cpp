#include <bits/stdc++.h>

using namespace std;

struct Ship {
    int rowA, colA, diagA;
};

bool isAttacked(int x1, int y1, int x2, int y2, const Ship& s) {
    // Check if (x2, y2) is attacked by ship at (x1, y1) with params s
    if (x1 == x2) { // Same row
        if (abs(y1 - y2) <= s.rowA) return true;
    }
    if (y1 == y2) { // Same column
        if (abs(x1 - x2) <= s.colA) return true;
    }
    if (abs(x1 - x2) == abs(y1 - y2)) { // Diagonal (both main and anti)
        if (abs(x1 - x2) <= s.diagA) return true;
    }
    return false;
}

bool canPlace(const vector<pair<int, int>>& placed, const Ship& s, int x, int y, int N, int M) {
    // Check if placing s at (x, y) is safe and doesn't attack any placed ship
    for (auto& p : placed) {
        if (isAttacked(p.first, p.second, x, y, s) || isAttacked(x, y, p.first, p.second, s)) return false;
    }
    return true;
}

bool backtrack(vector<pair<int, int>>& placed, const vector<Ship>& ships, int idx, int N, int M) {
    if (idx == ships.size()) return true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (canPlace(placed, ships[idx], i, j, N, M)) {
                placed.push_back({i, j});
                if (backtrack(placed, ships, idx + 1, N, M)) return true;
                placed.pop_back();
            }
        }
    }
    return false;
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<Ship> ships(K);
    for (int i = 0; i < K; i++) {
        cin >> ships[i].rowA >> ships[i].colA >> ships[i].diagA;
    }
    vector<pair<int, int>> placed;
    if (backtrack(placed, ships, 0, N, M)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
