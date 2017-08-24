#include <iostream>
#include <cassert>

using namespace std;

template <class T>

class Avl_tree {

private:
	struct Tree_node {
		friend class Avl_tree;
		T val;
		Tree_node *left_child;
		Tree_node *right_child;
		Tree_node *parent;
		int bal;
		int nodecount;

		Tree_node();
		Tree_node(const T node_val) : val(node_val) {}
		~Tree_node() {}

		bool isa_right_child() const {
			if ((parent == 0) || (parent->right_child != this))
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

		bool isa_leaf() const {
			return ((right_child == 0) && (left_child == 0));
		}

		void print (const int level = 0) const {
			const Tree_node *tn = this;
			if (tn != 0) tn->right_child->print(level + 1);
			for (int spaces = 0; spaces < level; ++spaces)
				cout << "      ";
			if (tn != 0)
				cout << tn->val << '(' << tn->nodecount << '/' << bal << ')' << endl;
			else
				cout << "@" << endl;
			if (tn != 0)
				tn->left_child->print(level + 1);
		}

	};

private:
	Tree_node *root;
	Tree_node *zero_node;

	Avl_tree(const Avl_tree &);
	Avl_tree & operator=(const Avl_tree &);

	void make_new_root(const T root_val) {
		root = new Tree_node(root_val);
		root->left_child  = 0;
		root->right_child = 0;
		root->parent      = 0;
		root->bal         = 0;
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

	Tree_node * insert_node (const T insert_value, Tree_node * start_node = 0) {
		if (root == 0)  {
			make_new_root(insert_value);
			return root;
		}

		if (start_node == 0)
			start_node = root;

		Tree_node *tn = start_node;

		while ((tn != 0) && (tn->val != insert_value)) {
			if (insert_value < tn->val)  {
				if (tn->left_child == 0)  {
					attach_node(tn, tn->left_child, insert_value);
					adjust_for_add(tn->left_child);
					return tn->left_child;
				} else {
					tn = tn->left_child;
				}
			} else {
				if (tn->right_child == 0)  {
					attach_node(tn, tn->right_child, insert_value);
					adjust_for_add(tn->right_child);
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
		new_child->parent = new_parent;
		new_child->nodecount = 1;
		new_child->bal = 0;
	}

	void adjust_nodecount_to_root(Tree_node * tn, int incr) {
		while (tn != 0) {
			tn->nodecount += incr;
			tn = tn->parent;
		}
	}

	void adjust_for_add(Tree_node * new_child) {
		assert(new_child != root);
		bool rotate_flag = false;
		bool bal_was_changed = false;

		Tree_node * new_parent      = new_child->parent;
		Tree_node * new_grandparent = new_parent->parent;

		++(new_parent->nodecount);

		if (new_child->isa_right_child()) {
			++(new_parent->bal);
			bal_was_changed = true;
		} else {
			--(new_parent->bal);
			bal_was_changed = true;
		}

		assert ((new_parent->bal > -2) && (new_parent->bal < 2));

		while (new_grandparent != 0) {
			++(new_grandparent->nodecount);
			if (new_parent->isa_right_child()) {
				if (new_parent->bal != 0 && bal_was_changed)
					++(new_grandparent->bal);
				else
					bal_was_changed = false;
			} else if (new_parent->isa_left_child()) {
				if (new_parent->bal != 0 && bal_was_changed)
					--(new_grandparent->bal);
				else
					bal_was_changed = false;
			}
			if ((new_grandparent->bal < -1) || (new_grandparent->bal > 1) ) {
				rotate_flag = true;
				break;
			}
			new_child = new_parent;
			new_parent = new_grandparent;
			new_grandparent = new_grandparent->parent;
		}

		if (rotate_flag) {
			int new_child_orig_bal = new_child->bal;

			if (new_parent->isa_left_child() && new_child->isa_left_child()) {
				if (new_grandparent->isa_left_child())
					rotate_right(new_grandparent->parent->left_child);
				else if (new_grandparent->isa_right_child())
					rotate_right(new_grandparent->parent->right_child);
				else {
					assert(new_grandparent == root);
					rotate_right(root);
				}

				new_parent->bal = 0;
				new_parent->right_child->bal = 0;
				adjust_nodecount_to_root(new_parent->parent, 1);
			} else if (new_parent->isa_right_child() && new_child->isa_right_child()) {
				if (new_grandparent->isa_left_child())
					rotate_left(new_grandparent->parent->left_child);
				else if (new_grandparent->isa_right_child())
					rotate_left(new_grandparent->parent->right_child);
				else {
					assert(new_grandparent == root);
					rotate_left(root);
				}
				new_parent->bal = 0;
				new_parent->left_child->bal = 0;
				adjust_nodecount_to_root(new_parent->parent, 1);
			} else if (new_parent->isa_left_child() && new_child->isa_right_child()) {
				rotate_left(new_grandparent->left_child);
				if (new_grandparent->isa_left_child())
					rotate_right(new_grandparent->parent->left_child);
				else if (new_grandparent->isa_right_child())
					rotate_right(new_grandparent->parent->right_child);
				else {
					assert(new_grandparent == root);
					rotate_right(root);
				}

				new_grandparent->parent->bal = 0;

				if (new_child_orig_bal == 0) {
					new_grandparent->bal = 0;
					new_grandparent->parent->left_child->bal = 0;
				} else if (new_child_orig_bal == -1) {
					new_grandparent->bal = 1;
					new_grandparent->parent->left_child->bal = 0;
				} else if (new_child_orig_bal == 1) {
					new_grandparent->bal = 0;
					new_grandparent->parent->left_child->bal = -1;
				}

				adjust_nodecount_to_root(new_grandparent->parent->parent , 1);
			} else if (new_parent->isa_right_child() && new_child->isa_left_child()) {
				rotate_right(new_grandparent->right_child);

				if (new_grandparent->isa_left_child())
					rotate_left(new_grandparent->parent->left_child);
				else if (new_grandparent->isa_right_child())
					rotate_left(new_grandparent->parent->right_child);
				else {
					assert(new_grandparent == root);
					rotate_left(root);
				}

				new_grandparent->parent->bal = 0;

				if (new_child_orig_bal == 0) {
					new_grandparent->bal = 0;
					new_grandparent->parent->right_child->bal = 0;
				} else if (new_child_orig_bal == -1) {
					new_grandparent->bal = 0;
					new_grandparent->parent->right_child->bal = 1;
				} else if (new_child_orig_bal == 1) {
					new_grandparent->bal = -1;
					new_grandparent->parent->right_child->bal = 0;
				}

				adjust_nodecount_to_root(new_grandparent->parent->parent , 1);
			}
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

	static void rotate_right(Tree_node * & node) {
		Tree_node *tn = node->left_child;
		node->left_child = tn->right_child;
		if (tn->right_child) tn->right_child->parent = node;

		tn->right_child = node;
		tn->parent      = node->parent;
		node->parent    = tn;

		int leftcount  = node->left_child ? node->left_child->nodecount : 0;
		int rightcount = node->right_child ? node->right_child->nodecount : 0;
		node->nodecount = leftcount + rightcount + 1;
		leftcount  = tn->left_child ? tn->left_child->nodecount : 0;
		rightcount = tn->right_child ? tn->right_child->nodecount : 0;
		tn->nodecount   = leftcount + rightcount + 1;
		node            = tn;
	}

	static void rotate_left(Tree_node * & node) {
		Tree_node *tn = node->right_child;
		node->right_child = tn->left_child;
		if (tn->left_child) tn->left_child->parent = node;
		tn->left_child = node;
		tn->parent     = node->parent;
		node->parent   = tn;

		int leftcount  = node->left_child ? node->left_child->nodecount : 0;
		int rightcount = node->right_child ? node->right_child->nodecount : 0;
		node->nodecount = leftcount + rightcount + 1;
		leftcount  = tn->left_child ? tn->left_child->nodecount : 0;
		rightcount = tn->right_child ? tn->right_child->nodecount : 0;
		tn->nodecount   = leftcount + rightcount + 1;
		node           = tn;
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

	void print_in(const Tree_node * tn) const {
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

	Avl_tree() : zero_node(0) {root = 0;}
	Avl_tree(const T root_val) : zero_node(0) {
		make_new_root(root_val);
	}
	~Avl_tree() {
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
		int delta_balance = 0;

		if (node_to_remove == zero_node) return;
		assert(node_to_remove->val == value);

		if (node_to_remove->left_child == 0) {
			temp = node_to_remove;
			if (temp->parent) {
				--(temp->parent->nodecount);
				if (temp->isa_left_child()) {
					++(temp->parent->bal);
					delta_balance = 1;
				} else if (temp->isa_right_child()) {
					--(temp->parent->bal);
					delta_balance = -1;
				}
			}

			if (node_to_remove->right_child != 0)  {
				node_to_remove->right_child->parent = node_to_remove->parent;
			}

			node_to_remove = node_to_remove->right_child;
			adjust_for_remove(temp->parent, delta_balance);
			delete temp;
			return;
		} else if (node_to_remove->right_child == 0) {
			temp = node_to_remove;
			if (temp->parent) {
				--(temp->parent->nodecount);
				if (temp->isa_left_child()) {
					++(temp->parent->bal);
					delta_balance = 1;
				} else if (temp->isa_right_child()) {
					--(temp->parent->bal);
					delta_balance = -1;
				}
			}
			node_to_remove->left_child->parent = node_to_remove->parent;
			node_to_remove = node_to_remove->left_child;
			adjust_for_remove(temp->parent, delta_balance);
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
			++(pp->bal);
			delta_balance = 1;
			if (predecessor->left_child != 0)
				predecessor->left_child->parent = pp;
		} else if (predecessor->left_child != 0) {
			pp->right_child = predecessor->left_child;
			predecessor->left_child->parent = pp;
			--(pp->bal);
			delta_balance = -1;
		} else {
			assert(pp->right_child == predecessor);
			pp->right_child = 0;
			--(pp->bal);
			delta_balance = -1;
		}

		--(pp->nodecount);
		adjust_for_remove(pp, delta_balance);
		delete predecessor;
	}

	void adjust_for_remove(Tree_node * start_node, int delta_balance) {
		Tree_node * tn   = start_node;
		int tn_bal_orig  = tn->bal;

		if ((tn->bal == -2) || (tn->bal == 2))
			tn = rotate_for_remove (tn, delta_balance);

		delta_balance = tn_bal_orig - tn->bal;
		int absdelta = (delta_balance > 0) ? delta_balance : -delta_balance;
		Tree_node * tnp  = tn->parent;

		while (tnp != 0)  {
			--(tnp->nodecount);
			assert(tn != root);

			if (tn->bal == 0) {
				if (tn->isa_right_child()) {
					--(tnp->bal);
					delta_balance = -1;
				} else {
					++(tnp->bal);
					delta_balance = 1;
				}
			} else {
				adjust_nodecount_to_root(tnp->parent, -1);
				return;
			}

			if ((tnp->bal > -2) && (tnp->bal < 2))  {
				tn  = tnp;
				tnp = tn->parent;
				continue;
			}

			tn = rotate_for_remove(tnp, delta_balance);
			tnp = tn->parent;
		}
	}

	Tree_node * rotate_for_remove(Tree_node * tn, int delta_balance) {
		Tree_node * resume_iteration = 0;
		Tree_node * tnp = tn->parent;

		if (delta_balance > 0) {
			resume_iteration = tn->right_child;
			if ((tn->bal == 2) && ((tn->right_child->bal == 1) || (tn->right_child->bal == 0))) {
				if (tn->right_child->bal == 1) {
					tn->bal = 0;
					tn->right_child->bal = 0;
				} else {
					assert(tn->right_child->bal == 0);
					tn->bal = 1;
					tn->right_child->bal = -1;
				}

				if (tn->isa_left_child())
					rotate_left(tn->parent->left_child);
				else if (tn->isa_right_child())
					rotate_left(tn->parent->right_child);
				else {
					assert(tn == root);
					rotate_left(root);
				}
				return resume_iteration;
			} else if ((tn->bal == 2) && (tn->right_child->bal == -1)) {
				if (tn->right_child->left_child->bal == 1) {
					tn->bal = -1;
					tn->right_child->bal = 0;
					tn->right_child->left_child->bal = 0;
				} else if (tn->right_child->left_child->bal == -1) {
					tn->bal = 0;
					tn->right_child->bal = 1;
					tn->right_child->left_child->bal = 0;
				} else {
					assert (tn->right_child->left_child->bal == 0);
					tn->bal = 0;
					tn->right_child->bal = 0;
					tn->right_child->left_child->bal = 0;
				}

				resume_iteration = resume_iteration->left_child;
				rotate_right(tn->right_child);

				if (tn->isa_left_child())
					rotate_left(tn->parent->left_child);
				else if (tn->isa_right_child())
					rotate_left(tn->parent->right_child);
				else {
					assert(tn == root);
					rotate_left(root);
				}
				return resume_iteration;
			}
		} else {
			assert (delta_balance < 0);
			resume_iteration = tn->left_child;

			if ((tn->bal == -2) && ((tn->left_child->bal == -1) || (tn->left_child->bal == 0))) {
				if (tn->left_child->bal == -1) {
					tn->bal = 0;
					tn->left_child->bal = 0;
				} else {
					assert(tn->right_child->bal == 0);
					tn->bal = -1;
					tn->left_child->bal = 1;
				}

				if (tn->isa_left_child())
					rotate_right(tn->parent->left_child);
				else if (tn->isa_right_child())
					rotate_right(tn->parent->right_child);
				else {
					assert(tn == root);
					rotate_right(root);
				}
				return resume_iteration;
			} else if ((tn->bal == -2) && (tn->left_child->bal == 1)) {
				if (tn->left_child->right_child->bal == -1) {
					tn->bal = 1;
					tn->left_child->bal = 0;
					tn->left_child->left_child->bal = 0;
				} else if (tn->left_child->right_child->bal == 1) {
					tn->bal = 0;
					tn->left_child->bal = -1;
					tn->left_child->right_child->bal = 0;
				} else {
					assert(tn->left_child->right_child->bal == 0);
					tn->bal = 0;
					tn->left_child->bal = 0;
					tn->left_child->right_child->bal = 0;
				}

				resume_iteration = resume_iteration->right_child;
				rotate_left(tn->left_child);

				if (tn->isa_left_child())
					rotate_right(tnp->parent->left_child);
				else if (tn->isa_right_child())
					rotate_right(tn->parent->right_child);
				else {
					assert(tn == root);
					rotate_right(root);
				}
				return resume_iteration;
			}
		}
		assert(false);
		return zero_node;
	}

	T get_nth(const int element_num) const {
		Tree_node * tn = get_nth_node(root, element_num);
		return tn->val;
	}

	int size() const {return root ? root->nodecount : 0;}

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

	void print_post_order() const {
		print_post(root);
		cout << endl;
	}

};
