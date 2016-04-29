#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

class student_record{						//class Student Record
private:
	string roll_no;
	string firstname;
	string address;
	string branch;
	double cgpa;
	string email;
	long int phone_no;
public:
	string get_roll(){
		return roll_no;					
	}
	void set_roll(string roll){
		roll_no  = roll;
	}
	string get_name(){
		return firstname;
	}
	friend ostream &operator<<(ostream &os, const student_record &s){
		os << s.roll_no << '\n';
		os << s.firstname<< '\n';
		os << s.address<< '\n';
		os << s.branch<< '\n';
		os << s.cgpa<< '\n';
		os << s.email<< '\n';
		os << s.phone_no<< '\n';
		return os;
	}
	friend istream &operator>>(istream &is, student_record &s){
		is >> s.roll_no ;
		is >> s.firstname;
		is >> s.address ;
		is >> s.branch ;
		is >> s.cgpa ;
		is >> s.email ;
		is >> s.phone_no ;	
		return is;
	}
		
	void insert_data(){					//function for inserting record in the table
		cout <<"enter roll no.	";
		cin >>roll_no;
		cout <<"enter name	";
		cin >>firstname;	
		cout <<"enter address	";
		cin >>address;
		cout <<"enter branch	";
		cin >>branch;
		cout <<"enter cgpa	";
		cin >>cgpa;
		cout <<"enter email id	";
		cin >>email;
		cout <<"enter phone no.	";
		cin >>phone_no;
	}
};

