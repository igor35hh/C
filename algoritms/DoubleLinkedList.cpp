#include "HeaderDoubleLinkedList.h"

Double_list my_list;

int main() {
	for (int val = 0; val < 5; ++val) {
		my_list.add_front(val);
		my_list.add_rear(val);
		my_list.print();
	}

	my_list.insert_after(-999, 3);
	my_list.print();(-999, 3);

	my_list.remove_val(3);
	my_list.print();(-999, 3);

	while (!my_list.is_empty()) {
		my_list.remove_front();
		my_list.print();
	}

	return 0;
}
