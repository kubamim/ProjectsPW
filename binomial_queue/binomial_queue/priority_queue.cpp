#include "priority_queue.h"

using namespace std;

void priority_queue::insert(int v)
{
	node * to_insert = new node(v, 0, nullptr, nullptr, nullptr);
	to_insert->prev = to_insert;
	root = union_tree(root, to_insert);
}

int priority_queue::delete_max()
{
	//Find max element. The max() method will set the max_tree field properly
	int to_return = max();
	node * max_child = max_tree->child;

	//Extract max_tree
	if (max_tree->next)
		max_tree->next->prev = max_tree->prev;
	else
		root->prev = max_tree->prev;

	if (max_tree != root)
		max_tree->prev->next = max_tree->next;
	else
		root = root->next;

	//Delete root of max_tree
	delete max_tree;

	//Again add the rest of max_tree to the queue
	root = union_tree(root, max_child);

	return to_return;
}

int priority_queue::max()
{
	//Search for the root of max tree
	node* p = root->next;
	node* p_max = root;
	
	while (p)
	{
		if (p->v > p_max->v)
			p_max = p;
		p = p->next;
	}

	//Set the max_tree field of the class - used in the delete_max() method
	max_tree = p_max;

	return p_max->v;
}

priority_queue priority_queue::union_queues(priority_queue q1, priority_queue q2)
{
	//Create a new instance of the class. Use union_tree() to set the root field
	priority_queue to_return = priority_queue();
	to_return.root = q1.union_tree(q1.root, q2.root);
	return to_return;
}


void priority_queue::print()
{
	cout << "Priority queue. Elements:" << endl;

	//Use the recursive function to print all trees
	print_rec(root);
	cout << endl;
}

node * priority_queue::merge_tree(node * p1, node * p2)
{
	//Make sure that p1 is root with bigger value
	if (p1->v < p2->v)
	{
		node * t = p1;
		p1 = p2;
		p2 = t;
	}

	//Add p2 to the end of the list of children of p1
	if (!p1->child)
		p1->child = p2;
	else
	{
		p2->prev = p1->child->prev;
		p1->child->prev = p2;
		p2->prev->next = p2;
	}

	p1->rank++;

	return p1;
}

node * priority_queue::extract(node *& head)
{
	//Set p - pointer for the extracted tree. Set the head field
	node * p = head;
	head = head->next;

	if (head)
		head->prev = p->prev;

	p->next = nullptr;
	p->prev = p;

	return p;
}

void priority_queue::add_tree(node *& head, node * t)
{
	if (!head)
	{
		head = t;
		return;
	}

	head->prev->next = t;
	t->prev = head->prev;
	head->prev = t;
}

node * priority_queue::union_tree(node * p1, node * p2)
{
	node * q = nullptr, * last = nullptr, *t1, *t2;
	while (p1 || p2)
	{
		//Set next trees to add depending on ranks of the trees
		if (!p1)
		{
			t1 = extract(p2);
			t2 = nullptr;
		}
		else if (!p2)
		{
			t1 = extract(p1);
			t2 = nullptr;
		}
		else if (p1->rank == p2->rank)
		{
			t1 = extract(p1);
			t2 = extract(p2);
		}
		else if (p1->rank < p2->rank)
		{
			t1 = extract(p1);
			t2 = nullptr;
		}
		else
		{
			t1 = extract(p2);
			t2 = nullptr;
		}

		//Add the trees
		if (last && last->rank < t1->rank)
		{
			add_tree(q, last);
			last = nullptr;
		}

		if (!last && !t2)
			add_tree(q, t1);
		else if (!last)
			last = merge_tree(t1, t2);
		else if (!t2)
			last = merge_tree(t1, last);
		else
		{
			last = merge_tree(last, t1);
			add_tree(q, t2);
		}

	}

	//Check if there is a tree remaining after the loop
	if (last)
		add_tree(q, last);

	return q;
}

void priority_queue::print_rec(node * head)
{
	if (!head)
		return;
	cout << head->v << " ";
	print_rec(head->child);
	print_rec(head->next);
}
