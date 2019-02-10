#pragma once
#include <iostream>

using namespace std;

//struct for a node of binomial tree
struct node
{
	node(int v, int rank, node* next, node* prev, node* child) : v(v), rank(rank), next(next), prev(prev), child(child) {};
	int v;
	int rank;
	node* next;
	node* prev;
	node* child;
};

class priority_queue
{
public:
	//Construct an empty queue
	priority_queue() {};

	//Insert element of the specified value
	void insert(int v);

	//Delete and return maximum element
	int delete_max();

	//Find maximum element
	int max();

	//Return union of queues
	static priority_queue union_queues(priority_queue q1, priority_queue q2);

	//Print all elements
	void print();

private:
	node * root;
	node * max_tree;

	//Merge two binomial trees of the same rank
	node * merge_tree(node * p1, node * p2);

	//Extract first tree from binomial queue (of least height)
	node * extract(node *& head);

	//Add tree (with root pointed by t) to the end of binomial queue (root pointed by  head)
	void add_tree(node *& head, node * t);

	//Union binomial queues (roots pointed by p1 and p2) using algorithm for adding binary numbers
	node * union_tree(node* p1, node* p2);

	//Recursive function used in print() method
	void print_rec(node * head);
};
