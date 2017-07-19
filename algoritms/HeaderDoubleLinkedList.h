#include <iostream>
#include <cassert>

using namespace std;

class Double_list {

private:
  class Double_node {
	  friend class Double_list;
	  Double_node(int node_val) : val(node_val) {}
	  Double_node() {}
	  ~Double_node() {}
	  void print_val() const { cout << val << " "; }
	  Double_node *next;
	  Double_node *prev;
	  int val;
  };

  Double_node *head;
  Double_node *tail;

  Double_list & operator=(const Double_list &);
  Double_list(const Double_list &);

public:
  Double_list() {
	  head = tail = new Double_node;
	  tail->next = 0;
	  tail->prev = 0;
  }

  Double_list(int node_val) {
	  head = tail = new Double_node;
	  tail->next = 0;
	  tail->prev = 0;
	  add_front(node_val);
  }

  ~Double_list()  {
	  Double_node *node_to_delete = head;
	  for (Double_node *sn = head; sn != tail;) {
		  sn = sn->next;
		  delete node_to_delete;
		  node_to_delete = sn;
	  }
	  delete node_to_delete;
  }

  bool is_empty() const {return head == tail;}

  void add_front(int node_val) {
	  Double_node *node_to_add = new Double_node(node_val);
	  node_to_add->next = head;
	  node_to_add->prev = 0;
	  head->prev = node_to_add;
	  head = node_to_add;
  }

  void add_rear(int node_val)  {
	  if (is_empty()) {
		  add_front(node_val);
	  } else {
		  Double_node *node_to_add = new Double_node(node_val);
		  node_to_add->next = tail;
		  node_to_add->prev = tail->prev;
		  tail->prev->next = node_to_add;
		  tail->prev = node_to_add;
	  }
  }

  bool insert_after(int node_val, const int key)  {
	  for (Double_node *dn = head; dn != tail; dn = dn->next) {
		  if (dn->val == key) {
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

  int remove_front() {
	  if ( is_empty() ) {
		  throw "list is empty";
	  }
	  Double_node *node_to_remove = head;
	  int return_val = node_to_remove->val;
	  head = node_to_remove->next;
	  head->prev = 0;
	  delete node_to_remove;
	  return return_val;
  }

  int remove_rear() {
	  if (is_empty()) {
		  throw "list is empty";
	  }
	  Double_node *node_to_remove = tail->prev;
	  if (node_to_remove->prev == 0) {
		  return remove_front();
	  } else {
		  int return_val = node_to_remove->val;
		  node_to_remove->prev->next = tail;
		  tail->prev = node_to_remove->prev;
		  delete node_to_remove;
		  return return_val;
	  }
  }

  bool remove_val(int node_val)  {
	  for (Double_node *dn = head; dn != tail; dn = dn->next) {
		  if ( dn->val == node_val ) {
			  dn->prev->next = dn->next;
			  dn->next->prev = dn->prev;
			  delete dn;
			  return true;
		  }
	  }
	  return false;
  }

  bool find(int node_val) const {
	  for (Double_node *dn = head; dn != tail; dn = dn->next) {
		  if (dn->val == node_val) {
			  return true;
		  }
	  }
	  return false;
  }

  int get_nth(const int element_num) const {
	  if (element_num < 1) {
		  throw "argument less than one";
	  }
	  int count = 1;
	  for (Double_node *dn = head; dn != tail; dn = dn->next) {
		  if (count++ == element_num) {
			  return dn->val;
		  }
	  }
	  throw "exceeds list size";
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
