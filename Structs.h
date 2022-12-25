#pragma once

#include<list>
#include<math.h>

struct Pos {
	int x, y;

	Pos(int x, int y) : x(x), y(y) {}

	friend std::ostream& operator<<(std::ostream&, const Pos& pos) {
		std::cout << pos.x << "," << pos.y;
		return std::cout;
	}
};

struct Node {

	Node(Pos pos) : pos(pos) {}

	Pos pos;
	bool isTraversable {true};
	Node* parent {nullptr};
	double G = 0.0, H { 0.0 };
	std::list<Node*> neighbours;
	
	double Fcost() {
		return G + H;
	}

	//Only for calcuating distances from immediate (horizontal, vertical or diagonal) neighbours.
	double dist(Node* n) {
		if (pos.x == n->pos.x || pos.y == n->pos.y)
			return 1;
		return sqrt(2);
	}
	bool operator<(Node& node) {
		return this->Fcost() < node.Fcost();
	}

	void setH(Pos target) {
		double dist = 0.0;
		int dx = abs(this->pos.x - target.x),
			dy = abs(this->pos.y - target.y);

		int ddiag = std::min(dx, dy);	//'ddiag' gives the number of diagonal steps.
		dist += ddiag * sqrt(2);

		int dstraight = std::max(dx, dy) - ddiag;	//'dstraight' gives the number of straight steps.
		dist += dstraight;

		H = dist;
	}
};