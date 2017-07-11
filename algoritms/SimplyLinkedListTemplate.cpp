#include "HeaderSimplyLinkedListTemplate.h"

Single_list<float> my_list;

int main() {

	float f = 0.0;
	for(int val = 0; val<5; ++val) {
		my_list.add_front(f);
		my_list.add_rear(f);
		my_list.print();
		f += 0.1F;
	}

	my_list.reset_current();
	while(!my_list.current_is_tail()) {
		cout << my_list.get_current() << " ";
		my_list.increment_current();
	}

	cout << endl;

	while(!my_list.is_empty()) {
		my_list.remove_front();
		my_list.print();
	}

	return 0;

}
