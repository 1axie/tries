#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;

struct Point {
    int r, c;
    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }
};

class MazeSolver {
private:
    int rows, cols;
    vector<string> grid;
    Point startPos;
    Point flagPos;
    Point goalPos;

    Point findChar(char target) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == target) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

    vector<string> getPath(Point src, Point dest) {
        vector<vector<Point>> parent(rows, vector<Point>(cols, {-1, -1}));
        vector<vector<string>> moveFromParent(rows, vector<string>(cols, ""));
        vector<vector<bool>> vis(rows, vector<bool>(cols, false));

        queue<Point> q;
        q.push(src);
        vis[src.r][src.c] = true;

        int dr[] = {-1,  1,  0,  0};
        int dc[] = { 0,  0, -1,  1};
        string moveNames[] = {"UP", "DOWN", "LEFT", "RIGHT"};

        bool found = false;
        while (!q.empty()) {
            Point curr = q.front();
            q.pop();

            if (curr == dest) {
                found = true;
                break;
            }

            for (int i = 0; i < 4; ++i) {
                int nr = curr.r + dr[i];
                int nc = curr.c + dc[i];

                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                    char cell = grid[nr][nc];
                    bool canPass = (cell == '.' || cell == 'S' || cell == 'F' || cell == 'G');
                    
                    if (canPass && !vis[nr][nc]) {
                        vis[nr][nc] = true;
                        parent[nr][nc] = curr;
                        moveFromParent[nr][nc] = moveNames[i];
                        q.push({nr, nc});
                    }
                }
            }
        }

        vector<string> pathMoves;
        if (!found) return pathMoves;

        Point curr = dest;
        while (!(curr == src)) {
            Point p = parent[curr.r][curr.c];
            string move = moveFromParent[curr.r][curr.c];
            pathMoves.push_back(move);
            curr = p;
        }

        vector<string> finalMoves(pathMoves.rbegin(), pathMoves.rend());
        return finalMoves;
    }

    void printMapWithRobot(Point robotPos) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i == robotPos.r && j == robotPos.c) {
                    cout << "R ";
                } else {
                    cout << grid[i][j] << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void simulateMovement(Point start, const vector<string>& moves) {
        Point curr = start;
        int step = 1;

        for (const string& move : moves) {
            if (move == "UP") curr.r--;
            else if (move == "DOWN") curr.r++;
            else if (move == "LEFT") curr.c--;
            else if (move == "RIGHT") curr.c++;

            cout << "STEP " << step++ << " - MOVE: " << move << " - POSITION (" << curr.r << "," << curr.c << ")" << endl;
            printMapWithRobot(curr);
            
        }
    }

public:
    MazeSolver(const vector<string>& inputGrid) {
        grid = inputGrid;
        rows = grid.size();
        cols = grid[0].size();
        startPos = findChar('S');
        flagPos = findChar('F');
        goalPos = findChar('G');
    }

    void solve() {
        cout << "MAP LOADED : " << rows << " x " << cols << endl;
        cout << "START POSITION : (" << startPos.r << "," << startPos.c << ")" << endl << endl;

        // 1 jalur dari S ke F
        vector<string> pathToFlag = getPath(startPos, flagPos);
        cout << "--- SIMULASI MENUJU FLAG (F) ---" << endl;
        simulateMovement(startPos, pathToFlag);
        cout << "FLAG CAPTURED" << endl << endl;

        // 2. jalur dari F ke G
        vector<string> pathToBase = getPath(flagPos, goalPos);
        cout << "--- SIMULASI MENUJU BASE (G) ---" << endl;
        simulateMovement(flagPos, pathToBase);
        cout << "BASE REACHED" << endl;
        cout << "MISSION COMPLETE" << endl;
        cout << "TOTAL MOVES : " << (pathToFlag.size() + pathToBase.size()) << endl;
    }
};

int main() {
    vector<string> mapSoal1 = {
        "#######",
        "#S....#",
        "###.#.#",
        "#...#.#",
        "#.###.#",
        "#X..F.#",
        "#######"
    };

    MazeSolver robot(mapSoal1);
    robot.solve();

    return 0;
}