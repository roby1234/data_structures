#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include "linked_list.cpp"

using namespace std;

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
 
 
