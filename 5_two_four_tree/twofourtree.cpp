#include <iostream>
#include <fstream> 
#include <string>
#include  "twofourtree.h"
#include <cmath>

using namespace std;


node_2_4::~node_2_4(){}				//destructor

/***********************************************************/

node_2_4* node_2_4::get_child_1(){
	return child[0];
}

node_2_4* node_2_4::get_child_2(){
	return child[1];
}

node_2_4* node_2_4::get_child_3(){
	return child[2];
}

node_2_4* node_2_4::get_child_4(){
	return child[3];
}

node_2_4* node_2_4::get_parent(){
	return parent;
}

string node_2_4::get_key_1(){
	return h[0]->get_roll();
}

string node_2_4::get_key_2(){
	return h[1]->get_roll();
}

string node_2_4::get_key_3(){
	return h[2]->get_roll();
}

/************************************************************************/

void node_2_4::set_child_1(node_2_4* a){
	child[0] = a ;
}

void node_2_4::set_child_2(node_2_4* a){
	child[1] = a ;
}

void node_2_4::set_child_3(node_2_4* a){
	child[2] = a ;
}

void node_2_4::set_child_4(node_2_4* a){
	child[3] = a ;
}

void node_2_4::set_parent(node_2_4* a){
	parent = a ;
}

void node_2_4::set_key_1(string k){
	h[0]->set_roll(k) ;
}

void node_2_4::set_key_2(string k){
	h[1]->set_roll(k) ;
}

void node_2_4::set_key_3(string k){
	h[2]->set_roll(k) ;
}

student_record* node_2_4::get_record(int i){
   	return h[i];
}

node_2_4* node_2_4::returnleftchild(int i){
    return child[i];
} 
	   
node_2_4* node_2_4::returnrightchild(int i){
    return child[i+1];
} 
	    
int node_2_4::isfull(){
	if(h[0]->get_roll() != "0" && h[1]->get_roll() != "0" && h[2]->get_roll() != "0")
   		return 3;
	else if(h[0]->get_roll() != "0" && h[1]->get_roll() != "0" && h[2]->get_roll() == "0")
	   	return 2;
	else if(h[0]->get_roll() != "0" && h[1]->get_roll() == "0" && h[2]->get_roll() == "0")
	   	return 1;
	else
		return 0;
}
		   
int node_2_4::isleaf(){
	int i;
	for(i = 0 ; i < 4 ; ++i){
		if(child[i] == NULL)
			continue;
		else
			break;
	}
	if(i==4)
		return 1;
	else 
		return 0;
}
			   
int node_2_4::no_of_records_in_node(){
	if(h[2]->get_roll() != "0")
		return 2;
	else if(h[1]->get_roll() != "0")
		return 1;
	else 
		return 0;
}
void node_2_4::set_record(student_record* a, int i){
	h[i] = a;
}

/************************************************************************************************/

tree_2_4::tree_2_4()  
{
	root=NULL;
}


bool tree_2_4:: isemptytree()
{
	return (root == NULL);
}


void tree_2_4:: inserttree(student_record* x)
{
	node_2_4* temp = root;
	node_2_4* curr = temp;
	int k , i;
	while(temp != NULL){
		for(i = 0 ; i < 3 ; ++i){
			if(x->get_roll() > temp->get_record(i)->get_roll() && temp->get_record(i)->get_roll() != "0")
				continue;
			else
				break;
		}
		curr = temp;
		temp = temp->child[i];
	}		
	if(curr != NULL){
		if(curr->isfull() != 3){
			arrange(x,curr);
		}
		else {
			node_2_4* left = new node_2_4;
		    node_2_4* right = new node_2_4;
		    seprate(left,right,x,curr);
			cascade(left,right,x,curr->parent);
		}
	}
	else if(curr == NULL){
		node_2_4* re = new node_2_4;
		root = re;
		arrange(x,root);
	}
}


