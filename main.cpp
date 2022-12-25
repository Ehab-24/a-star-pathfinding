
#include<iostream>
#include<unordered_set>

#include"Structs.h"
#include"Utility.h"
#include"AStarPathFinding.h"

using namespace std;


void loadGrid(Node***& grid, int& rows, int& cols) {

	grid = new Node **[rows];
	for (int r = 0; r < rows; r++) {
		grid[r] = new Node * [cols];
		for (int c = 0; c < cols; c++) {
			grid[r][c] = new Node(Pos(r, c));
		}
	}

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (c != 0) {
				grid[r][c]->neighbours.push_back(grid[r][c - 1]);
			}
			if (c != cols - 1) {
				grid[r][c]->neighbours.push_back(grid[r][c + 1]);
			}
			if (r != 0) {
				grid[r][c]->neighbours.push_back(grid[r - 1][c]);
			}
			if (r != rows - 1) {
				grid[r][c]->neighbours.push_back(grid[r + 1][c]);
			}
			if (c != 0 && r != 0) {
				grid[r][c]->neighbours.push_back(grid[r - 1][c - 1]);
			}
			if (c != 0 && r != rows - 1) {
				grid[r][c]->neighbours.push_back(grid[r + 1][c - 1]);
			}
			if (c != cols - 1 && r != 0) {
				grid[r][c]->neighbours.push_back(grid[r - 1][c + 1]);
			}
			if (c != cols - 1 && r != rows - 1) {
				grid[r][c]->neighbours.push_back(grid[r + 1][c + 1]);
			}
		}
	}

	grid[0][0]->isTraversable = false;
	for (int i = 0; i <= 4; i++) {
		grid[1][i]->isTraversable = false;
	}
}

void displayGrid(Node*** grid, int rows, int cols) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (!grid[r][c]->isTraversable) {
				setColor(3);
				cout << grid[r][c]->pos << "  -  ";
				setColor(7);
			}
			else {
				cout << grid[r][c]->pos << "  -  ";
			}
		}
		cout << "\n";
	}
}




int main() {

	Node*** grid;
	int rows = 5, cols = 6;

	loadGrid(grid, rows, cols);

	Node* target = grid[0][1], * startingNode = grid[3][4];

	cout << "Starting node: " << startingNode->pos.x << ", " << startingNode->pos.y << "\n"
		<< "Target: " << target->pos.x << ", " << target->pos.y << "\n"
		<< "Obstacles are shown in blue.\n\n";

	displayGrid(grid, rows, cols);

	findTarget(grid, rows, cols, startingNode, target);

	while (target != nullptr) {
		cout << target->pos << "<-";
		target = target->parent;
	}
	cout << "\n";

	return 0;
}