#include <iostream>
#include <fstream> 
#include <string.h>
#include <string>
#include <cmath>
#include <stdlib.h>
#include "dictionary.cpp"

int main(int argc, char *argv[]){
	int no_of_records,size_of_hash_table, choice;
	cout <<"How many student records are there in your file??\n";
	cin >> no_of_records;
	cout << "Enter no of slots in your hash table(choose a prime no)\n";
	cin >> size_of_hash_table;
	cout << "How do u want to manipulate the hash table. Plz select the technique\n";
	cout <<"Press 1 for linear probing\n";
	cout <<"Press 2 for chaining\n";
	cout <<"Press 3 for double hashing\n";
	cin >> choice;

	if(choice == 1){
		linear_list list(size_of_hash_table);			
		dictionary dict(size_of_hash_table,choice);			
		dict.insert(argv[1],list);
		//cout << "break 1\n";
		dict.display(list);
		//cout << "break 2\n";
		student_record student;
		student.insert_data();
		dict.insert(argv[1] , student , list);
		dict.display(list);
		//cout << "break 3\n";
		student_record naughty;
		cout << list.search(student) << endl;
		dict.hash_delete(student , list , naughty);
		cout << dict.search(student , list) << endl;
		dict.display(list);
		//cout << "break 4\n";
	}
	else if(choice == 2){
		linked_list list(size_of_hash_table);
		dictionary dict(size_of_hash_table , choice);
		dict.insert(argv[1] , list);
		cout << "break 1\n";		
		dict.display(list);
		cout << "break 2\n";
		student_record student;
		student.insert_data();
		dict.insert(argv[1] , student , list);
		dict.display(list);
		cout << "break 3\n";
		cout << (dict.search(student , list)) << endl;
		dict.hash_delete(student,list);
		dict.display(list);
		cout << "break 4\n";
	}
	else if(choice == 3){
		linear_list list(size_of_hash_table);
		dictionary dict(size_of_hash_table , choice);
		dict.insert(argv[1] , list);
		//cout << "break 4\n";
		dict.display(list);
		//cout << "break 4\n";
		student_record student;
		student.insert_data();
		dict.insert(argv[1],student,list);
		dict.display(list);
		//cout << "break 4\n";
		student_record naughty;
		cout << dict.search(student , list) << endl;
		dict.hash_delete(student , list , naughty);
		cout << dict.search(student , list) << endl;
		dict.display(list);
		//cout << "break 4\n";
	}
	else if (choice != 1 || choice != 2 || choice != 3){
		cout << "u hv enterd a wrong key\n";
		exit(0);
	}
	return 0;
}
