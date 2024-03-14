#include <iostream>
#include <vector>

using namespace std;


bool isValidMove(int i, int j, int rows, int cols) {
    return 0 <= i && i < rows && 0 <= j && j < cols;
}

void dfs(vector<vector<char>>& mat, vector<vector<bool>>& visited, int i, int j, int& count) {
    visited[i][j] = true;
    count++;

    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (const auto& dir : directions) {
        int ni = i + dir.first;
        int nj = j + dir.second;
        if (isValidMove(ni, nj, mat.size(), mat[0].size()) && !visited[ni][nj] && mat[ni][nj] == '.') {
            dfs(mat, visited, ni, nj, count);
        }
    }
}

int countSecureServers(vector<vector<char>>& mat) {
    int count = 0;

    int start_i, start_j;//procura posicao i0j0
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].size(); ++j) {
            if (mat[i][j] == '@') {
                start_i = i;
                start_j = j;
                break;
            }
        }
    }

    vector<vector<bool>> visited(mat.size(), vector<bool>(mat[0].size(), false));
    dfs(mat, visited, start_i, start_j, count);

    return count;
}

int main() {
    int W, H;
    cin >> W >> H;

    vector<vector<char>> mat(H, vector<char>(W));
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> mat[i][j];
        }
    }

    int result = countSecureServers(mat);
    cout << result << endl;

    return 0;
}
