#pragma once
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

//Struct for the node of the main list of elements
struct node
{
	node(node* next, int v) : next(next), v(v) {};

	node* next;
	int v;
};

//Struct for the node of temporary list
struct tmp_list
{
	tmp_list(node* list, tmp_list* next) : list(list), next(next) {};

	node* list;
	tmp_list* next;
};

class sort_file
{
public:
	//Load the file and create sorted list of all number (integer) values
	sort_file(string path);

	//Print the list of elements
	void print();

private:
	node * sentinel;
	list<int> sorted_list;

	//Non-recursive merge sort 
	void merge_sort(node *& head);

	//Create temporary lists. Used in merge_sort() 
	void create_lists(node * head, tmp_list *& head2);

	//Merge the temporary lists created in create_lists()
	void merge_lists(tmp_list *& head2);

	//Merge two lists
	node * merge(node * head1, node * head2);

	//Extract a node from the beginning of [head_in] list and add to end of [head_out] list
	void shift_to_end(node *& head_in, node *& head_out, node *& tail_out);
};
