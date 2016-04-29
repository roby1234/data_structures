#include <iostream>
#include <fstream> 
#include <string.h>
#include "dictionary.cpp"
#include <cmath>


using namespace std;

int main(int argc, char *argv[]){
int d;
cout << "Enter the type of dictionary you want to maintain:\n";
cout << "1-for BST....2-for AVL tree ....3-hashtables.....4- for 2-4trees\n";
cin >> d;



if(d==1){
int t;
cout << "Enter the type of traversal u want to make\n";
cout << "1-for Inorder....2-for Preorder....3-for Postorder traversal\n";
cin >> t;

binarytree samya;
bst ranjan;

ranjan.bst_insert(argv[1],samya);
cout << "the tree after insertion of record from file\n\n";
ranjan.bst_display(samya,t);

hospital_record x;
x.insertdata();
ranjan.bst_insert(argv[1],samya,x);
cout << "the tree after insertion of new record into the dictionary\n";
ranjan.bst_display(samya,t);
cout << "searching for the new record entered\n";
cout <<"Address of the searched element :"<<ranjan.bst_search(samya,x)<<endl;
cout << "Enter a record u want to delete\n";
x.insertdata();
ranjan.bst_delete(samya,x);
cout << "the tree after deletetion of  record from the  dictionary\n";
ranjan.bst_display(samya,t);

}

if(d==2){
	
	int t;
cout << "Enter the type of traversal u want to make\n";
cout << "1-for Inorder....2-for Preorder....3-for Postorder traversal\n";
cin >> t;
	
binarytree samya;
avltree ranjan;

ranjan.avl_insert(argv[1],samya);
cout << "the tree after insertion of record from file\n\n";
ranjan.bst_display(samya,t);

hospital_record x;
x.insertdata();
ranjan.avl_insert(argv[1],samya,x);
cout << "the tree after insertion of new record into the dictionary\n";
ranjan.bst_display(samya,t);
cout << "searching for the new record entered\n";
cout <<"Address of the searched element :"<<ranjan.bst_search(samya,x)<<endl;
cout << "Enter a record u want to delete\n";
x.insertdata();
ranjan.avl_delete(samya,x);
cout << "the tree after deletetion of  record from the  dictionary\n";
ranjan.bst_display(samya,t);
}

if(d==3){
	int n,t,u;

cout <<"Enter no of patient records in your file";
cin >> n;

cout << "choose your collison resolution technique\n";
cout <<"Enter 1-linear probing\n";
cout <<"Enter 2-chaining\n";
cout <<"Enter 3-double hashing\n";
cin >> u;

cout << "Enter no of slots in your hash table(choose a prime no)";
cin >>t;

if(u==1){
linear_list samya(t);

hashtable ranjan(t,1);
ranjan.hash_insert(argv[1],samya);
ranjan.display(samya);
hospital_record x;
x.insertdata();
ranjan.hash_insert(argv[1],x,samya);
ranjan.display(samya);
hospital_record y;
cout << ranjan.search(x,samya)<<endl;
ranjan.hash_delete(x,samya,y);
cout << ranjan.search(x,samya)<<endl;
ranjan.display(samya);

}

else if(u==3){

linear_list samya(t);

hashtable ranjan(t,3);

ranjan.hash_insert(argv[1],samya);

ranjan.display(samya);
hospital_record x;
x.insertdata();
ranjan.hash_insert(argv[1],x,samya);
ranjan.display(samya);
hospital_record y;
cout << ranjan.search(x,samya)<<endl;
ranjan.hash_delete(x,samya,y);
cout << ranjan.search(x,samya)<<endl;
ranjan.display(samya);


}


else if(u==2){

link_list samya(t);
link_list s(t);
hashtable ranjan(t,2);
ranjan.hash_insert(argv[1],samya);
ranjan.display(samya);
hospital_record x;
x.insertdata();
ranjan.hash_insert(argv[1],x,samya);
ranjan.display(samya);
cout << (ranjan.search(x,samya))<<endl;
ranjan.hash_delete(x,samya);
//cout << (ranjan.search(x,samya))<<endl;
ranjan.display(samya);


}


	}

if(d==4){
	
twofourtree samya;
two_four_tree ranjan;
int a,b;
hospital_record x;
cout << "--------welcome--------"<<endl;
char c='a';
while(c!='q'){
	
	cout << "Enter 0-to insert records from file into dictionary\n";
	cout << "Enter 1-to insert new record into dictionary\n";
	cout << "Enter 2-to search for a record in dictionary\n";
	cout << "Enter 3-for displaying records in dictionary\n";
	cout << "Enter 4-to delete a record from dictionary\n";
	cout << "Enter 5-to delete a record from dictionary and file\n";
	cout << "Enter q-to exit\n";
	cin >>c;
	
	
	if(c=='0'){
				ranjan.two_four_insert(argv[1],samya);
				cout << "----------------------------------\n";
		}
	else if(c=='1'){
				x.insertdata();
				ranjan.two_four_insert(argv[1],samya,x);
				cout<< "----------------------------------\n";
		}
	else if(c=='2'){
				cout << "enter patient's id  you want to search--";
				cin >> a;
				x.insertkey(a);
				cout <<"Address of the searched element :"<<ranjan.two_four_search(samya,x,b)<<endl;
				//cout << "position of the searched element :"<<b<<endl;
				cout<< "----------------------------------\n";
		}
	else if(c=='3'){
				int t;
				cout << "Enter the type of traversal u want to make\n";
				cout << "1-for Inorder....2-for Preorder....3-for Postorder traversal\n";
				cin >> t;
				ranjan.two_four_display(samya,t);
				cout << "----------------------------------\n";
		}
	else if(c=='4'){
				cout << "enter patient's id you want to delete from record--";
				cin >> a;
				x.insertkey(a);
				ranjan.two_four_delete(samya,x);
				cout<< "----------------------------------\n";
		}
	else if(c=='5'){
				cout << "enter patient's id you want to delete from record and file --";
				cin >> a;
				x.insertkey(a);
				ranjan.two_four_delete(argv[1],samya,x);
				cout << "----------------------------------\n";
		}
	else if(c=='q')break;
	}

	}

}
