#ifndef tree_2_4_h
#define tree_2_4_h

#include <algorithm>

#include "dictionary.cpp"
using namespace std;

class node_2_4{
public:
	node_2_4* parent;
	student_record* h[3];
	node_2_4* child[4];
	   
public:
	friend class tree_2_4;
	node_2_4(){
	child[0] = NULL ;
	child[1] = NULL ;
	child[2] = NULL ;
	child[3] = NULL ;
	h[0]->set_roll("0") ;
	h[1]->set_roll("0") ;
	h[2]->set_roll("0") ;
	parent = NULL ;
	}
	~node_2_4();
	node_2_4* get_child_1();
	node_2_4* get_child_2();
	node_2_4* get_child_3();
	node_2_4* get_child_4();
	node_2_4* get_parent();
	string get_key_1();
	string get_key_2();
	string get_key_3();

	void set_child_1(node_2_4*);
	void set_child_2(node_2_4*);
	void set_child_3(node_2_4*);
	void set_child_4(node_2_4*);	
	void set_parent(node_2_4*);
	void set_key_1(string);
	void set_key_2(string);
	void set_key_3(string);

	student_record* get_record(int);
	void set_record(student_record* , int); 
    node_2_4* returnleftchild(int); 
	node_2_4* returnrightchild(int);
	int isfull();
	int isleaf(); 
	int no_of_records_in_node();
};


class tree_2_4{
private:
	node_2_4* root;
	   
protected:
    void changeroot(node_2_4* x , tree_2_4* r){
    	r->root = x;
    }
      
public:	
    tree_2_4();						//constructor
	~tree_2_4();					//destructor
	bool  isemptytree();
	int  heightoftree();
	node_2_4* searchtree(node_2_4* z , student_record* x , int &i);
	void deletetree(student_record* x);
	void inserttree(student_record* x);
	node_2_4* get_root(){
		return root;
	}
	void set_root(node_2_4* a){
		root = a;
	}


	void arrange(student_record* x , node_2_4* y){
		int k = y->isfull();
		int m = y->isleaf();
		if(m == 1){
			int i;
			if(k == 0){
				y->set_record(x , 0);
			}
			else{
				for(i=k-1 ; i >= 0 ; --i){
					if(x->get_roll() < y->get_record(i)->get_roll())
						y->set_record(y->get_record(i) , i+1);
					else
						break;
				}
				y->set_record(x , i+1);
			}
		}
	}
			
	void cascade(node_2_4* left , node_2_4* right , student_record* x , node_2_4* y){
		if(y != NULL)
			int m = y->isleaf();
		else if(y == NULL){
			node_2_4* kkk = new node_2_4;
			kkk->set_record(left->get_record(1) , 0);
			left->get_record(1)->set_roll("0");
			kkk->set_child_1(left);
			kkk->set_child_2(right);
			kkk->get_child_1()->set_parent(kkk);
			kkk->get_child_2()->set_parent(kkk);	
			set_root(kkk);		
		}
		else if(y->isfull() != 3){
			int i;
			for(i = y->isfull()-1 ; i >= 0 ; --i){
				if(left->get_record(1)->get_roll() < y->get_record(i)->get_roll()){
					y->set_record(y->get_record(i) , i+1);
					y->child[i+2] = y->child[i+1];
				}
				else 
					break;
			}
			y->set_record(left->get_record(1) , i+1);
			left->get_record(1)->set_roll("0");
			y->child[i+1] = left;
			y->child[i+2] = right;
			left->set_parent(y);
			right->set_parent(y);
		}
		else if(y->isfull()==3){
			node_2_4* newleft = new node_2_4;
		    node_2_4* newright = new node_2_4;
		    student_record* l;
		    l = left->get_record(1);
		    left->get_record(1)->set_roll("0");
		    student_record* s[4];
		    node_2_4* sc[5];
			int j = 0;
			int k;
			int q , u;
			for(q = 0 ; q < 4 ; ++q){
				if(y->get_record(j)->get_roll() < l->get_roll() && j<3){
					s[q] = y->get_record(j);
					sc[q] = y->child[j];
					++j;
				}
				else{
					s[q] = l;
					sc[q] = left;
					sc[q+1] = right;
					break;
				}
			}
			for(k = j ; k < 3 ; ++k){
				++q;
				s[q] = y->h[k];
				sc[q+1] = y->child[k+1];
			}
			newleft->set_record(s[0] , 0);
			newleft->set_child_1(sc[0]);
			newleft->set_child_2(sc[1]);
			newleft->get_child_2()->set_parent(newleft);
			newleft->get_child_1()->set_parent(newleft);
			newleft->set_record(s[1] , 1);
			for(u = 2 ; u < 4 ; ++u){
				newright->set_record(s[u] , u-2);
				newright->child[u-2] = sc[u];  
				newright->child[u-2]->set_parent(newright);
			}
			newright->child[u-2] = sc[u];
			newright->child[u-2]->set_parent(newright);
			cascade(newleft , newright , s[1] , y->parent);
		}
	}
			
