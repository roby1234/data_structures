#ifndef _BST_H
#define _BST_H

#include <string>
#include "linked_list.cpp"
//#include "student_record.cpp"

using namespace std;

class bstnode 
{
private:
	bstnode* leftchild;
	bstnode* rightchild;
	bstnode* parent;
	student_record* data;
public:
	bstnode();
	~bstnode();
	bstnode* get_left();
	bstnode* get_right();
	bstnode* get_parent();
	string get_key();
	student_record& get_record();
	void set_left(bstnode*);
	void set_right(bstnode*);
	void set_parent(bstnode*);
	void set_key(string);
	void set_record(student_record&);
};

template <class T>
class bst
{
private:
	T* root;
public:
	T* get_root(){
		return root;
	}
	void set_root(T* a){
		root = a;
	}
	bst();
	~bst();
	void insert_file(char a[]);
	void insert_file(char a[] , T* );
	void insert_node(T*);
	void delete_node(T* , T*);
	void delete_filenode(char a[] , T*);
	int search_node(string , T*);
	T* find_node(string , T*);
	void preorder(T* , T*);
	void inorder(T* , T*);
	void postorder(T* , T*);
	string successor(T* , T*);
	string max_of_tree(T* , T*);
	string min_of_tree(T* , T*);
	void clear_tree(T*);
	int height(T*);
};

#endif
