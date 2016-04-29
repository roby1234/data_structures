#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <string.h>
// #include "linked_list.cpp"
//#include "twofourtree.h"
#include "avl.h"

using namespace std;

/***********************************************************************************************************************************/
					/*functions accessing hashing technique
/***********************************************************************************************************************************/

class dictionary
{
private:
	int choice;
	int size;
	int length;
public:
	dictionary(int a,int b){
		size = a;
		choice = b;
		length = 0;
	}
	~dictionary(){}

	dictionary(const dictionary &d){
		size = d.size;
		choice = d.choice;
		length = d.length;
	}
	int get_size(){
		return size;
	}

/***********************************************************************************************************************************/
					/*functions accessing dictionary
/***********************************************************************************************************************************/
	void linear_probe(student_record &x,linear_list &y){
		if(length == get_size())
			cout<< "TABLE FULL\n";
		int hash_key = gen_key1(x.get_roll());
		while(1){
			if(y.return_element(hash_key)->get_roll() == "000"){
				y.insert(hash_key , x);
				break;
      			}
    			else{
				if(hash_key < (y.get_size()))
					hash_key++;
				else if(hash_key == y.get_size())
					hash_key = 0;
    			}
  		}
	}

	void double_hash(student_record &x,linear_list &y){
		int hash_key1 = gen_key1(x.get_roll());
		int hash_key2 = gen_key2(x.get_roll());
		while(1){
			if(y.return_element(hash_key1)->get_roll() == "000"){
				y.insert(hash_key1 , x);
				break;
			}
	    		else{
    				hash_key1 = hash_key1 + hash_key2 ;
				if(hash_key1 <= (y.get_size()))
					continue;
				else if(hash_key1 > y.get_size())
					hash_key1 = (hash_key1 - (y.get_size()-1));
    			}
  		}
	}

/***********************************************************************************************************************************/
					/*inserting functions
/***********************************************************************************************************************************/
	void insert(char a[] , student_record &x , linear_list &y){
  		ofstream File(a , ios::app);
  		File << x ; 
  		if(choice==1){
  			linear_probe(x,y);
  			++length;
  			if(length == size)
				cout <<"table is full\n";
  		}
   		else if(choice == 3){
   			double_hash(x,y);
			++length;
			if(length == size)
				cout <<"table is full\n";
		}
   		else
   			cout << "wrong function call\n";
  		File.close();
	}


	void insert(char a[], linear_list &y){
    	student_record x;
    	ifstream File(a); 
    	while(File >> x){ 
			if(choice == 1){
    				linear_probe(x,y);
				++length;
    				if(length == size){
					rehash(y);
    					cout << "Rehashing has taken place\n\n";
    					File.seekg(0, ios::beg);		//Sets the position of the next character
										//to be extracted from the input stream.
    				}
    			}
    		else if(choice == 3){
   				double_hash(x,y);
				++length;
   				if(length == size){
					rehash(y);
    					cout << "Rehashing has taken place\n\n";
    					File.seekg(0, ios::beg);		//Sets the position of the next character
										//to be extracted from the input stream.
    			}
   			}
   			else
   				cout << "wrong function call\n";
    		}
    	File.close();
	}

/***********************************************************************************************************************************/
					/*searching functions
/***********************************************************************************************************************************/
	int search(student_record &x,linear_list &y){
    		int hash_key1 = gen_key1(x.get_roll());
		int hash_key2 = gen_key2(x.get_roll());
    		int i=0;
  		if(choice == 1){  
	    		while(i < size){
       				if(y.return_element(hash_key1)->get_roll() == x.get_roll())
    					return hash_key1 ;
    				else if(y.return_element(hash_key1)->get_roll() != "000"){
      					if(hash_key1 == size-1){
						hash_key1 = 0;
						++i;
				      	}
      					else{
						++hash_key1;
						++i;
      					}
    				}
    				else
    					break;
    			}
    			return -1;
		}
  		else if(choice == 3){
    			while(i < size){
       				if(y.return_element(hash_key1)->get_roll() == x.get_roll())
    					return hash_key1 ;
    				else if(y.return_element(hash_key1)->get_roll() != "000"){
     					hash_key1 = hash_key1 + hash_key2 ;
     					++i;
      					if(hash_key1 <= y.get_size()){
            					continue;
      					}
      					else if(hash_key1 > y.get_size())
            					hash_key1 = (hash_key1 - (y.get_size()-1));
    				}
    				else
    					break;
    			}
    			return -1;
  		}
  		else{cout << "wrong entry \n";}
	}


