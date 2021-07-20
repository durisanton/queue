#include<stdio.h>
#include<stack>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

/*****************************************************
 * Implementation of queue using two stacks,         *
 * including almost all of the member functions      *
 * whitch are included in std::queue.                *
 * 						     *
 * Functions: push, pop, front, rear, size, empty    *
 * (all functions using only stack member functions) *
 *						     *	
 * Main idea:					     *
 * We always need to have the oldest element on the  *
 * top of the stack. To make this real, we must push *
 * all elements from the first stack to second one,  *
 * then insert element to the first one and push     * 
 * back all elements to that stack.		     *
 ****************************************************/
class queue{
	stack<int> stack_1, stack_2;
	vector<int> element_vector;
	int input;
	void to_stack_2(), back_to_stack_1();
	void print(), push(), pop(), empty(), front(), back(), size(), save(), elements();	
	public:	
	ofstream queue_elements;
};

//push all elements from stack_1 to stack_2
void queue::to_stack_2()
{
	while(!stack_1.empty())
	{
		stack_2.push(stack_1.top());
		stack_1.pop();
	}
}

//push back all elements form stack_2 to stack_1
void queue::back_to_stack_1()
{
	while(!stack_2.empty())
	{
		stack_1.push(stack_2.top());
		stack_2.pop();
	}
}

//helper function for printing elements from stack_1
void queue::elements()
{ 
	if(stack_1.empty())
	{
		return;
	}

	while(!stack_1.empty())
	{
		element_vector.insert(element_vector.begin(), stack_1.top());
		stack_1.pop();
	}	

	for(auto i : element_vector)
	{
		stack_1.push(i);
	}
}

//function for printing elements
void queue::print()
{
	element_vector.clear();	
	queue::elements();

	cout << "***********************" << endl;
	cout << "Elements in queue: ";
	
	for (auto n : element_vector)
	{	
        	cout << n << " ";
	}		
	cout << "\n***********************" << endl;
}

//insert element form terminal to stack_1
void queue::push()
{
	to_stack_2();
	cout << "Insert element: ";
	cin >> input;
	stack_1.push(input);
	back_to_stack_1();
}

//checking wether queue is empty
void queue::empty()
{
	if(!stack_1.empty())
	{
		cout << "Queue is not empty!" << endl;
	}
	else
	{
		cout << "Queue is empty!" << endl;
	}
}

//removing oldest element from queue
void queue::pop()
{
	if(!stack_1.empty())
	{
		cout << "Oldest element removed!!!" << endl;
		stack_1.pop();
	}
	else
	{
		empty();
	}
}

//printing next element in queue
void queue::front()
{
	if(!stack_1.empty())
	{
		cout << "Next element is: " << stack_1.top() << endl;
	}
	else
	{
		empty();
	}
}

//printing last element in queue
void queue::back()
{
	if(!stack_1.empty())
	{
		to_stack_2();
		cout << "Last element is: " << stack_2.top() << endl;
		back_to_stack_1();
	}
	else
	{
		empty();
	}
}

//printing size of queue
void queue::size()
{
	cout << "Size of queue is: " << stack_1.size() << endl;
}

//to txt file
void queue::save()
{
	for (auto j : element_vector)
	{
		queue_elements << j << " ";
	}
	queue_elements << endl;
}

//printing menu 
void menu()
{
	cout << "1 - insert element" << endl;
	cout << "2 - remove next element" << endl;
	cout << "3 - access next element" << endl;
	cout << "4 - access last element" << endl;
	cout << "5 - size of queue" << endl;
	cout << "6 - test whether queue is empty" << endl;
	cout << "7 - print queue" << endl;
	cout << "8 - save to txt file" << endl;
	cout << "9 - exit" << endl;
}

//main loop 
int main()
{
	//initial declarations
	queue my_queue; //easier way -> namespace my_queue
	int selection;
	//ofstream queue_elements;
	my_queue.queue_elements.open("queue_elements.txt", ios::ate);
	//show menu in terminal
	menu();
	//infinite queue loop 	
	while(1)
	{
		cout << "Your selection: ";
		cin >> selection;
		switch(selection)
		{
			case 1: my_queue.push(); cout << endl; my_queue.print(); cout << endl; break;
			case 2: my_queue.pop(); cout <<endl; my_queue.print(); cout << endl; break;
			case 3: my_queue.front(); break;
			case 4: my_queue.back(); break;
			case 5: my_queue.size(); break;
			case 6: my_queue.empty(); break;
			case 7: cout << endl; my_queue.print(); cout << endl; break;
			case 8: my_queue.save(); break;
			case 9: goto end;	
			default: cout << "Wrong option :/" << endl;
		}
	}
	//close txt file
	end: my_queue.queue_elements.close();	

	return 0;
}
