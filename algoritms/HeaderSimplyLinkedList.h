#include <cassert>

class Single_list {

	private:

		class Single_node {

			friend class Single_list;

			Single_node(int node_val) : val(node_val) {}

			Single_node() {}

			~Single_node() {}

			Single_node *next;

			int val;

		};

		Single_node *head;
		Single_node *tail;

		Single_list & operator=(const Single_list &);
		Single_list(const Single_list &);

	public:

		Single_list() {

			head = tail = new Single_node;

			tail -> next = 0;

		}

		Single_list(int node_val) {

			head = tail = new Single_node;

			tail -> next = 0;

			add_front(node_val);
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

		void add_front(int node_val) {
			Single_node *node_to_add = new Single_node(node_val);
			node_to_add->next = head;
			head = node_to_add;
		}

		int remove_front() {
			if(is_empty()) {
				throw "error, list is empty";
			}
			Single_node *node_to_remove = head;
			int return_val = node_to_remove->val;
			head = node_to_remove->next;
			delete node_to_remove;
			return return_val;
		}

		bool find(const int node_val) const {
			for(Single_node *sn = head; sn != tail; sn = sn->next) {
				if(sn->val == node_val) {
					return true;
				}
			}
			return false;
		}

		int get_nth(const int element_num) const {
			if(element_num < 1) {
				throw "argument less than one";
			}
			int count = 1;
			for(Single_node *sn = head; sn != tail; sn = sn->next) {
				if(count++ == element_num) {
					return sn->val;
				}
			}
			throw "exceeds list size";
		}

		int size() const {
			int count = 0;
			for(Single_node *sn = head; sn != tail; sn = sn->next) {
				++count;
			}
			return count;
		}

};