node_2_4* tree_2_4::searchtree(node_2_4* z,student_record* x, int &j){
	node_2_4* temp=z;
	int i;	
	for(i = 0 ; i < 3 ; ++i){
		if(x->get_roll() == temp->get_record(i)->get_roll()){
			j = i;
			return temp;
		}
		else if(x->get_roll() > temp->get_record(i)->get_roll() && temp->get_record(i)->get_roll() != "0")
			continue;
		else
			break;
	}	
	node_2_4* y = temp->child[i];
	if(y == NULL)
		return NULL;
	else
		searchtree(y,x,j);
}


void tree_2_4:: deletetree(student_record* x){
	int j;
	int k;
	int aaaaa;
	node_2_4* found;
	node_2_4* see = searchtree(root,x,j);
	if(see == NULL){
		cout << "element not found\n";
		return;
	}
	
	if(see->isleaf() != 1){
		found=maximum(see->child[j],k);
		if (found->isfull()==1){
			see->set_record(found->get_record(k) , j);
			see = found;
			j = k;
		}
	}
	if(see->isleaf() == 1 && see->isfull() > 1){
		see->h[j]->set_roll("0");
		if(see->h[0]->get_roll()=="0"){
			see->set_record(see->get_record(1) , 0);
			see->set_record(see->get_record(2) , 1);
			see->get_record(2)->set_roll("0");
		}
		else if(see->get_record(1)->get_roll() == "0"){
			see->set_record(see->get_record(2) , 1);
			see->get_record(2)->set_roll("0");
		}
	}
	
	else if(see->isleaf()==0 && found->isfull()>1){
		see->set_record(found->get_record(k) , j);
		found->get_record(k)->set_roll("0");
	}
	
	else if(see->isleaf() == 1 && see->isfull() == 1){
		node_2_4* sib = sibling(see , aaaaa);
		see->get_record(j)->set_roll("0");
		if(sib->isfull() > 1){
			if(aaaaa == 0){
				if(see->get_parent()->get_child_1() == sib){
					see->set_record(see->get_parent()->get_record(aaaaa) , j);
					sib->get_parent()->h[aaaaa]=sib->h[sib->no_of_records_in_node()];
					sib->h[sib->no_of_records_in_node()]->set_roll("0");
				}
				else{
					see->h[j]=see->parent->h[aaaaa];
					see->parent->h[aaaaa]=sib->h[0];
					sib->h[0]->set_roll("0");
					if(sib->h[0]->get_roll() == "0"){
						sib->h[0]=sib->h[1];
						if(sib->h[2]->get_roll()!="0")
							sib->h[1]=sib->h[2];
						else
							sib->h[1]->set_roll("0");	
						sib->h[2]->set_roll("0");
					}
					else if(sib->h[1]->get_roll()=="0"){
						sib->h[1]=sib->h[2];
						sib->h[2]->set_roll("0");
					}
				}
				
			}
			else{
				see->h[j]=see->parent->h[aaaaa];
				sib->parent->h[aaaaa]=sib->h[sib->no_of_records_in_node()];
				sib->h[sib->no_of_records_in_node()]->set_roll("0");
			}
		}
		else if(sib->isfull()==1 && sib->parent->isfull()>1){
			if(aaaaa==0){
				if(see->parent->child[0]==sib){
					sib->h[1]=sib->parent->h[aaaaa];
					sib->parent->h[aaaaa]->set_roll("0");
					rearrange(see->parent);
					}
				else{
					sib->h[1]=sib->h[0];
					sib->h[0]=sib->parent->h[aaaaa];
					sib->parent->h[aaaaa]->set_roll("0");
					//cout << "hello8" <<endl;
					rearrange(see->parent);
					}
				
			}
			else{
				sib->h[1]=sib->parent->h[aaaaa];
					sib->parent->h[aaaaa]->set_roll("0");
					rearrange(see->parent);
				}
			}
		else if(sib->isfull()==1 && sib->parent->isfull()==1){
			node_2_4* merge=new node_2_4;
			if(aaaaa==0 && see->parent->child[1]==sib){
				merge->h[0]=see->parent->h[0];
				merge->h[1]=sib->h[0];
				see->parent->h[0]->set_roll("0");
			}
			else{
				merge->h[1]=see->parent->h[0];
				merge->h[0]=sib->h[0];
				see->parent->h[0]->set_roll("0");
			}	
			delcascade(merge,see->parent);
		}
	}
}