	int search(char a[], student_record &x , linear_list &y){
		insert(a,y);
 		return search(x,y);
	}

/***********************************************************************************************************************************/
				/*deleting functions
/***********************************************************************************************************************************/
 	void hash_delete(student_record &x , linear_list &y, student_record &z){
 		int p = search(x,y);
 		if(p == -1)
			cout <<"u r trying to delete a record which does not exist\n";
 		else
 			y.deleteElement(p,z);
  	}


	void hash_delete(char a[] , student_record &x , linear_list &y, student_record &z){
    		insert(a,y);
    		hash_delete(x,y,z);
    		student_record m;
	    	ifstream File(a);
    		ofstream temp("temp.txt");
    		while(File >> m){ 
      			if(m.get_roll() != x.get_roll())
      				temp << m;
      			else if(m.get_roll() == x.get_roll())
      				continue;
    		}
    		File.clear(); 				//clear eof and fail bits
    		File.seekg(0, ios::beg);			//Sets the position of the next character
								//to be extracted from the input stream.
    		File.close();
    		temp.close();
    		remove(a); 
    		rename("temp.txt",a);
}
 
/***********************************************************************************************************************************/
				/*printing functions
/***********************************************************************************************************************************/
 	void display(int k , linear_list &y){
 		cout << *(y.return_element(k));
 	}
 
 
 	void display(linear_list &y){
 		for(int i=0 ; i <= y.get_size() ; ++i){
 			if (y.return_element(i)->get_roll() == "000" || y.return_element(i) == NULL)
 				continue;
 			else
 				cout << *(y.return_element(i)) << endl;
 		}
	}

/***********************************************************************************************************************************/
					/*chaining 
/***********************************************************************************************************************************/
 	void chaining(student_record &x , linked_list &y){
 		int i = gen_key1(x.get_roll());
 		y.insertlist(x,i);
	}

	void insert(char a[] , student_record &x , linked_list &y){
  		ofstream File(a , ios::app);
  		File << x; 
  		if(choice == 2){
  			chaining(x,y);
			++length;
		}
  		else
    			cout << "wrong entry fool"<<endl;
  			File.close();
	}


	void insert(char a[], linked_list &y){
    		student_record x;
    		ifstream File(a);
     		int i;
    		while(File >> x){ 
     			i = gen_key1(x.get_roll());
    			if(choice == 2){
    				chaining(x,y);
    				++length;
			}
    			else{
    				cout << "wrong member function call"<<endl;
  			}
    		}
    		File.close();
    		rehashcheck(a,y);
	}

	node* search(student_record &x , linked_list &y){
    		int hash_key = gen_key1(x.get_roll());
    		return y.findlist(hash_key,x);
	}

	node* search(char a[] , student_record &x , linked_list &y){
		insert(a,y);
 		return search(x,y);
	}

 	void hash_delete(student_record &x , linked_list &y){
    		int hash_key = gen_key1(x.get_roll());
    		y.deletelist(hash_key , x);
	}

 	void hash_delete(char a[] , student_record &x , linked_list &y){
    		insert(a,y);
    		hash_delete(x,y);
     		student_record k;
    		ifstream File(a);
    		ofstream temp("temp.txt");
    		while(File >> k){ 
      			if(k.get_roll() != x.get_roll())
      				temp << k;
      			else if(k.get_roll() == x.get_roll())
      				continue;
    		}
		File.clear(); // clear eof and fail bits
    		File.seekg(0, ios::beg);
    		File.close();
    		temp.close();
    		remove(a); 
    		rename("temp.txt",a);
	}
 
 	void display(linked_list &y){
 		for(int i=0;i<size;++i){
 			y.printlist(i);
 		}
 	}
	

/***********************************************************************************************************************************/
				/*key generation
/***********************************************************************************************************************************/
	int gen_key1(string roll_no){					//Hashing Function 1
		int key = 0 ;
		double A = 0.618034;
		for (int i = 0; i < (roll_no.size()); ++i){
			key = key + ((pow(2,i))*roll_no.at(i));
		}
		key = (int)(((float)(key*A)-(int)(key*A))*get_size());
		return key;
	}

