#include <iostream>
#include "sort_file.h"

using namespace std;

int main()
{
	//Tests for the methods:
	sort_file f("file_to_sort.txt");

	cout << "Sorted numbers found the file:" << endl;
	f.print();
	cout << endl;

	system("pause");
	return 0;
}