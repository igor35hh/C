#include <iostream>
#include <cassert>

using namespace std;

template <class T>
class Binary_tree {

private:
	struct Tree_node {

		friend class Binary_tree;
		T val;
		Tree_node *left_child;
		Tree_node *right_child;
		Tree_node *parent;
		int nodecount;

		Tree_node();
		Tree_node(const T node_val) : val(node_val) {}
		~Tree_node() {}

		bool isa_right_child() const {
			if ((parent == 0) || ( parent->right_child != this))
				return false;
			else
				return true;
		}

		bool isa_left_child() const {
			if ((parent == 0) || ( parent->left_child != this))
				return false;
			else
				return true;
		}

		void print (const int level = 0) const {
			const Tree_node *tn = this;

			if (tn != 0)
				tn->right_child->print(level + 1);

			for (int spaces = 0; spaces < level; ++spaces)
				cout << "   ";

			if (tn != 0)
				cout << tn->val << '(' << tn->nodecount << ')' << endl;
			else
				cout << "@" << endl;

			if (tn != 0)
				tn->left_child->print(level + 1);

		}

	};

private:
	Tree_node *root;
	Tree_node *zero_node;

	Binary_tree(const Binary_tree &);
	Binary_tree & operator=(const Binary_tree &);

	void make_new_root(const T root_val) {
		root = new Tree_node(root_val);
		root->left_child  = 0;
		root->right_child = 0;
		root->parent      = 0;
		root->nodecount   = 1;
	}

	Tree_node * & find_node(T find_value) {
		Tree_node *tn = root;
		while ((tn != 0) && (tn->val != find_value))  {
			if (find_value < tn->val)
				tn = tn->left_child;
			else
				tn = tn->right_child;
		}

		if (tn == 0)
			return zero_node;
		else if (tn->isa_left_child())
			return tn->parent->left_child;
		else if (tn->isa_right_child())
			return tn->parent->right_child;
		else if (tn == root)
			return root;

		assert(false);
		return zero_node;
	}

	Tree_node * insert_node(const T insert_value, Tree_node * start_node = 0) {

		if (root == 0)  {
		      make_new_root(insert_value);
		      return root;
		}

		if (start_node == 0) start_node = root;

		Tree_node *tn = start_node;

		while ((tn != 0) && (tn->val != insert_value)) {
			if (insert_value < tn->val)  {
				if (tn->left_child == 0)  {
					attach_node(tn, tn->left_child, insert_value);
					adjust_nodecount_to_root(tn, 1);
					return tn->left_child;
				} else {
					tn = tn->left_child;
				}
			} else {
				if (tn->right_child == 0)  {
					attach_node(tn, tn->right_child, insert_value);
					adjust_nodecount_to_root(tn, 1);
					return tn->right_child;
				} else {
					tn = tn->right_child;
				}
			}
		}

		assert (tn != 0);
		return 0;
	}

	void attach_node(Tree_node * new_parent, Tree_node * & new_child, T insert_value) {
		new_child = new Tree_node(insert_value);
		new_child->left_child  = 0;
		new_child->right_child = 0;
		new_child->parent      = new_parent;
		new_child->nodecount   = 1;
	}

	void adjust_nodecount_to_root(Tree_node * tn, int incr) {
		while (tn != 0) {
			tn->nodecount += incr;
			tn = tn->parent;
		}
	}

	Tree_node * get_nth_node(Tree_node * tn, const int nth) const {
		if (tn == 0) return 0;
		int lc_count = (tn->left_child != 0) ? tn->left_child->nodecount : 0;
		if ((lc_count + 1) == nth) {
			return tn;
		} else if (lc_count >= nth) {
			return get_nth_node(tn->left_child, nth);
		} else {
			return get_nth_node(tn->right_child, nth - lc_count -1);
		}
	}

	void cleanup (Tree_node *tn) {
		if (tn == 0) return;
		if (tn->left_child != 0) {
			cleanup(tn->left_child);
			tn->left_child = 0;
		}
		if (tn->right_child != 0) {
			cleanup(tn->right_child);
			tn->right_child = 0;
		}
		delete tn;
	}

	void print_pre(const Tree_node * tn) const {
		if (tn == 0) return;
		cout << tn->val << "  ";
		if (tn->left_child != 0) {
			print_pre(tn->left_child);
		}
		if (tn->right_child != 0) {
			print_pre(tn->right_child);
		}
	}

	void print_in(const Tree_node * tn)  const {
		if (tn == 0) return;
		if (tn->left_child != 0) {
			print_in(tn->left_child);
		}
		cout << tn->val << "  ";
		if (tn->right_child != 0) {
			print_in(tn->right_child);
		}
	}

	void print_post(const Tree_node * tn) const {
		if (tn == 0) return;
		if (tn->left_child != 0) {
			print_post(tn->left_child);
		}
		if (tn->right_child != 0) {
			print_post(tn->right_child);
		}
		cout << tn->val << "  ";
	}

public:
	Binary_tree() : zero_node(0) {root = 0;}
	Binary_tree(const T root_val ) : zero_node(0) {
		make_new_root(root_val);
	}

	~Binary_tree() {
		cleanup(root);
	}

	bool add(const T insert_value) {
		Tree_node *ret = insert_node(insert_value);
		if (ret)
			return true;
		else
			return false;
	}

	void remove(T value) {
		Tree_node * & node_to_remove = find_node(value);
		Tree_node * predecessor = 0;
		Tree_node * temp = 0;

		if (node_to_remove == zero_node) return;
		assert(node_to_remove->val == value);

		if (node_to_remove->left_child == 0) {
			temp = node_to_remove;

			if (node_to_remove->right_child != 0)  {
				node_to_remove->right_child->parent = node_to_remove->parent;
			}

			node_to_remove = node_to_remove->right_child;

			adjust_nodecount_to_root(temp->parent, -1);

			delete temp;
			return;
		} else if (node_to_remove->right_child == 0) {
			temp = node_to_remove;
			node_to_remove->left_child->parent = node_to_remove->parent;
			node_to_remove = node_to_remove->left_child;
			adjust_nodecount_to_root(temp->parent, -1);
			delete temp;
			return;
		}

		predecessor = node_to_remove->left_child;
		while (predecessor->right_child != 0)
			predecessor = predecessor->right_child;

		node_to_remove->val = predecessor->val;

		Tree_node * pp = predecessor->parent;
		if (pp == node_to_remove) {
			pp->left_child = predecessor->left_child;
			if (predecessor->left_child != 0)
				predecessor->left_child->parent = pp;
		} else if (predecessor->left_child != 0) {
			pp->right_child = predecessor->left_child;
			predecessor->left_child->parent = pp;
		} else {
			assert(pp->right_child == predecessor);
			pp->right_child = 0;
		}

		adjust_nodecount_to_root(pp, -1);
		delete predecessor;
	}

	T get_nth(const int element_num) const {
		Tree_node * tn = get_nth_node(root, element_num);
		return tn->val;
	}

	int size() const {
		return root ? root->nodecount : 0;
	}

	bool find(T find_value) {
		Tree_node *tn = find_node(find_value);

		if (tn != 0)
			return true;
		else
			return false;
	}

	void print() const {
		cout << "\n" << "===================================" << "\n" << endl;
		root->print();
	}

	void print_pre_order() const {
		print_pre(root);
		cout << endl;
	}

	void print_in_order() const {
		print_in(root);
		cout << endl;
	}

	void print_post_order( ) const {
		print_post(root);
		cout << endl;
	}

};