	int gen_key2(string rollno){					//Hashing Function 2
		int k = gen_key1(rollno);
		int key = 11 - (k % 11);
		return key ; 
	}

/***********************************************************************************************************************************/
				/*rehashing process
/***********************************************************************************************************************************/
	int hash_length(){
	    	return length;
	}
	    
	int find_prime(int k){
	    	for(int i=2;i<k;++i){
	    		if(k%i!=0)
	    			continue;
	    		else
	    			return 0;
	    	}
	    	cout<< "size of table : " << k<<endl;
	    	return 1;
	    }
	    
	 void rehash(linear_list &y){
	    	if(choice == 1){
	    		for(int i = 2*size ; i > size ; --i){
	    			if(find_prime(i) == 1){
					size = i;
					break;
				}
	    		}
	    		linear_list *sam = new linear_list(size);
	    		length = 0;
	    		y = *sam;
	     		sam = NULL;
	    		cout <<"Table has been rehashed\nThe size of the table is :"<< size << "  now\n";
	    	}
	   	else if(choice == 3){
	    		for(int i = 2*size ; i > size ; --i){
	    			if(find_prime(i) == 1){
					size = i;
					break;
				}
	    		}
	    		linear_list *sam = new linear_list(size);
	    		length = 0;
	    		y = *sam;
	    		sam = NULL;
	    		cout <<"Table has been rehashed\nThe size of the table is :"<< size << "  now\n";
	    	}
	    	else
	    		cout << "wrong member function call\n";
	}
	    
	void rehash(char a[] , linked_list &y){
	    	if(choice == 2){
	    		size = 2*size + 1;
	    		linked_list *sam = new linked_list(size);
	    		length = 0;
	    		y = *sam;
	    		sam=NULL;
	    		insert(a,y);
	    		cout <<"Table has been rehashed\n";
		}
	    	else
	    		cout << "wrong member function call\n";
	}
	    
	void rehashcheck(char a[] , linked_list &y){
  		int j;
    		for(j=0 ; j < size ; ++j){
	 		if(y.countlist(j) > ((length/2)+1)){
				cout << " Rehashing required , and is in process\n";
				break;
			}
    		}
   		if(j < size)
    			rehash(a,y);
	}	
};
 
 
/***********************************************************************************************************************************/
					/*functions accessing BST technique
/***********************************************************************************************************************************/

/************************************************************************************************/
							/*	functions of class node */
/************************************************************************************************/

bstnode::bstnode(){
	leftchild = NULL;
	rightchild = NULL;
	parent = NULL;
	data = new student_record;
	//data->set_roll("0");
}

bstnode::~bstnode(){}

bstnode* bstnode::get_left(){
	return leftchild;
}

bstnode* bstnode::get_right(){
	return rightchild;
}

bstnode* bstnode::get_parent(){
	return parent;
}

string bstnode::get_key(){
	return data->get_roll();
}

student_record& bstnode::get_record(){
	return *data;
}

void bstnode::set_left(bstnode* l){
	leftchild = l;
}

void bstnode::set_right(bstnode* r){
	rightchild = r;
}

void bstnode::set_parent(bstnode* p){
	parent = p;
}

void bstnode::set_key(string k){
	data->set_roll(k);
}

void bstnode::set_record(student_record &a){
	*data = a ;
}

/************************************************************************************************/
							/*	functions of class bst */
/************************************************************************************************/

template <class T>
bst<T>::bst(){
	root = NULL;
}

template <class T>
bst<T>::~bst(){
	clear_tree(root);
}

template <class T>
void bst<T>::clear_tree(T* a){		
	if (a != NULL){
		clear_tree(a->get_left());
		clear_tree(a->get_right());
		delete a;
	}
}

template <class T>
void bst<T>::insert_file(char a[]){
	T* n;
	n = new T ;
	student_record x;
	ifstream File(a);
	while(File >> x){
		n->set_record(x);
		// cout << "record set\n";
		// cout << x.get_roll() << endl;
		// cout << x.get_name() << endl;
		insert_node(n);
		cout<<"\n\n";
		// cout << "inserted key   " <<n->get_key()<<endl;
		// cout << (n->get_record()).get_roll() << endl;
		n = new T;
	}
	delete n;
}

