#pragma once
#include <vector>

// enum class GLIB : char {
// 	SGL = '1', VLKN = '2', DX11 = '3',
// 	DX12 = '4', SFML = '5', SDL = '6',
// 	RAYLIB = '7', NONE = '0'
// };

struct Point {
	int x;
	int y;
	Point(int _x, int _y) : x(_x), y(_y) {}
	Point() : x(0), y(0) {}

    // Compares 'x' first, then 'y' if 'x' is equal
    auto operator<=>(const Point&) const = default;
};

struct Node {
	Point pos;
	int data;
	Node(Point _pos, int _data) : pos(_pos), data(_data) {}
	Node() : pos(), data(0) {}

	// Member-wise comparison: compares 'pos' first (using Point's <=>), then 'data'
    auto operator<=>(const Node&) const = default;
};

class Quad {
	Point topLeft;
	Point botRight;

	// Store multiple nodes per leaf until capacity is exceeded
	std::vector<Node*> nodes;
	bool subdivided{ false };

	Quad* topLeftTree;
	Quad* topRightTree;
	Quad* botLeftTree;
	Quad* botRightTree;

	static constexpr int NODE_CAPACITY = 4;

	bool inBoundary(Point p);
	void subdivide();
	void insertIntoChildren(Node* node);
	int totalNodes{ 0 };
public:
	Quad();

	Quad(Point topL, Point botR);

	void insert(Node* node);

	Node* search(Point p);
	void incrementTotalNodes();
	void incrementTotalNodes(int nodeCount);
	int nodeCount() const;
	// Accessors for visualization
	Point getTopLeft() const;
	Point getBotRight() const;
	Node* getNode() const; // returns first node in this leaf (if not subdivided)
	const std::vector<Node*>& getNodes() const;
	Quad* getTopLeftTree() const;
	Quad* getTopRightTree() const;
	Quad* getBotLeftTree() const;
	Quad* getBotRightTree() const;
};