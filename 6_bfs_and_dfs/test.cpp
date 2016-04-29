#include "graph.cpp"
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "cstdlib"

using namespace std;

int main(int argc, char *argv[])
{
	stack<int> q(5);
	int z;
	for (int i = 0; i < 5; ++i)
	{
		cin >> z;
		q.push_back(z);
		q.print_stack();
	}
	q.pop_back();
	q.print_stack();
	q.pop_back();
	q.print_stack();
	return 0;
}