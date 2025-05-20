
#include <iostream>
#include <vector>
#include <functional>
#include "SegmentTree.h"

double plus(double x, double y) {
	return x + y;
}

int main(void)
{
	std::vector<double> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	SegmentTree<double, std::function<double(double, double)>> tree(vec, plus, double(0.0));

	for (int i = 0; i <= vec.size(); ++i) {
		std::cout << tree.query(0, i) << std::endl;
	}

	tree.show();
}