#include <iostream>
#include <cassert>

using namespace std;

template <class T>
class Double_list {

public:
	class iterator;
	friend class iterator;

private:
	class Double_node;
	friend class Double_node;

	class Double_node {

	public:
		friend class Double_list;
		friend class iterator;

		Double_node(T node_val) : val(node_val) {}
		Double_node() {}
		~Double_node() {}

		void print_val() {
			cout << val << " ";
		}

		Double_node *next;
		Double_node *prev;
		T val;

	};

public:
	class iterator {
		friend class Double_list<T>;
	public:
		iterator() : the_node(0) {}
		iterator(Double_node * dn) : the_node(dn) {}
		iterator(const iterator & it) : the_node(it.the_node) {}

		iterator& operator=(const iterator& it) {
			the_node = it.the_node;
			return *this;
		}

		bool operator==(const iterator& it) const {
			return (the_node == it.the_node);
		}

		bool operator!=(const iterator& it) const {
		     return !(it == *this);
		}

		iterator& operator++( ) {
			if ( the_node == 0 )
				throw "empty iterator";
			if ( the_node->next == 0 )
			    throw "increment too far past the end";

			the_node = the_node->next;
			return *this;
		}

		iterator& operator--() {
			if ( the_node == 0 )
				throw "empty iterator";
			if ( the_node->prev == 0 )
			    throw "decrement past the beginning";

			the_node = the_node->prev;
			return *this;
		}

		T& operator*( ) const {
			if ( the_node == 0 )
				throw "tried to dereference an empty iterator";
			return the_node->val;
		}

	private:
		Double_node * the_node;

	};

private:
	Double_node *head;
	Double_node *tail;

	Double_list & operator=(const Double_list &);
	Double_list(const Double_list &);

	iterator head_iterator;
	iterator tail_iterator;

public:
	Double_list() {
		head = tail = new Double_node;
		tail->next = 0;
		tail->prev = 0;
		head_iterator = iterator(head);
		tail_iterator = iterator(tail);
	}

	Double_list(T node_val) {
		head = tail = new Double_node;
		tail->next = 0;
		tail->prev = 0;

		head_iterator = iterator(head);
		tail_iterator = iterator(tail);
		add_front(node_val);
	}

	~Double_list() {
		Double_node *node_to_delete = head;
		for (Double_node *sn = head; sn != tail;) {
			sn = sn->next;
			delete node_to_delete;
			node_to_delete = sn;
		}
		assert(node_to_delete == tail);
		delete node_to_delete;
	}

	bool is_empty() {
		return head == tail;
	}

	iterator front() {
		return head_iterator;
	}

	iterator rear()  {
		return tail_iterator;
	}

	void add_front(T node_val) {
		Double_node *node_to_add = new Double_node(node_val);
		node_to_add->next = head;
		node_to_add->prev = 0;
		head->prev = node_to_add;
		head = node_to_add;
		head_iterator = iterator(head);
	}

	void add_rear(T node_val) {
		if ( is_empty( ) )
			add_front(node_val);
		else {
		    Double_node *node_to_add = new Double_node(node_val);
		    node_to_add->next = tail;
		    node_to_add->prev = tail->prev;
		    tail->prev->next = node_to_add;
		    tail->prev = node_to_add;
		    tail_iterator = iterator(tail);
		}
	}

	bool insert_after(T node_val, const iterator & key_i) {
		for ( Double_node *dn = head; dn != tail; dn = dn->next ) {
			if ( dn == key_i.the_node ) {
				Double_node *node_to_add = new Double_node(node_val);
				node_to_add->prev = dn;
				node_to_add->next = dn->next;
				dn->next->prev    = node_to_add;
				dn->next          = node_to_add;
				return true;
			}
		}
		return false;
	}

	T remove_front() {
		if ( is_empty( ) )
			throw "empty list";

		Double_node *node_to_remove = head;
		T return_val = node_to_remove->val;
		head = node_to_remove->next;
		head->prev = 0;
		head_iterator = iterator(head);
		delete node_to_remove;
		return return_val;
	}

	T remove_rear() {
		if ( is_empty( ) )
			throw "empty list";

		Double_node *node_to_remove = tail->prev;

		if (node_to_remove->prev == 0) {
			return remove_front( );
		} else {
		    T return_val = node_to_remove->val;
		    node_to_remove->prev->next = tail;
		    tail->prev = node_to_remove->prev;
		    delete node_to_remove;
		    return return_val;
		}
	}

	bool remove_it(iterator & key_i) {
		for (Double_node *dn = head; dn != tail; dn = dn->next) {
			if (dn == key_i.the_node) {
				dn->prev->next = dn->next;
				dn->next->prev = dn->prev;
				delete dn;
				key_i.the_node = 0;
				return true;
			}
		}
		return false;
	}

	iterator find(T node_val) const {
		for ( Double_node *dn = head; dn != tail; dn = dn->next ) {
			if ( dn->val == node_val )
				return iterator(dn);
		}
		return tail_iterator;
	}

	iterator get_nth(const int element_num) const {
		if ( element_num < 1 )
			return tail_iterator;

		int count = 1;
		for (Double_node *dn = head; dn != tail; dn = dn->next) {
			if ( count++ == element_num ) return iterator(dn);
		}
		return tail_iterator;
	}

	int size() const {
		int count = 0;
		for (Double_node *dn = head; dn != tail; dn = dn->next) {
			++count;
		}
		return count;
	}

	void print() const {
		for (Double_node *dn = head; dn != tail; dn = dn->next) {
			dn->print_val();
		}
		cout << endl;
	}

};