template <class T>
void bst<T>::insert_file(char a[] , T* n){
	insert_node(n);	
	ofstream File(a,ios::app);
	File << n->get_record();	
}

template <class T>
void bst<T>::insert_node(T* new_node){
	if (root == NULL){						//if there is no node in the tree 			
		root = new T;							//add the first node with key k  
		root->set_record(new_node->get_record());			//initialise all its pointers to null
		root->set_left(NULL);						
		root->set_right(NULL);
		root->set_parent(NULL); 
		cout << "Tree was empty firstly , now the node with key "<< root->get_key() <<" is inserted at the root position\n"; 
		return;
	}
	T* temproot = root;
	while (temproot != NULL){
		if (new_node->get_key() == temproot->get_key()){			//if given key is already present in the tree
			cout << "This record has already been inserted before. Can't insert it again\n";	
			return;
		}
		else if (new_node->get_key() < temproot->get_key()){		//if given key is less than the the root
			if (temproot->get_left() != NULL){
				temproot = temproot->get_left();
			}
			else{
				temproot->set_left(new_node);
				new_node->set_left(NULL);
				new_node->set_right(NULL);
				new_node->set_parent(temproot);
				cout << "The node with key "<< new_node->get_key()<<" is inserted to the left of "<<(new_node->get_parent())->get_key() <<"\n";
				return;
			}
		}
		else if (new_node->get_key() > temproot->get_key()){		//if given key is less than the the root
			if (temproot->get_right() != NULL){
				temproot = temproot->get_right();
			}
			else{
				temproot->set_right(new_node);
				new_node->set_left(NULL);
				new_node->set_right(NULL);
				new_node->set_parent(temproot);
				cout << "The node with key "<< new_node->get_key()<<" is inserted to the right of "<<(new_node->get_parent())->get_key() <<"\n";
				return;
			}
		}	
	}	
}

template <class T>
int bst<T>::search_node(string k , T* root){
	if (root != NULL){
		if (k == root->get_key()){
			cout << "Found\n";
			return 1 ;
		}
		else if (k < root->get_key()){
			return search_node(k , root->get_left());
		}
		else{
			return search_node(k , root->get_right());
		}
	}
	else{
		cout << "Key not found. U r searching for the key , that does not exist.\n";
		return -1;
	}
}

template <class T>
T* bst<T>::find_node(string k , T* root){
	if (root != NULL){
		if (k == root->get_key()){
			cout << "Found\n";
			cout << "Key 	: " << root->get_key()<<"\n";
			cout << "Record 	:\n" << root->get_record()<<"\n";
			if(root->get_parent() == NULL){
				cout << "Parent : does not exist\n";
				return root;
			}
			cout << "Parent : " << ((root->get_parent())->get_key()) << endl;
			return root;
		}
		else if (k < root->get_key() && root->get_left() != NULL){
			return find_node(k , root->get_left());
		}
		else if(k > root->get_key() && root->get_right() != NULL)
			return find_node(k , root->get_right());
	}
	else{
		cout << "Key not found. U r searching for the key , that does not exist.\n";
		return NULL;
	}
}

template <class T>
void bst<T>::delete_filenode(char a[] , T* x){
	//insert_file(a);
	student_record k;
	ifstream File(a);
	ofstream tempfile("temp.txt");
	while(File >> k){ 
		if(k.get_roll() != x->get_key())
			tempfile << k;
		else if(k.get_roll() == x->get_key())
			continue;
	}
	File.clear(); 
	File.seekg(0, ios::beg);
	File.close();
	tempfile.close();
	remove(a); 
	rename("temp.txt",a);	
	delete_node(x ,root);
}

