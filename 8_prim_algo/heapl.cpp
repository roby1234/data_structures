#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <string.h>


using namespace std;

class heapnode{
private:
	int v;
	int key;
public:
	heapnode(){
		key = -1 ;
		v = -1 ;
	}

	heapnode* create_heap_node(int v , int k){
		heapnode* node = new heapnode;
		node->v = v;
		node->key = k;
		return node;
	}

	int get_key(){
		return key;
	}
	void set_key(int a){
		key = a;
	}
	int get_vertex(){
		return v;
	}
	void set_vertex(int a){
		v = a;
	}
};

class heap : public heapnode
{
private:
	int size;
	int capacity;
	int* pos;
	heapnode** array;
public:
	heap(int c){
		pos = new int[c];
		size = 0;
		capacity = c;
		array = new heapnode*[c];
	}
	
	~heap(){
		delete[] array ;
	}

	heap* create_heap(int c){
		heap* minheap  = new heap(c);
		minheap->pos = this->pos;
		minheap->size = this->size;
		minheap->capacity = this->capacity;
		minheap->array = this->array;
		return minheap ;
	}

	void swap_node( heapnode** a , heapnode** b){
		heapnode* temp = *a ;
		*a = *b ;
		*b = temp;
	}

	heapnode* get_array(int i){
		return array[i];
	}

	void set_array(int i , heapnode* u){
		array[i] = u;
		//cout << "array's "<< i <<"th position's vertex is set to " << u->get_vertex() << endl;
		//cout << "array's "<< i <<"th position's key is set to " << u->get_key() << endl;
	}

	int get_position(int i){
		return pos[i];
	}

	void set_position(int i , int a){
		pos[i] = a;
		//cout << "pos "<< i <<"th position is set to " << a << endl<<endl<<endl;
	}


	int left(int i){
		return ((2*i) + 1);
	}

	int right(int i){
		return ((2*i) + 2);
	}

	int parent(int i){
		return ((i-1)/2);
	}

	int is_empty(){
		return (size == 0);
	}	

	int get_size(){
		return size;
	}
	
	void set_size(int a){
		size = a;
	}

	void heapify(int i){
		if(is_empty()){
			cout <<"Heap Empty\n";
			return ;
		}
		int l =left(i);
		int r =right(i);
		int smallest = i; 
		if(l < size && array[l]->get_key() < array[smallest]->get_key())
			smallest = l;

		if(r < size && array[r]->get_key() < array[smallest]->get_key())
			smallest = r;

		if (smallest != i){

			pos[array[smallest]->get_vertex()] = i ;					//swapping position 
			pos[array[i]->get_vertex()] = smallest ;

			swap_node(&(array[smallest]) , &(array[i]));		//swapping the nodes
			heapify(smallest);
		}
	}
	
	void heap_decrease_key(int v, int k){
		if(is_empty()){
			cout <<"Heap Empty\n";
			return;
		}
		int i = pos[v];
		array[i]->set_key(k);

		while (i && array[i]->get_key() < array[parent(i)]->get_key()){
			pos[array[i]->get_vertex()] = parent(i);
			pos[array[parent(i)]->get_vertex()] = i;							//swapping position 

			swap_node(&(array[i]) , &(array[parent(i)]));						//swapping the nodes

			i = parent(i);
		}
	}

	heapnode* extract_min(){
		if(is_empty()){
			cout <<"Heap Empty\n";
			return NULL;	
		}
		heapnode* root = array[0];
		heapnode* last = array[size - 1];
		array[0] = last;

		pos[root->get_vertex()] = size - 1;
		pos[last->get_vertex()] = 0;
		size--;
		heapify(0);
		return root;
	}

	bool is_vertex_present(heap* h , int v){
		if (h->pos[v] < h->get_size())
			return 1;
		return 0;
	}

};