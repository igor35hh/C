
#include <iostream>
#include "HeaderSimplyLinkedList.h"
using namespace std;

void print_slist(const Single_list & sl) {
	int list_size = sl.size();
	if(list_size == 0) {
		printf("empty list\n");
	} else {
		int elt = 1;
		while(elt <= list_size) {
			printf("%d ", sl.get_nth(elt++));
		}
		printf("\n");
	}
}

Single_list my_list;

int main() {

	for(int val = 0; val < 5; ++val) {
		my_list.add_front(val);
		print_slist(my_list);
	}

	cout << "**********" << endl;

	while(!my_list.is_empty()) {
		print_slist(my_list);
		my_list.remove_front();
	}

	return 0;
}