template <class T>
void bst<T>::delete_node(T* k , T* root){
	if(root == NULL){
		cout << "Nothing to delete.\n";
		return;
	}
	else{
		T* temp = find_node(k->get_key() , root);
		//cout<<"Hello";
		if (temp == NULL){
			cout << "Nothing to delete. Key is not present in the tree\n";
		}
		else if (temp->get_left() == NULL && temp->get_right() == NULL){
			if (temp == ((temp->get_parent())->get_left())){
				(temp->get_parent())->set_left(NULL);
			}
			else {
				(temp->get_parent())->set_right(NULL);
			}
		}
		else if (temp->get_left() != NULL && temp->get_right() == NULL){
			if (temp == ((temp->get_parent())->get_left())){
				(temp->get_parent())->set_left(temp->get_left());
			}
			else {
				(temp->get_parent())->set_right(temp->get_left());
			}
		}
		else if (temp->get_left() == NULL && temp->get_right() != NULL){
			if (temp == ((temp->get_parent())->get_left())){
				(temp->get_parent())->set_left(temp->get_right());
			}
			else {
				(temp->get_parent())->set_right(temp->get_right());
			}
		}
		else if (temp->get_left() != NULL && temp->get_right() != NULL){
			string sccsr = successor(temp , root);
			T* ps = new T;
			ps->set_key(sccsr);
			delete_node(ps , temp->get_right()); 
			temp->set_key(sccsr);
			return;
		}
		delete temp;
	}
	cout<<"Given key has been deleted\n";
	return ;
}

template <class T>
string bst<T>::successor(T* a , T* root){
	if (root == NULL){
		cout << "Tree is empty.\n";
		return "-1";
	}
	if (a->get_right() != NULL){
		return (min_of_tree(a->get_right() , root));		
	}
	else{
		T* y = a->get_parent();
		while(a != y->get_left() || y->get_parent() != NULL){
			a = y ;
			y = a->get_parent();
		}
		return y->get_key();
	}
}

template <class T>
string bst<T>::max_of_tree(T* a , T* root){
	if (root == NULL){
		cout << "Tree is empty.\n";
		return "-1";
	}
	T* temp = a->get_parent();
	while (a != NULL){
		temp = a;
		a = a->get_right();
	}
	cout << "Maximum key in the tree is : " << temp->get_key() << endl;
	return temp->get_key() ;
}

template <class T>
string bst<T>::min_of_tree(T* a , T* root){
	if (root == NULL){
		cout << "Tree is empty.\n";
		return "-1";
	}
	T* temp = a->get_parent();
	while (a != NULL){
		temp = a;
		a = a->get_left();
	}
	cout << "Minimum key in the tree is : " << temp->get_key() << endl;
	return temp->get_key();
}

template <class T>
void bst<T>::preorder(T* a , T* root){
	if (root == NULL){
		cout << "Tree is empty.\n";
		return;
	}
	if (a != NULL){
		cout << a->get_key() << "\t";
		preorder(a->get_left() , root);
		preorder(a->get_right() , root);
	}
}

template <class T>
void bst<T>::inorder(T* a , T* root){
	if (root == NULL){
		cout << "Tree is empty.\n";
		return;
	}
	if (a != NULL){
		inorder(a->get_left() , root);
		cout << a->get_key() << "\t";
		inorder(a->get_right() , root);
	}
}

template <class T>
void bst<T>::postorder(T* a , T* root) {
	if (root == NULL){
		cout << "Tree is empty.\n";
		return;
	}
	if (a != NULL){
		postorder(a->get_left() , root);
		postorder(a->get_right() , root);
		cout << a->get_key() << "\t";
	}
}

template <class T>
int bst<T>::height(T* count){		
	int l = 0;
	int r = 0;
	if(count == NULL){
		return 0;
	}
	l = height(count->get_left());
	r = height(count->get_right());
	if( l > r || l == r){
			return (l + 1);
		}

	else{
			return (r + 1);
	}
}


/***********************************************************************************************************************************/
					/*functions accessing AVL technique
/***********************************************************************************************************************************/

/************************************************************************************************/
							/*	functions of class avlnode */
/************************************************************************************************/

avlnode::avlnode(){
	leftchild = NULL;
	rightchild = NULL;
	parent = NULL;
	data = new student_record;
	bf = 0;
}

avlnode::~avlnode(){}

int avlnode::get_bf(){
	return bf;
}

void avlnode::set_bf(int n){
	bf = n;
}

avlnode* avlnode::get_left(){
	return leftchild;
}

avlnode* avlnode::get_right(){
	return rightchild;
}

avlnode* avlnode::get_parent(){
	return parent;
}

string avlnode::get_key(){
	return data->get_roll();
}

student_record& avlnode::get_record(){
	return *data;
}

void avlnode::set_left(avlnode* l){
	leftchild = l;
}

