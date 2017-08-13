#include "BinaryTreeHeader.h"

Binary_tree<int> my_bt(7);

void populate() {
	my_bt.add(5);
	my_bt.add(9);
	my_bt.add(6);
	my_bt.add(4);
	my_bt.add(11);
	my_bt.add(8);
	my_bt.add(2);
	my_bt.add(10);
	my_bt.add(19);
}

int main() {

	populate();
	my_bt.print();

	cout << endl;
	cout << "Pre-order: ";
	my_bt.print_pre_order();

	cout << "Post-order: ";
	my_bt.print_post_order();

	cout << "In-order: ";
	my_bt.print_in_order();

	cout << "In-order, using get_nth(int):" << endl;
	cout << "            ";

	int i;
	for (i = 1; i <= my_bt.size(); ++i) {
		cout << my_bt.get_nth(i) << "  ";
	}

	cout << endl; cout << endl;

	my_bt.remove(2);
	cout << "===================================" << endl;
	cout << " removed 2";
	my_bt.print();

	my_bt.remove(7);
	cout << "===================================" << endl;
	cout << " removed 7";
	my_bt.print();

	return 0;
}
