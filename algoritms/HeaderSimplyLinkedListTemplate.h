#include <cassert>
#include <iostream>

using namespace std;

template <class T>
class Single_list {

private:

	class Single_node {
		friend class Single_list<T>;
		Single_node(T node_val) : val(node_val) {}
		Single_node() {}
		~Single_node() {}
		void print_val() const {cout << val << " ";}
		Single_node *next;
		T val;
	};

	Single_node *head;
	Single_node *tail;
	Single_node *current;

	Single_list & operator=(const Single_list &);
	Single_list(const Single_list &);

	void add_to_empty(T node_val) {
		Single_node *node_to_add = new Single_node(node_val);
		node_to_add->next = head;
		head = node_to_add;
		tail->next = head;
		current = head;
	}

public:

	Single_list() {
		head = tail = new Single_node;
		tail->next = 0;
		current = tail;
	}

	Single_list(T node_val) {
		head = tail = new Single_node;
		tail->next = 0;
		add_to_empty(node_val);
	}

	~Single_list() {
		Single_node *node_to_delete = head;
		for(Single_node *sn = head; sn != tail;) {
			sn = sn->next;
			delete node_to_delete;
			node_to_delete = sn;
		}
		delete node_to_delete;
	}

	bool is_empty() const {
		return head == tail;
	}

	void add_front(T node_val) {
		if(is_empty()) {
			add_to_empty(node_val);
		} else {
			Single_node *node_to_add = new Single_node(node_val);
			node_to_add->next = head;
			head = node_to_add;
		}
	}

	void add_rear(T node_val) {
		if(is_empty()) {
			add_to_empty(node_val);
		} else {
			Single_node *node_to_add = new Single_node(node_val);
			node_to_add->next = tail;
			tail->next->next = node_to_add;
			tail->next = node_to_add;
		}
	}

	T remove_front() {
		if(is_empty()) {
			throw "list is empty";
		}
		Single_node *node_to_remove = head;
		T return_val = node_to_remove->val;
		head = node_to_remove->next;

		if(current == node_to_remove) {
			current = node_to_remove->next;
		}
		delete node_to_remove;
		return return_val;
	}

	bool find(T node_val) const {
		for(Single_node *sn = head; sn != tail; sn = sn->next) {
			if(sn->val == node_val) {
				return true;
			}
		}
		return false;
	}

	T get_nth(const int element_num) const {
		if(element_num<1) {
			throw "no argument";
		}
		int count = 1;
		for(Single_node *sn = head; sn != tail; sn = sn->next) {
			if(count++ == element_num) {
				return sn->val;
			}
		}
		throw "argument exceeds list size";
	}

	int size() const {
		if(is_empty()) {
			return 0;
		}
		int count = 0;
		for(Single_node *sn = head; sn != tail; sn = sn->next) {
			++count;
		}
		return count;
	}

	void print() const {
		for(Single_node *sn = head; sn != tail; sn = sn->next) {
			sn->print_val();
		}
		cout << endl;
	}

	void reset_current() {
		current = head;
	}

	bool increment_current() {
		if(current != tail) {
			current = current->next;
			return true;
		}
		return false;
	}

	T get_current() const {
		return current->val;
	}

	bool current_is_tail() const {
		return current == tail;
	}

	bool insert_after_current(const T node_val) {
		if(current_is_tail()) {
			return false;
		}
		Single_node *node_to_add = new Single_node(node_val);
		node_to_add->next = current->next;
		current->next = node_to_add;
		return true;
	}

};
