#include "BalancedBinaryTreeHeader.h"

Avl_tree<int> my_avlt;

void populate() {
	my_avlt.add(1);
	my_avlt.add(2);
	my_avlt.add(3);
	my_avlt.add(4);
	my_avlt.add(5);
	my_avlt.add(6);
	my_avlt.add(7);
}

int main() {
	populate();

	my_avlt.print();

	my_avlt.remove(1);
	my_avlt.remove(2);
	my_avlt.remove(3);

	my_avlt.print();

	return 0;
}