void avlnode::set_right(avlnode* r){
	rightchild = r;
}

void avlnode::set_parent(avlnode* p){
	parent = p;
}

void avlnode::set_key(string k){
	data->set_roll(k) ;
}

void avlnode::set_record(student_record &a){
	*data = a ;
}

/************************************************************************************************/
							/*	functions of class avl */
/************************************************************************************************/

template <class T>
avl<T>::avl(){
	avlroot = NULL;
}

template <class T>
avl<T>::~avl(){
	bst<T>::clear_tree(avlroot);			//as clear tree is a function of class bst
}

template <class T>
T* avl<T>::get_avlroot(){
	return avlroot;
}

template <class T>
void avl<T>::set_avlroot(T* a){
	avlroot = a;
}
template <class T>
int avl<T>::getting_bf(T* a){
	return (bst<T>::height(a->get_left()) - bst<T>::height(a->get_right()));
}

template<class T>
void avl<T>::balance(T* present){
	while((present->get_bf() != 2 || present->get_bf() != -2) && present != NULL){
		present->set_bf(getting_bf(present));
		cout << "present is : "<< present->get_key()<<endl;
		cout << "present's balance factor is : "<< present->get_bf()<<endl;
		if (present->get_bf() == 2 || present->get_bf() == -2)
			break;
		if(present->get_parent() == NULL){
			break;
		}
		present = present->get_parent();
	}
	if(present->get_left() != NULL && ((present->get_left())->get_bf() == 1)){
		if(present->get_bf() == 2 || present->get_bf() == -2){
			cout << "right rotation has been performed about : "<< present->get_key()<<endl;
			rotateright(present);
			present->set_bf(getting_bf(present));
			cout << "TEST key : " << present->get_key() << "\t" << "bf : " << present->get_bf() << endl;
		}
	}
	else if(present->get_left() != NULL && ((present->get_left())->get_bf() == -1)){
		if(present->get_bf() == 2 || present->get_bf() == -2){
			cout << "left rotation has been performed about : "<< (present->get_left())->get_key()<<endl;
			rotateleft(present->get_left());
			present->set_bf(getting_bf(present));
			cout << "TEST key : " << present->get_key() << "\t" << "bf : " << present->get_bf() << endl;
			cout << "right rotation has been performed about : "<< present->get_key()<<endl;
			rotateright(present);
			present->set_bf(getting_bf(present));
			cout << "TEST key : " << present->get_key() << "\t" << "bf : " << present->get_bf() << endl;
		}
	}
	else if(present->get_right() != NULL && ((present->get_right())->get_bf() == -1)){
		if(present->get_bf() == 2 || present->get_bf() == -2){
			cout << "left rotation has been performed about : "<< present->get_key()<<endl;
			rotateleft(present);
			present->set_bf(getting_bf(present));
			cout << "TEST key : " << present->get_key() << "\t" << "bf : " << present->get_bf() << endl;
		}
	}
	else if(present->get_right() != NULL && ((present->get_right())->get_bf() == 1)){
		if(present->get_bf() == 2 || present->get_bf() == -2){
			cout << "right rotation has been performed about : "<< (present->get_right())->get_key()<<endl;
			rotateright(present->get_right());
			present->set_bf(getting_bf(present));
			cout << "TEST key : " << present->get_key() << "\t" << "bf : " << present->get_bf() << endl;
			cout << "left rotation has been performed about : "<< present->get_key()<<endl;
			rotateleft(present);
			present->set_bf(getting_bf(present));
			cout << "TEST key : " << present->get_key() << "\t" << "bf : " << present->get_bf() << endl;
		}
	}
	else
		return;
}

