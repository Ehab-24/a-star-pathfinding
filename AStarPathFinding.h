#pragma once


Node* minIn(std::list<Node*>&list) {
	Node* min = list.front();
	for (Node* n : list) {
		if (*n < *min) {
			min = n;
		}
	}
	return min;
}
bool isPresent(std::list<Node*>& list, Node* node) {
	for (Node* n : list) {
		if (n == node)
			return true;
	}
	return false;
}

void findTarget(Node*** grid, int rows, int cols, Node* startingNode, Node* target) {
//This function sets the parent of each opened node. 
//We can later identify the shortest path by repeatedly
//calling the parent of target node.

	std::unordered_set<Node*> closed;
	std::list<Node*> opened;

	opened.push_back(startingNode);

	Node* current;
	while (true) {

		current = minIn(opened);
		if (current == target) {
			return;
		}
		opened.remove(current);
		closed.insert(current);

		for (Node* n : current->neighbours) {
			if (closed.find(n) != closed.end() || !n->isTraversable)
				continue;

			bool _isPresent = isPresent(opened, n);
			
			if(!_isPresent)
				n->setH(target->pos);

			double	newGCost = current->G + current->dist(n);
			double	newFCost = newGCost + n->H;

			if (!_isPresent || newFCost < n->Fcost()) {
				n->G = newGCost;
				n->parent = current;

				if (!_isPresent) {
					opened.push_back(n);
				}
			}
		}
	}
}