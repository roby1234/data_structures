#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

class info{
private:
	int key;
	int weight;
public:
	info(){
		key = -1 ;
		weight = 0;
	}
	int get_key(){
		return key;
	}
	void set_key(int a){
		key = a;
	}
	int getwt(){
		return weight;
	}
	void setwt(int a){
		weight = a;
	}
};

class node : public info{
private:
	node* next;
	info* data;
public:
	node(){
		next = NULL;
		data = new info();
	}
	node* get_next(){
		return next;
	}
	void set_next(node* p){
		next = p;
	}
	int get_element(){
		return data->get_key();
	}
	int get_weight(){
		return data->getwt();
	}
	void set_element(int s){
		data->set_key(s);
	}
	void set_weight(int a){
		data->setwt(a);
	}
};


/***********************************************************************************************************************************/

/***********************************************************************************************************************************/

class linked_list : public node
{
private:
	node* head;
	node* tail;
	int* len;
public:
	void set_head(node* p){
		head = p;
	}

	node* get_head(int u){
		return (head+u);
	}

	int get_length(int u){
		return len[u];
	}

	linked_list(){
		head = NULL;
		tail = NULL;
		len = NULL;	
	}

	linked_list(const linked_list &l){
		head = new node;
		tail = new node;
		len = new int;
		head = NULL;
		tail = NULL;
		len = NULL;	
	}
	linked_list(int m){					//m is the no of vertices
		head = new node[m];
		tail = new node[m];
		len = new int[m];
		for(int i = 0 ; i < m ; ++i){
			head[i].set_element(-1);
			head[i].set_weight(0);
			len[i]=0;
			head[i].set_next(NULL);
			tail[i].set_next(head+i);		//next pointer of all tail pointers pointing to their respective heads 
		}
	}

	~linked_list(){
		node *temp;
		while(head){
			temp = head->get_next();
        		delete head;
        		head = temp;
    		}
    		delete[] len;
	}

	void insertlist(int x , int i , int w){	// this function inserts the integer at the end of linked list
		node *temp1 = new node;
		temp1->set_element(x) ;
		temp1->set_weight(w);
		//cout<<temp1->get_weight()<<endl;
		temp1->set_next(NULL) ;
		if((head+i)->get_element() == -1){		//checks if first node is inserted
		    (head+i)->set_element(temp1->get_element());
		    (head+i)->set_weight(temp1->get_weight());
			head[i].set_next(NULL);
			len[i]++;
    	}
    	else{
        	(tail[i].get_next())->set_next(temp1);		//if node inserted goes into chain
			(tail+i)->set_next(temp1);
			len[i]++;
    	}
	}

	void printlist(int k){								//prints out the integers in linked list
		node *temp ;
		temp = head + k;
		while(temp){
			if(temp->get_element() == -1)
				break;
			cout<< temp->get_element() <<"( "<< temp->get_weight() <<" )"<< "\t";
			temp = temp->get_next();
		}
	}

	node* findlist (int  k, int &x){
		node *temp;
		temp = head + k;
		while(temp){
			if(temp->get_element() == x)
				return temp;
			temp=temp->get_next();
		}
		return NULL;
	}

	void deletelist(int k, int x){
		node *temp;
		node *curr;
		temp = head + k;
		curr = temp;
		while(temp){
			if(temp->get_element() == x){
				if(temp == head + k){
					temp->set_element(-1);
					temp->set_weight(-1);
					break;
				}
				else if(temp->get_next() == NULL){
					(tail+k)->set_next(curr);
					curr->set_next(NULL);
					break;
				}
			}
			else{
				curr = temp;
				temp = temp->get_next();
			}
		}
	}
	
	int searchlist(int k , int x){
		if(findlist(k,x) == NULL)
			return 0;
		else
			return 1;
	}

	int countlist(int b){
		return len[b];
	}
};
//int main(){return 0;}