template <class T>
void avl<T>::insert_avlnode(T* new_node){
	if (avlroot == NULL){		
		avlroot = new avlnode;							
		avlroot->set_record(new_node->get_record());			
		avlroot->set_left(NULL);						
		avlroot->set_right(NULL);
		avlroot->set_parent(NULL); 
		avlroot->set_bf(getting_bf(avlroot));
		cout << "Tree was empty firstly , now the node with key "<< avlroot->get_key() <<" is inserted at the root position\n"; 
		cout << "key : " << avlroot->get_key() << "\t" << "bf : " << avlroot->get_bf() << endl;
		return;
	}
	T* temproot = avlroot;
	T* current ;
	while (temproot != NULL){
		if (new_node->get_key() == temproot->get_key()){			//if given key is already present in the tree
			cout << "This key has already been inserted before. Cant insert it again.\n";	
			return ;
		}
		else if (new_node->get_key() < temproot->get_key()){		//if given key is less than the the root
			if (temproot->get_left() != NULL){
				temproot->set_bf(getting_bf(temproot));
				//cout << "TEST key : " << temproot->get_key() << "\t" << "bf : " << temproot->get_bf() << endl;
				temproot = temproot->get_left();

			}
			else{
				temproot->set_left(new_node);
				temproot->set_bf(getting_bf(temproot));
				//cout << "TEST key : " << temproot->get_key() << "\t" << "bf : " << temproot->get_bf() << endl;
				new_node->set_left(NULL);
				new_node->set_right(NULL);
				new_node->set_parent(temproot);
				new_node->set_bf(getting_bf(new_node));
				//cout << "TEST key : " << new_node->get_key() << "\t" << "bf : " << new_node->get_bf() << endl;
				cout << "The node with key "<< new_node->get_key()<<" is inserted to the left of "<<(new_node->get_parent())->get_key() <<"\n";
				current = new_node;
				break;
			}
		}
		else if (new_node->get_key() > temproot->get_key()){		//if given key is less than the the root
			if (temproot->get_right() != NULL){
				temproot->set_bf(getting_bf(temproot));
				//cout << "TEST key : " << temproot->get_key() << "\t" << "bf : " << temproot->get_bf() << endl;
				temproot = temproot->get_right();
			}
			else{
				temproot->set_right(new_node);
				temproot->set_bf(getting_bf(temproot));
				//cout << "TEST key : " << temproot->get_key() << "\t" << "bf : " << temproot->get_bf() << endl;
				new_node->set_left(NULL);
				new_node->set_right(NULL);
				new_node->set_parent(temproot);
				new_node->set_bf(getting_bf(new_node));
				//cout << "TEST key : " << new_node->get_key() << "\t" << "bf : " << new_node->get_bf() << endl;
				cout << "The node with key "<< new_node->get_key()<<" is inserted to the right of "<<(new_node->get_parent())->get_key() <<"\n";
				current = new_node;
				break;
			}
		}	
	}	
	balance(current);
	return;
}

template <class T>
void avl<T>::delete_avlnode(T* k , T* avlroot){
	T* current;
	if(avlroot == NULL){
		cout << "Nothing to delete.\n";
		return;
	}
	else{
		T* temp = bst<T>::find_node(k->get_key() , avlroot);
		if (temp == NULL){
			cout << "Nothing to delete. Key is not present in the tree\n";
			return;
		}
		else if (temp->get_left() == NULL && temp->get_right() == NULL){
			if (temp == ((temp->get_parent())->get_left())){
				current = temp->get_parent();
				current->set_left(NULL);
				delete temp ;
				current->set_bf(getting_bf(current));
				if(current->get_bf() == 2){
					rotateright(current);
					cout << "right rotation about : "<< current->get_key()<<endl;
				}
				if(current->get_bf() == -2){
					rotateleft(current);
					cout << "left rotation about : "<< current->get_key()<<endl;
				}
			}
			else {
				current = temp->get_parent();
				current->set_right(NULL);
				delete temp ;
				current->set_bf(getting_bf(current));
				if(current->get_bf() == -2){
					rotateleft(current);
					cout << "left rotation about : "<< current->get_key()<<endl;
				}
				if(current->get_bf() == 2){
					rotateright(current);
					cout << "right rotation about : "<< current->get_key()<<endl;
				}
			}
		}
		else if (temp->get_left() != NULL && temp->get_right() == NULL){
			if (temp == ((temp->get_parent())->get_left())){
				current = temp->get_parent();
				current->set_left(temp->get_left());
				delete temp ;
				current->set_bf(getting_bf(current));
				(temp->get_left())->set_parent(current);
				if(current->get_bf() == -2){
					rotateleft(current);
					cout << "left rotation about : "<< current->get_key()<<endl;
				}
				if(current->get_bf() == 2){
					rotateright(current);
					cout << "right rotation about : "<< current->get_key()<<endl;
				}
			}
			else {
				current = temp->get_parent();
				current->set_right(temp->get_left());
				(temp->get_left())->set_parent(current);
				delete temp ;
				current->set_bf(getting_bf(current));
				if(current->get_bf() == -2){
					rotateleft(current);
					cout << "left rotation about : "<< current->get_key()<<endl;
				}
				if(current->get_bf() == 2){
					rotateright(current);
					cout << "right rotation about : "<< current->get_key()<<endl;
				}
			}
		}
		else if (temp->get_left() == NULL && temp->get_right() != NULL){
			if (temp == ((temp->get_parent())->get_left())){
				current = temp->get_parent();
				current->set_left(temp->get_right());
				(temp->get_right())->set_parent(current);
				delete temp ;
				current->set_bf(getting_bf(current));
				if(current->get_bf() == -2){
					rotateleft(current);
					cout << "left rotation about : "<< current->get_key()<<endl;
				}
				if(current->get_bf() == 2){
					rotateright(current);
					cout << "right rotation about : "<< current->get_key()<<endl;
				}
			}
			else {
				current = temp->get_parent();
				current->set_right(temp->get_right());
				(temp->get_right())->set_parent(current);
				delete temp ;
				current->set_bf(getting_bf(current));
				if(current->get_bf() == -2){
					rotateleft(current);
					cout << "left rotation about : "<< current->get_key()<<endl;
				}
				if(current->get_bf() == 2){
					rotateright(current);
					cout << "right rotation about : "<< current->get_key()<<endl;
				}
			}
		}
		else if (temp->get_left() != NULL && temp->get_right() != NULL){
			string sccsr = bst<T>::successor(temp , avlroot);
			avlnode* ps = new avlnode;
			ps->set_key(sccsr);	
			delete_avlnode(ps , temp->get_right()); 
			temp->set_key(sccsr);
			return;
		}
	}
	balance(current);
	cout<<"Given key has been deleted\n";
	return ;
}

