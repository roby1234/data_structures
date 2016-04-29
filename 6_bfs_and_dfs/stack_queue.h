#ifndef _STACK_QUEUE_H_
#define _STACK_QUEUE_H_

using namespace std;

template <class T>
class stack{				//Last In First Out structure
	private:
		int size;
		T* array;
		int top; 
		int length;
	public:
		stack(int);				//constructor
		~stack();				//destructor
		bool is_empty();		//return true if stack is empty
		int size_of_stack();	//return the size of the stack
		void pop_back();		//pop the top element of stack and top pointer points to the descending element
		void push_back(T&);		//push the new element in the stack and top pointer points to the ascending element
		T& return_top();		//return the top element of the stack
		int top_position();		//return position of top pointer
		void print_stack();
};

template <class T>	
class queue{				//First In First Out structure
	private:
		int size;
		T* array;
		int front;
		int rear;
		int length;
	public:
		queue(int n);				//constructor
		~queue();				//destructor
		bool is_empty();		//return true if queue is empty
		int size_of_queue();	//return the size of the queue
		void dequeue();			//pop the element from front of queue and front pointer points to the descending element
		void enqueue(T&);		//push the new element in the rear of queue and rear pointer points to the descending element
		T& return_front();				//return the front element of the queue
		int front_position();	//return position of front pointer
		T& return_rear();				//return the rear element of the queue
		int rear_position();	//return position of rear pointer
		void print_queue();
};

#endif