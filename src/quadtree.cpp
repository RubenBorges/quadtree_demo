#include <quadtree.hpp>
#include <cmath>
#include <algorithm>

// Private helpers
bool Quad::inBoundary(Point p) {
	return p.x >= topLeft.x && p.x <= botRight.x &&
		p.y >= topLeft.y && p.y <= botRight.y;
}

void Quad::subdivide() {
	if (subdivided) return;

	int midX = (topLeft.x + botRight.x) / 2;
	int midY = (topLeft.y + botRight.y) / 2;

	topLeftTree  = new Quad(topLeft, Point(midX, midY));
	topRightTree = new Quad(Point(midX, topLeft.y), Point(botRight.x, midY));
	botLeftTree  = new Quad(Point(topLeft.x, midY), Point(midX, botRight.y));
	botRightTree = new Quad(Point(midX, midY), botRight);
	subdivided = true;

	for (Node* n : nodes) {
		insertIntoChildren(n);
	}
	nodes.clear();
}

void Quad::traverse(const std::function<void(const Quad*)>& callback) const {
    callback(this);	// Execute user-defined lambda function on the current quadrant node

    // If this quadrant has been split, recursively pass the lambda to all child branches
    if (subdivided) {
        if (topLeftTree)  topLeftTree->traverse(callback);
        if (topRightTree) topRightTree->traverse(callback);
        if (botLeftTree)  botLeftTree->traverse(callback);
        if (botRightTree) botRightTree->traverse(callback);
    }
}


void Quad::insertIntoChildren(Node* node) {
	int midX = (topLeft.x + botRight.x) / 2;
	int midY = (topLeft.y + botRight.y) / 2;

	if (node->pos.x <= midX) {
		if (node->pos.y <= midY) {
			if (!topLeftTree) topLeftTree = new Quad(topLeft, Point(midX, midY));
			topLeftTree->insert(node);
		}
		else {
			if (!botLeftTree) botLeftTree = new Quad(Point(topLeft.x, midY), Point(midX, botRight.y));
			botLeftTree->insert(node);
		}
	}
	else {
		if (node->pos.y <= midY) {
			if (!topRightTree) topRightTree = new Quad(Point(midX, topLeft.y), Point(botRight.x, midY));
			topRightTree->insert(node);
		}
		else {
			if (!botRightTree) botRightTree = new Quad(Point(midX, midY), botRight);
			botRightTree->insert(node);
		}
	}
}

// Constructors
Quad::Quad()
	: topLeft(), botRight(), nodes(), subdivided(false),
	topLeftTree(nullptr), topRightTree(nullptr), botLeftTree(nullptr), botRightTree(nullptr) {
}

Quad::Quad(Point topL, Point botR)
	: topLeft(topL), botRight(botR), nodes(), subdivided(false),
	topLeftTree(nullptr), topRightTree(nullptr), botLeftTree(nullptr), botRightTree(nullptr) {
}

// Public methods
void Quad::insert(Node* node) {
	if (!node || !inBoundary(node->pos)) return;
	
    // Check if any existing node shares the same position
    bool duplicate = std::any_of(nodes.begin(), nodes.end(), [node](Node* n) {
        return n->pos == node->pos;
    });

    if (duplicate) return;
	
	//for (auto* n : nodes) if (n->pos == node->pos) return; 
	
	const int w = std::abs(botRight.x - topLeft.x);
	const int h = std::abs(botRight.y - topLeft.y);

	// If this cell is minimal, keep all nodes here; never subdivide further
	if (w <= 1 && h <= 1) {
		nodes.push_back(node);
		return;
	}

	// Store locally until capacity is reached
	if (!subdivided && static_cast<int>(nodes.size()) < NODE_CAPACITY) {
		nodes.push_back(node);
		return;
	}

	// Exceeded capacity; subdivide once and redistribute
	if (!subdivided) {
		subdivide();
	}

	insertIntoChildren(node);
}

Node* Quad::search(Point p) {
	if (!inBoundary(p)) return nullptr;

	if (!subdivided) {
		for (Node* n : nodes) {
			if (n->pos.x == p.x && n->pos.y == p.y) return n;
		}
		return nullptr;
	}

	int midX = (topLeft.x + botRight.x) / 2;
	int midY = (topLeft.y + botRight.y) / 2;

	if (p.x <= midX) {
		if (p.y <= midY)
			return topLeftTree ? topLeftTree->search(p) : nullptr;
		else
			return botLeftTree ? botLeftTree->search(p) : nullptr;
	}
	else {
		if (p.y <= midY)
			return topRightTree ? topRightTree->search(p) : nullptr;
		else
			return botRightTree ? botRightTree->search(p) : nullptr;
	}
}
void Quad::incrementTotalNodes() {
	totalNodes++;
}

void Quad::incrementTotalNodes(int nodeCount) {
	totalNodes += nodeCount;
}

// Accessors
int Quad::nodeCount() const {return totalNodes;}
Point Quad::getTopLeft() const { return topLeft; }
Point Quad::getBotRight() const { return botRight; }
Node* Quad::getNode() const { return nodes.empty() ? nullptr : nodes.front(); }
const std::vector<Node*>& Quad::getNodes() const { return nodes; }
Quad* Quad::getTopLeftTree() const { return topLeftTree; }
Quad* Quad::getTopRightTree() const { return topRightTree; }
Quad* Quad::getBotLeftTree() const { return botLeftTree; }
Quad* Quad::getBotRightTree() const { return botRightTree; }