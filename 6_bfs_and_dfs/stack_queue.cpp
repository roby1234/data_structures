#include "stack_queue.h"
#include <iostream>
#include <cmath>

//#define n 100
using namespace std;

template <class T>
stack<T>::stack(int n){					//constructor
	length = n;
	array = new T[n] ;
	/*for (int i = 0; i < n; ++i){
		array[i] = -2;
	}*/
	top = -1;
	size = 0;
}			

template <class T>	
stack<T>::~stack(){					//destructor
	delete[] array;
}

template <class T>
bool stack<T>::is_empty(){			//return true if stack is empty
	return (size == 0);
}

template <class T>
int stack<T>::size_of_stack(){		//return the size of the stack
	return size;
}

template <class T>
void stack<T>::pop_back(){			//pop the top element of stack and top pointer points to the descending element
	if(is_empty()){
		cout<<"Stack empty\n";
		return;
	}
	else {
		cout << "position of top = " << top <<endl;
		cout << "Element " << array[top] << " has been deleted from the " << (top) << "th position of the stack\n";
		top--;
		size--;
		cout << "position of New top = " << top <<endl<<endl;
		print_stack();
		return;
	}
}

template <class T>
void stack<T>::push_back(T& x){		//push the new element in the stack and top pointer points to the ascending element
	if (top >= length ){
		cout << "Stack Overflow\n";
		int k = 2*length;
		T* stack1 = new T[k];
		for (int i = 0; i < length ; ++i){
			stack1[i] = array[i];
			top = i;
		}
		delete[] array;
		array = stack1;
		cout << "position of top = " << top <<endl;
		array[++top] = x;
		cout << "Element " << x << " has been added to the " << top << "th position of the stack\n"; 
		cout << "position of New top = " << top << endl<<endl; 
		size++;
		print_stack();
		return;  
	}
	else
		cout << "position of top = " << top <<endl;
		array[++top] = x;
		cout << "Element " << x << " has been added to the " << top << "th position of the stack\n"; 
		cout << "position of New top = " << top << endl<<endl;
		size++; 
		print_stack();
		return;
}

template <class T>
T& stack<T>::return_top(){					//return the top element of the stack
	if(top != -1 && top < length){
		return array[top];
	}
	else 
		cout << "Empty Stack\n";
}

template <class T>
int stack<T>::top_position(){		//return position of top pointer
	return top;
}

template <class T>
void stack<T>::print_stack(){
	if(top < 0){
		cout <<"Stack Empty\n";
		return;
	}
	cout << "Stack::\n";
	for (int i = top ; i >= 0; i--){
		cout << array[i] << "\n";
	}
	cout << endl;
}
/**********************************************************************************************************************************/

template <class T>
queue<T>::queue(int n){					//constructor
	length = n;
	array = new T[n];
	/*for (int i = 0; i < n; ++i){
		array[i] = -2;
	}*/
	size = 0 ;
	rear = -1 ;
	front = -1 ;
}

template <class T>	
queue<T>::~queue(){					//destructor
	delete[] array;
}

template <class T>
bool queue<T>::is_empty(){			//return true if queue is empty
	if (front == rear)
		return 1;
	else 
		return 0;
}

template <class T>
int queue<T>::size_of_queue(){		//return the size of the queue
	return (rear - front);
}

template <class T>
void queue<T>::dequeue(){			//pop the element from front of queue and front pointer points to the descending element
	if (is_empty()){
		cout<<"Queue empty\n";
		return;
	}
	else{
		cout << "front = " << front <<" and rear = " << rear <<endl;
		cout << "Element " << array[(front + 1)%length] << " has been deleted from the " << (front + 1)%length << "th position of the queue\n";
		(++front)%length;
		cout << "New front = " << front <<" and New rear = " << rear <<endl<<endl;
		print_queue();
		return;
	}
}

template <class T>
void queue<T>::enqueue(T &x){			//push the new element in the rear of queue and rear pointer points to the descending element
	if ((rear-front) >= length ){
		cout << "Queue Overflow\n";
		int k = 2*length;
		T* queue1 = new T[k];
		for (int i = 0; i < length ; ++i){
			queue1[i] = array[i];
			rear = i;
		}
		delete[] array;
		array = queue1;
		cout << "front = " << front <<" and rear = " << rear <<endl;
		array[(++rear)%length] = x;
		cout << "Element " << x << " has been added to the " << rear << "th position of the queue\n"; 
		cout << "New front = " << front <<" and New rear = " << rear <<endl << endl<<endl; 
		print_queue();
		return; 
	}
	else{
		cout << "front = " << front <<" and rear = " << rear <<endl;
		array[(++rear)%length] = x;
		cout << "Element " << x << " has been added to the " << rear << "th position of the queue\n"; 
		cout << "New front = " << front <<" and New rear = " << rear <<endl << endl;
		print_queue();
		return;
	}
}

template <class T>
T& queue<T>::return_front(){				//return the front element of the queue
	return array[(front + 1)%length];
}

template <class T>
int queue<T>::front_position(){		//return position of front pointer
	return front;
}

template <class T>
T& queue<T>::return_rear(){				//return the rear element of the queue
	return array[(rear)];
}

template <class T>
int queue<T>::rear_position(){		//return position of rear pointer
	return rear;
}

template <class T>
void queue<T>::print_queue(){
	if(is_empty()){
		cout <<"Queue Empty\n";
		return;
	}
	cout << "Queue::\n";
	for (int i = (front + 1); i <= rear; ++i){
		cout << array[i] << "\t";
	}
	cout << endl<<endl;
}
//int main(){return 0;}