#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <iostream>

struct Node {
    int row, col, cost;

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

struct Position {
    int row, col;
};

class PathFinder {
private:
    std::vector<std::string> map;
    int rows, cols;
    Position start, goal;

    // Direction vectors: up, down, left, right
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    bool isValid(int r, int c) {
        return r >= 0 && r < rows && c >= 0 && c < cols;
    }

    int getCost(char cell) {
        if (cell == ' ' || cell == 'F' || cell == '%') return 1;
        if (cell == 'Y') return 4;
        if (cell == '#') return INT_MAX; // Impassable
        return 1; // Default
    }

    bool findStartAndGoal() {
        bool foundStart = false, foundGoal = false;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (map[r][c] == 'F') {
                    start = {r, c};
                    foundStart = true;
                }
                if (map[r][c] == '%') {
                    goal = {r, c};
                    foundGoal = true;
                }
            }
        }

        return foundStart && foundGoal;
    }

    void drawPath(const std::vector<std::vector<Position>>& parent) {
        // Create a copy of the map to draw the path
        std::vector<std::string> pathMap = map;

        // Backtrack from goal to start
        Position current = goal;

        while (!(current.row == start.row && current.col == start.col)) {
            Position prev = parent[current.row][current.col];

            if (prev.row == -1) break; // No parent (shouldn't happen if path exists)

            // Mark the path (but don't overwrite start and goal)
            if (!(current.row == goal.row && current.col == goal.col)) {
                pathMap[current.row][current.col] = '.';
            }

            current = prev;
        }

        // Print the map with path
        for (const std::string& line : pathMap) {
            std::cout << line << std::endl;
        }
    }

public:
    PathFinder(const std::vector<std::string>& inputMap) : map(inputMap) {
        rows = map.size();
        cols = rows > 0 ? map[0].size() : 0;
    }

    bool findPath(int& totalCost) {
        if (!findStartAndGoal()) {
            std::cout << "Error: Could not find start (F) or goal (%)!" << std::endl;
            return false;
        }

        // Initialize distance matrix
        std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INT_MAX));
        std::vector<std::vector<Position>> parent(rows, std::vector<Position>(cols, {-1, -1}));

        // Priority queue: min-heap based on cost
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

        dist[start.row][start.col] = 0;
        pq.push({start.row, start.col, 0});

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            int r = current.row;
            int c = current.col;

            // If we reached the goal
            if (r == goal.row && c == goal.col) {
                totalCost = dist[r][c];
                drawPath(parent);
                return true;
            }

            // If this is not the best path to this cell, skip it
            if (current.cost > dist[r][c]) {
                continue;
            }

            // Explore all 4 directions
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (!isValid(nr, nc)) continue;

                int moveCost = getCost(map[nr][nc]);
                if (moveCost == INT_MAX) continue; // Impassable

                int newDist = dist[r][c] + moveCost;

                if (newDist < dist[nr][nc]) {
                    dist[nr][nc] = newDist;
                    parent[nr][nc] = {r, c};
                    pq.push({nr, nc, newDist});
                }
            }
        }

        // No path found
        return false;
    }
};

#endif // PATHFINDER_H
