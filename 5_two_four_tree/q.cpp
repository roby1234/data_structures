#include <iostream>
#include <fstream> 
#include <string.h>
#include <string>

#include <cmath>
#include  "twofourtree.h"


using namespace std;

int main(int argc, char *argv[]){
int d;
cout << "Enter the type of dictionary you want to maintain:\n";
cout << "1-for BST....2-for AVL tree ....3-hashtables.....4- for 2-4trees\n";
cin >> d;
if(d==4){
	
tree_2_4 tree;
two_four_tree camera;
string a,b;
student_record x;
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
				camera.two_four_insert(argv[1],tree);
				cout << "----------------------------------\n";
		}
	else if(c=='1'){
				x.insert_data();
				camera.two_four_insert(argv[1],tree,x);
				cout<< "----------------------------------\n";
		}
	else if(c=='2'){
				cout << "enter patient's id  you want to search--";
				cin >> a;
				x.set_roll(a);
				cout <<"Address of the searched element :"<<camera.two_four_search(tree,x,b)<<endl;
				//cout << "position of the searched element :"<<b<<endl;
				cout<< "----------------------------------\n";
		}
	else if(c=='3'){
				int t;
				cout << "Enter the type of traversal u want to make\n";
				cout << "1-for Inorder....2-for Preorder....3-for Postorder traversal\n";
				cin >> t;
				camera.two_four_display(tree,t);
				cout << "----------------------------------\n";
		}
	else if(c=='4'){
				cout << "enter patient's id you want to delete from record--";
				cin >> a;
				x.set_roll(a);
				camera.two_four_delete(tree,x);
				cout<< "----------------------------------\n";
		}
	else if(c=='5'){
				cout << "enter patient's id you want to delete from record and file --";
				cin >> a;
				x.set_roll(a);
				camera.two_four_delete(argv[1],tree,x);
				cout << "----------------------------------\n";
		}
	else if(c=='q')break;
	}

	}

}
