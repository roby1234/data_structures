#include <iostream>
#include <fstream> 
#include <string.h>
#include <string>
#include <cmath>
#include <stdlib.h>
#include "dictionary.cpp"

int main(int argc, char *argv[]){
	cout << "Which ds u wanna use ??\n";
	cout << "1. Hashing\n2. BST\n3. AVL Tree\n";
	int tech;
	cin >> tech;
	if (tech == 1)
	{
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
			// cout << "break 1\n";		
			dict.display(list);
			// cout << "break 2\n";
			student_record student;
			student.insert_data();
			dict.insert(argv[1] , student , list);
			dict.display(list);
			// cout << "break 3\n";
			cout << (dict.search(student , list)) << endl;
			dict.hash_delete(student,list);
			dict.display(list);
			// cout << "break 4\n";
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
	}
	else if(tech == 2)
	{
		bst<bstnode> bin;
		student_record x;
		bin.insert_file(argv[1]);
		cout << "\nrecords present in the file have been entered\n\n";
		int choice;
    	string num;
    	bstnode* temp = NULL;
    	while (1)
    	{
        	cout<<"-----------------"<<endl;
        	cout<<"Operations on BST"<<endl;
        	cout<<"-----------------"<<endl;
        	cout<<"1.Insert Element "<<endl;
        	cout<<"2.Delete Element "<<endl;
			cout<<"3.Search Element"<<endl;
			cout<<"4.Find element"<<endl;
			cout<<"5.Find maximum element"<<endl;
			cout<<"6.Find minimum element"<<endl;
        	cout<<"7.Inorder Traversal"<<endl;
        	cout<<"8.Preorder Traversal"<<endl;
        	cout<<"9.Postorder Traversal"<<endl;
        	cout<<"10.Height of tree "<<endl;
        	cout<<"11.Quit"<<endl;
       		cout<<"Enter your choice : ";
        	cin>>choice;
			if (choice == 1){
				temp = new bstnode ;
        	    cout << "Enter the record to be inserted : \n";
	    		x.insert_data();
           		//cout<< "name::::: " << x.get_name()<<endl;
	       		//cin >> num;
	       	 	//cout<<temp->get_key()<<endl;
				temp->set_record(x);
            	//cout << "name::::: " << x.get_name()<<endl;
            	//cout << (temp->get_record()).get_roll() << endl;		
            	bin.insert_file(argv[1] , temp);
			}	

			else if (choice == 2){
            	if (bin.get_root() == NULL){
        	    	cout<<"Tree is empty, nothing to delete"<<endl;
                	continue;
            	}
            	cout<<"Enter the number to be deleted : ";
            	cin >> num;
            	temp = new bstnode;
            	temp->set_key(num);
            	bin.delete_filenode(argv[1] , temp);
			}

				else if (choice == 3){
    	        cout << "Enter the number to be searched : \n";
		        cin >> num;
    	        bin.search_node(num, bin.get_root());
			}
	
    		else if (choice == 4){
    	        cout << "Enter the number to be found : \n";
		    	cin >> num;
    	        bin.find_node(num, bin.get_root());
			}
	
			else if (choice == 5){
    	        bin.max_of_tree(bin.get_root() , bin.get_root());
			}
	
			else if (choice == 6){
    	        bin.min_of_tree(bin.get_root() , bin.get_root());
			}
	
    		else if (choice == 7){ 
    	        cout<<"Inorder Traversal of BST:"<<endl;
    	        bin.inorder(bin.get_root() , bin.get_root());
    	        cout<<endl;
			}

    		else if (choice == 8){
    	        cout<<"Preorder Traversal of BST:"<<endl;
    	        bin.preorder(bin.get_root() , bin.get_root());
    	        cout<<endl;
			}

    		else if (choice == 9){
    	        cout<<"Postorder Traversal of BST:"<<endl;
    	        bin.postorder(bin.get_root() , bin.get_root());
    	        cout<<endl;
			}
		
			else if (choice == 10){
    	        cout<< bin.height(bin.get_root()) <<endl;
			}
	
    		else if (choice == 11){
    	        exit(1);
			}
	
			else {           
    	        cout<<"Wrong choice"<<endl;
    	        exit(0);
    		}
		}
	}
	else if (tech == 3)
	{
		avl<avlnode> bin;
    	student_record x;
    	bin.insert_file(argv[1]);
    	cout << "\nrecords present in the file have been entered\n\n";
    	int choice;
    	string num;
    	avlnode* temp = NULL;
    	while (1)
    	{
        	cout<<"-----------------"<<endl;
        	cout<<"Operations on AVL"<<endl;
        	cout<<"-----------------"<<endl;
        	cout<<"1.Insert Element "<<endl;
        	cout<<"2.Delete Element "<<endl;
			cout<<"3.Search Element"<<endl;
			cout<<"4.Find element"<<endl;
			cout<<"5.Find maximum element"<<endl;
			cout<<"6.Find minimum element"<<endl;
        	cout<<"7.Inorder Traversal"<<endl;
        	cout<<"8.Preorder Traversal"<<endl;
        	cout<<"9.Postorder Traversal"<<endl;
       		cout<<"10.Height of tree "<<endl;
        	cout<<"11.Quit"<<endl;
        	cout<<"Enter your choice : ";
        	cin>>choice;
			if (choice == 1){
        	    temp = new avlnode ;
        	    cout << "Enter the record to be inserted : \n";
        	    x.insert_data();
        	    //cout<< "name::::: " << x.get_name()<<endl;
        	    //cin >> num;
        	    //cout<<temp->get_key()<<endl;
        	    temp->set_record(x);
        	    //cout << "name::::: " << x.get_name()<<endl;
        		//cout << (temp->get_record()).get_roll() << endl;      
           	 	bin.insert_file(argv[1] , temp);
        	}	

        	else if (choice == 2){
            	if (bin.get_avlroot() == NULL){
            	    cout<<"Tree is empty, nothing to delete"<<endl;
                	continue;
            	}
            	cout<<"Enter the number to be deleted : ";
            	cin >> num;
            	temp = new avlnode;
            	temp->set_key(num);
            	bin.delete_filenode(argv[1] , temp);
        	}


			else if (choice == 3){
            	cout << "Enter the number to be searched : \n";
	        	cin >> num;
            	bin.search_node(num, bin.get_avlroot());
			}

    		else if (choice == 4){
            	cout << "Enter the number to be found : \n";
	    		cin >> num;
            	bin.find_node(num, bin.get_avlroot());
			}
	
			else if (choice == 5){
            	bin.max_of_tree(bin.get_avlroot() , bin.get_avlroot());
			}
	
			else if (choice == 6){
            	bin.min_of_tree(bin.get_avlroot() , bin.get_avlroot());
			}

    		else if (choice == 7){ 
           		cout<<"Inorder Traversal of AVL:"<<endl;
            	bin.inorder(bin.get_avlroot() , bin.get_avlroot());
            	cout<<endl;
			}	

    		else if (choice == 8){
            	cout<<"Preorder Traversal of AVL:"<<endl;
            	bin.preorder(bin.get_avlroot() , bin.get_avlroot());
            	cout<<endl;
			}	

    		else if (choice == 9){
            	cout<<"Postorder Traversal of AVL:"<<endl;
            	bin.postorder(bin.get_avlroot() , bin.get_avlroot());
            	cout<<endl;
			}
	
			else if (choice == 10){
        	    cout<< bin.height(bin.get_avlroot()) <<endl;
			}

    		else if (choice == 11){
        	    exit(1);
			}

			else {           
            	cout<<"Wrong choice"<<endl;
            	exit(0);
    		}
		}
	}

	else{           
           	cout<<"Wrong choice"<<endl;
           	exit(0);
    }
	return 0;
}
