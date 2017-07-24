#include "HeaderDoubleLinkedListTemplate.h"

Double_list<int> the_list;

int main() {

	int ret = 0;

	Double_list<int>::iterator list_iter;

	for (int j = 0; j < 5; ++j) {
		the_list.add_front(j);
	}

	the_list.print();

	for (list_iter = the_list.front(); list_iter != the_list.rear(); ++list_iter) {
		cout << *list_iter << " ";
	}

	cout << endl;

	for (list_iter = the_list.rear(); list_iter != the_list.front() ;) {
		--list_iter;
		cout << *list_iter << " ";
	}

	cout << endl;

	return 0;

}