	void seprate(node_2_4* left , node_2_4* right , student_record* x , node_2_4* y){
		student_record* s[4];
		int j = 0;
		int k , i;
		for( i = 0 ; i < 4 ; ++i){
			if(y->get_record(j)->get_roll() < x->get_roll() && j < 3){
				s[i] = y->get_record(j);
				++j;
			}
			else{
				s[i] = x;
				break;
			}
		}
		for(k = j ; k < 3 ; ++k){
			++i;
			s[i] = y->get_record(k);
		}
		left->set_record(s[0] , 0);
		left->set_record(s[1] , 1);
		right->set_record(s[2] , 0);
		right->set_record(s[3] , 1);
	}
			
			
	void inorder(node_2_4* x){
		if(x != NULL){
			if(x->get_record(0)->get_roll() != "0"){
				inorder(x->returnleftchild(0));
				for(int i = 0 ; i < 3 ; ++i){
					if(x->get_record(i)->get_roll() != "0"){
						cout << *(x->get_record(i)) << endl;
						inorder(x->returnrightchild(i));
					}
				}
			}
		}
	}
	
	void preorder(node_2_4* x){
		if(x!=NULL){
			if(x->get_record(0)->get_roll() != "0"){
				cout << *(x->get_record(0)) <<endl;
				preorder(x->returnleftchild(0));
				preorder(x->returnrightchild(0));
				if(x->get_record(1)->get_roll() != "0"){
					cout << *(x->get_record(1)) <<endl;
					preorder(x->returnrightchild(1));
					if(x->get_record(2)->get_roll() != "0"){
						cout << *(x->get_record(2)) <<endl;
						preorder(x->returnrightchild(2));
					}
				}
			}
		}
	}
	
	void postorder(node_2_4* x){	
		if(x!=NULL){
			if(x->get_record(0)->get_roll() != "0"){
				postorder(x->returnleftchild(0));
				postorder(x->returnrightchild(0));
				cout << *(x->get_record(0)) <<endl;
				if(x->get_record(1)->get_roll() != "0"){
					postorder(x->returnrightchild(1));
					cout << *(x->get_record(1)) <<endl;
					if(x->get_record(2)->get_roll() != "0"){
						postorder(x->returnrightchild(2));
						cout << *(x->get_record(2)) <<endl;
					}
				}
			}
		}
	}
 
 	node_2_4* sibling(node_2_4* x,int& j){
		node_2_4* tem = x->get_parent();
		int i;
		for(i = 0 ; i < 4 ; ++i){
			if(tem->child[i] == x)
				break;
		}
		if(i == 0){
			j=0;
			return tem->get_child_2();
		}
		else if(i==3){
			j=2;
			return tem->get_child_3();
		}
		else{
			j=i-1;
			return tem->child[j];
		}
	}
				
	void rearrange(node_2_4* x){
		if(x->get_record(0)->get_roll() == "0" && x->get_child_1()->isfull() == 0){
			for(int i = 1 ; i < 3 ; ++i){
				x->set_record(x->get_record(i) , i-1);
				x->child[i-1] = x->child[i];
			}
			x->get_record(2)->set_roll("0");
			x->set_child_3(x->get_child_4());
			x->set_child_4(NULL);
		}
		else if(x->get_record(0)->get_roll() == "0" && x->get_child_2()->isfull() == 0){
			for(int i = 1 ; i < 3 ; ++i){
				x->set_record(x->get_record(i) , i-1);
				x->child[i] = x->child[i+1];
			}
			x->get_record(2)->set_roll("0");
			x->set_child_4(NULL);
		}
		else if(x->get_record(1)->get_roll() == "0"){
			x->set_record(x->get_record(2) , 1);
			x->get_record(2)->set_roll("0");
			x->set_child_3(x->get_child_4());
			x->set_child_4(NULL);
		}
	}
				
	node_2_4* maximum(node_2_4* x, int &j){
		int i ;
		if(x->isleaf() == 1){
			for(i = 2 ; i >= 0 ; --i){
				if(x->get_record(i)->get_roll() != "0")
					break;
			}
			j = i;
			return x;
		}
		else{
			for( i = 2 ; i >= 0 ; --i){
				if(x->child[i+1] != NULL)
					break;
			}
			maximum(x->child[i+1] , j );
		}
	}
				
