#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include "student_record.cpp"
using namespace std;


/***********************************************************************************************************************************/

/***********************************************************************************************************************************/
class linear_list : public student_record{				//class linear list inheriting the class student record	
private:
	int size;
	student_record *record;
	int len;
public:									//public functions of the class linear list 
	linear_list(int  maxsize){
		size = maxsize-1;
		record = new student_record[maxsize];
		for(int i = 0 ; i < maxsize ; i++){
			record[i].set_roll("000");
		}
		len = 0;
	}
	linear_list(const linear_list &l){
		size = l.size;
		record = new student_record[size];
		for(int i = 0 ; i < size ; i++){
			record[i].set_roll("000");
		}
		len = l.len;
		memcpy(record , l.record , size);
	}
	~linear_list(){
		delete[] record;
	}
	bool isempty(){
		return (len == 0 ? 1 : 0) ;
	}
	int return_length(){
		return len;
	}
	int get_size(){
		return size;
	}
	int search(student_record &x){				//searching a record in the linear list
		for(int i=0;i<len;i++){
			if(record[i].get_roll() == x.get_roll()) 
				return 1;
		}
		return 0;
	}
	void deleteElement(int  k, student_record &x){		//deleting a record in the linear list
		if(k < 0 || k > size)
			cout << "cant be deleted ;; wrong input to the function"<<endl;
		else{
			x=record[k];
			record[k].set_roll("000");
		}
	}
	student_record* return_element(int k){
		if (k < 0 || k > size){
			cout <<"error , wrong entry!!!\n";
		}
		else
			return &record[k];
	}
	void insert(student_record &x){				//inserting a record in the linear list at successive pos
		len = len + 1;
		if (len <= size)
			record[len] = x;
		else 
			cout <<"error , TABLE FULL!!!\n";
	}
	void insert(int k , student_record &x){			//inserting a record in the linear list at given pos	
		if (k < 0 || k > size)
			cout <<"error , wrong entry!!!\n";
		len = len + 1;
		if (len <= size)
			record[k] = x;
		else 
			cout <<"error , TABLE FULL!!!\n";
	}
};

/***********************************************************************************************************************************/

/***********************************************************************************************************************************/

