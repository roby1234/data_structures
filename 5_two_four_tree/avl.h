#ifndef _AVL_H
#define _AVL_H
#include "bst.h"
#include <string>

using namespace std;

class avlnode 
{
private:
	avlnode* leftchild;
	avlnode* rightchild;
	avlnode* parent;
	student_record* data;
	int bf;
public:
	avlnode();
	~avlnode();
	int get_bf();
	string get_key();
	avlnode* get_left();	
	avlnode* get_right();
	avlnode* get_parent();
	student_record& get_record();
	void set_bf(int);
	void set_key(string);
	void set_left(avlnode*);
	void set_right(avlnode*);
	void set_parent(avlnode*);
	void set_record(student_record&);
};

template <class T>
class avl : public bst<T>
{
private:
	T* avlroot;
public:
	avl();
	~avl();
	T* get_avlroot();
	void set_avlroot(T*);
	void insert_avlnode(T*);
	void balance(T*);
	void delete_avlnode(T* , T*);
	void rotateleft(T*);
	void rotateright(T*);
	int getting_bf(T*);
	void insert_file(char a[]);
	void insert_file(char a[] , T* n);
	void delete_filenode(char a[] , T*);
};

#endif