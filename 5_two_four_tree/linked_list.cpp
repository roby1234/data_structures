#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include "linear_list.cpp"

using namespace std;

class node{
private:
	node* next;
	student_record record;
public:
	node* get_next(){
		return next;
	}
	void set_next(node* p){
		next = p;
	}
	student_record& get_record(){
		return record;
	}
	void set_record(student_record &s){
		record = s;
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
	linked_list(int m){					//m is the size of table
		head = new node[m];
		tail = new node[m];
		len = new int[m];
		for(int i = 0 ; i < m ; ++i){
			head[i].get_record().set_roll("000");
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
    		delete [] len;
	}

	void insertlist(student_record &x,int i){	// this function inserts the integer at the end of linked list
		node *temp1=new node;
		temp1->get_record() = x;
		temp1->set_next(NULL);
		if((head+i)->get_record().get_roll() == "000"){	//checks if first node is inserted
		        (head+i)->set_record(temp1->get_record());
			head[i].set_next(NULL);
			len[i]++;
    		}
    		else{
        		(tail[i].get_next())->set_next(temp1);		//if node inserted goes into chain
			(tail+i)->set_next(temp1);
			len[i]++;
        
    		}
	}

	void printlist(int k){				//prints out the integers in linked list
		node *temp;
		temp = head + k;
		while(temp){
			if(temp->get_record().get_roll()=="000")
				break;
			cout<< temp->get_record() <<endl;
			temp = temp->get_next();
		}
	}

	node* findlist (int  k, student_record &x){
		node *temp;
		temp = head + k;
		while(temp){
			if(temp->get_record().get_roll() == x.get_roll())
				return temp;
			temp=temp->get_next();
		}
		return NULL;
	}

	void deletelist(int  k, student_record& x){
		node *temp;
		node *curr;
		temp = head + k;
		curr=temp;
		while(temp){
			if(temp->get_record().get_roll() == x.get_roll()){
				if(temp == head + k){
					temp->get_record().set_roll("000");
					break;
				}
				else if(temp->get_next() == NULL){
					(tail+k)->set_next(curr);
					curr->set_next(NULL);
					break;
				}
			}
			else{
				curr=temp;
				temp=temp->get_next();
			}
		}
	}
	
	int searchlist(int  k,student_record &x){
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
