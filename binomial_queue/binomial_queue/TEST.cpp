#include "priority_queue.h"
#include <iostream>

using namespace std;

int main()
{
	//Some tests for the methods:
	priority_queue p = priority_queue();
	priority_queue p2 = priority_queue();
	priority_queue p3 = priority_queue::union_queues(p, p2);
	srand(1);

	for (int i = 0; i < 100; i++)
		p.insert(rand());
	p.print();
	cout << endl << "Max element of p: " << p.max() << endl << endl;

	for (int i = 0; i < 50; i++)
		p.delete_max();
	p.print();
	cout << endl << "Max element of p:" << p.max() << endl << endl;

	
	for (int i = 0; i < 100; i++)
		p2.insert(rand());
	p2.print();
	cout << endl << "Max element: " << p2.max() << endl << endl;

	priority_queue p3 = priority_queue::union_queues(p, p2);
	p3.print();
	cout << endl << "Max element: " << p3.max() << endl << endl;

	system("pause");
	return 0;
}