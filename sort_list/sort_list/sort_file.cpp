#include "sort_file.h"

sort_file::sort_file(string path)
{
	//Load the file. Initialize all fields
	ifstream file(path);
	char c;
	node* head = nullptr;
	sentinel = new node(nullptr, INT16_MAX);

	//Check for any errors
	if (file.fail() || file.eof())
		return;

	//Load integer values from the file (any other character treated as separator)
	while (!file.eof())
	{
		file.get(c);
		if (c >= '0' && c <= '9')
		{
			head = new node(nullptr, c - '0');
			break;
		}
	}

	node * p = head;
	bool the_same_number = true;
	while (!file.eof())
	{
		file.get(c);
		if (c >= '0' && c <= '9')
		{
			if (the_same_number)
			{
				p->v = 10 * p->v + (c - '0');
			}
			else
			{
				p->next = new node(nullptr, c - '0');
				p = p->next;
				the_same_number = true;
			}
		}
		else
			the_same_number = false;
	}

	file.close();

	//Sort the list
	merge_sort(head);

	//Add the elements to STL list<int>
	while (head != sentinel)
	{
		sorted_list.push_back(head->v);
		head = head->next;
	}
}

void sort_file::print()
{
	auto print = [](int a) { cout << a << " "; };

	for_each(sorted_list.begin(), sorted_list.end(), print);
}

void sort_file::merge_sort(node *& head)
{
	tmp_list * head2 = nullptr;

	//Create lists of substrings that are in proper order
	create_lists(head, head2);

	//Merge the lists and return
	merge_lists(head2);

	head = head2->list;
	delete head2;
}

void sort_file::create_lists(node * head, tmp_list *& head2)
{
	if (!head)
		return;

	//Add the first element to the temporary list
	node* p = head;
	head = head->next;
	p->next = nullptr;

	head2 = new tmp_list(p, nullptr);
	head2->next = head2;

	tmp_list* last_tmp_list = head2;
	node* last_node = head2->list;

	//Create cyclic list of substrings in proper order
	while (head)
	{
		node* p = head;
		head = head->next;
		p->next = nullptr;

		if (last_node->v <= p->v)
		{
			last_node->next = p;
			last_node = p;
		}
		else
		{
			tmp_list* new_tmp_list = new tmp_list(p, head2);
			last_tmp_list->next = new_tmp_list;
			last_node->next = sentinel;

			last_node = p;
			last_tmp_list = new_tmp_list;
		}

		if (last_node)
			last_node->next = sentinel;
	}
}

void sort_file::merge_lists(tmp_list *& head2)
{
	//Merge the lists in temporary list using merge() method
	while (head2->next != head2)
	{
		head2->list = merge(head2->list, head2->next->list);

		tmp_list* p = head2->next;
		head2->next = head2->next->next;
		delete p;

		head2 = head2->next;
	}
}

node* sort_file::merge(node* head1, node * head2)
{
	//Merge - classic algorithm from Merge Sort
	node * head = nullptr, * tail = nullptr;
	while (!tail || tail != sentinel)
		if (head1->v < head2->v)
			shift_to_end(head1, head, tail);
		else
			shift_to_end(head2, head, tail);
	return head;
}

void sort_file::shift_to_end(node *& head_in, node *& head_out, node *& tail_out)
{
	if (!head_in)
		return;

	node* p = head_in;
	head_in = head_in->next;
	p->next = nullptr;

	if (!head_out)
	{
		head_out = tail_out = p;
	}
	else
	{
		tail_out->next = p;
		tail_out = p;
	}
}


