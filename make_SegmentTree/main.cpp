
#include <iostream>
#include <vector>
#include <functional>
#include "SegmentTree.h"
#include "DequeSegmentTree.h"

float plus(float x, float y) {
	return x + y;
}

void test_DST() {
	DequeSegmentTree<float, std::function<float(float, float)>> tree(10, plus, 0.0);

	for (int i = 1; i < 11; ++i) tree.add(i);

	tree.show();
}

int main(void)
{
	std::vector<float> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	SegmentTree<float,std::function<float(float, float)>> tree(vec, plus, double(0.0));

	for (int i = 0; i <= vec.size(); ++i) {
		std::cout << tree.query(0, i) << std::endl;
	}

	tree.show();

	test_DST();
}