template <class T>
void avl<T>::rotateleft(T* n){
	T* temp = n->get_right();  
	n->set_right(temp->get_left());      
	if(temp->get_left() != NULL)      
    	temp->get_left()->set_parent(n);
   	if(n->get_parent() == NULL){
      	avlroot = temp;      
      	temp->set_parent(NULL);   
   	}
   	else if(n->get_parent()->get_left() == n){
      	n->get_parent()->set_left(temp); 
      	temp->set_parent(n->get_parent());
   	}
   	else{            
      	n->get_parent()->set_right(temp);
      	temp->set_parent(n->get_parent());
    }  	
   	temp->set_left(n);         
   	n->set_parent(temp);       
}

template <class T>
void avl<T>::rotateright(T* n){
	T* temp = n->get_left();  
	n->set_left(temp->get_right());      
	if(temp->get_right() != NULL)      
    	temp->get_right()->set_parent(n);
   	if(n->get_parent() == NULL){
      	avlroot = temp;      
      	temp->set_parent(NULL);   
   	}
   	else if(n->get_parent()->get_left() == n){
      	n->get_parent()->set_left(temp);   
      	temp->set_parent(n->get_parent());
   	}
   	else{
      	n->get_parent()->set_right(temp);
      	temp->set_parent(n->get_parent());
   	}
   	temp->set_right(n);         
   	n->set_parent(temp); 
}

template <class T>
void avl<T>::insert_file(char a[]){
	T* n;
	n = new T ;
	student_record x;
	ifstream File(a);
	while(File >> x){
		n->set_record(x);
		insert_avlnode(n);
		cout << "\n\n";
		n = new T;
	}
	delete n;
}

template <class T>
void avl<T>::insert_file(char a[] , T* n){
	insert_avlnode(n);	
	ofstream File(a,ios::app);
	File << n->get_record();	
}

template <class T>
void avl<T>::delete_filenode(char a[] , T* x){
	//insert_file(a);
	student_record k;
	ifstream File(a);
	ofstream tempfile("temp.txt");
	while(File >> k){ 
		if(k.get_roll() != x->get_key())
			tempfile << k;
		else if(k.get_roll() == x->get_key())
			continue;
	}
	File.clear(); 
	File.seekg(0, ios::beg);
	File.close();
	tempfile.close();
	remove(a); 
	rename("temp.txt",a);	
	delete_avlnode(x , avlroot);
}