	void delcascade(node_2_4* merge, node_2_4* see){
		int pa;
		node_2_4* sib;
		if(see->parent != NULL)
			sib = sibling(see , pa);
		if(see->parent == NULL)
			root = merge;			
		else if(sib->isfull() > 1 && see->isfull() == 0){
			if(pa == 0){
				if(see->get_parent()->get_child_1() == sib){
					see->set_record(see->parent->get_record(pa) , 0);
					sib->get_parent()->set_record(sib->get_record(sib->no_of_records_in_node()) , pa);
					sib->get_record(sib->no_of_records_in_node())->set_roll("0");
					see->set_child_1(sib->child[sib->no_of_records_in_node()+1]);
					sib->child[sib->no_of_records_in_node() + 1] = NULL;
					see->set_child_2(merge);
					merge->set_parent(see);
					see->get_child_1()->set_parent(see);
				}
				else{
					see->set_record(see->get_parent()->get_record(pa) , 0);
					sib->get_parent()->set_record(sib->get_record(0) , pa);
					sib->get_record(0)->set_roll("0");
					see->set_child_2(sib->get_child_1());
					see->set_child_1(merge);
					merge->set_parent(see);
					see->get_child_2()->set_parent(see);
					if(sib->get_record(0)->get_roll() == "0"){
						sib->set_record(sib->get_record(1) , 0);
						sib->child[0]=sib->child[1];
						sib->h[1]=sib->h[2];
						sib->child[1]=sib->child[2];
						sib->child[2]=sib->child[3];
						sib->child[3]=NULL;
						sib->h[2]->set_roll("0");
					}
				}
			}
			else{
				see->h[0]=see->parent->h[pa];
				sib->parent->h[pa]=sib->h[sib->no_of_records_in_node()];
				sib->h[sib->no_of_records_in_node()]->set_roll("0");
				see->child[0]=sib->child[sib->no_of_records_in_node()+1];
				sib->child[sib->no_of_records_in_node()+1]=NULL;
				see->child[1]=merge;
				merge->parent=see;
				see->child[0]->parent=see;
				}
		}
		else if(sib->isfull()==1 && see->isfull()==0){
			if(sib->parent->isfull()>1){
				if(pa==0){
					if(see->parent->child[0]==sib){
						sib->h[1]=sib->parent->h[pa];
						sib->parent->h[pa]->set_roll("0");
						sib->child[2]=merge;
						merge->parent=sib;
						rearrange(see->parent);
					}
					else{
						sib->h[1]=sib->h[0];
						sib->h[0]=sib->parent->h[pa];
						sib->parent->h[pa]->set_roll("0");
						sib->child[1]=sib->child[0];
						sib->child[2]=sib->child[1];
						sib->child[0]=merge;
						merge->parent=sib;
						rearrange(see->parent);
					}
				}
				else{
					sib->h[1]=sib->parent->h[pa];
					sib->parent->h[pa]->set_roll("0");
					sib->child[2]=merge;
					merge->parent=sib;
					rearrange(see->parent);
				}
			}
			else if(sib->parent->isfull()==1){
				node_2_4* newmerge= new node_2_4;
				if(pa==0 && see->parent->child[1]==sib){
					newmerge->h[0]=see->parent->h[0];
					newmerge->h[1]=sib->h[0];
					see->parent->h[0]->set_roll("0");
					newmerge->child[0]=merge;
					newmerge->child[1]=sib->child[0];
					newmerge->child[2]=sib->child[1];
					newmerge->child[2]->parent=newmerge;
					newmerge->child[1]->parent=newmerge;
					newmerge->child[0]->parent=newmerge;
				}
				else{
					newmerge->h[1]=see->parent->h[0];
					newmerge->h[0]=sib->h[0];
					see->parent->h[0]->set_roll("0");
					newmerge->child[2]=merge;
					newmerge->child[0]=sib->child[0];
					newmerge->child[1]=sib->child[1];
					newmerge->child[2]->parent=newmerge;
					newmerge->child[1]->parent=newmerge;
					newmerge->child[0]->parent=newmerge;
				}
				delcascade(newmerge,see->parent);
			}
		}
	}
};

class two_four_tree{
	private:
	
	public:
	
	void two_four_insert(char a[],tree_2_4& z)
	    {
	    
		  student_record x;
		  ifstream record(a);
		  while(record >> x)
		  { 
			 
			z.inserttree(&x);
			
		  }
		  record.close();
	    
	    }
	    
	 void two_four_insert(char a[],tree_2_4& x,student_record& y)
	    {
	    
		  ofstream record(a,ios::app);
		  record << y; 
		  x.inserttree(&y);
	    
	    }
	    
	    void two_four_delete(tree_2_4& x,student_record& y){
		  
		  x.deletetree(&y);
		 
	    }
	    
	     void two_four_delete(char a[],tree_2_4& x,student_record& y){
		  two_four_delete(x,y);
		  
		  student_record k;
		  ifstream record(a);
		  ofstream temp("temp.txt");
     
		  while(record >> k) 
		  { 
			if(k.get_roll()!=y.get_roll())
			temp << k;
			else if(k.get_roll()==y.get_roll())
			continue;
		  }
		  record.clear(); // clear eof and fail bits
		  record.seekg(0, ios::beg);
		  record.close();
		  temp.close();
		  remove(a); 
		  rename("temp.txt",a);
	    }
	    
	    node_2_4 * two_four_search(tree_2_4& z,student_record& y,int& a)
	    {
			
		  return z.searchtree(z.get_root(),&y,a);
	    }
	    void two_four_display(tree_2_4& z,int k)
	    {
			if(k==1)
	    z.inorder(z.get_root());
			else  if(k==2)
		 z.preorder(z.get_root());
			else  if(k==3)
		 z.postorder(z.get_root());
	    }
	};


#endif
