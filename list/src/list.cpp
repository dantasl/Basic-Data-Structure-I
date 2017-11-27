// g++ -Wall -g -O0 -pedantic -ansi -std=c++11 list.cpp -o list

#include <iostream>
#include "list.h"
#include <list>

int main(int argc, char const *argv[])
{
	ls::list<int> l;

	for(int a = 1; a < 10; ++a)
		l.push_back(a);

	for(auto i = l.begin(); i != l.end(); ++i)
	{
		std::cout << *i << std::endl;
	}

	ls::list<int> l2 = l;

	std::cout << std::endl;

	for(auto j = l2.begin(); j != l2.end(); ++j)
	{
		std::cout << *j << std::endl;
	}

	l2 = {1, 2, 3, 4, 5};

	ls::list<int> l3 = {1, 2, 3, 4, 5, 6};

	ls::list<int> l4(l3.begin(), l3.end());
	auto pos = l4.begin(); pos++; pos++; pos++;
	l4.insert( pos, {120, 123, 124, 124, 152} );

	for(auto j = l4.begin(); j != l4.end(); ++j)
	{
		std::cout << *j << std::endl;
	}

	//l4.insert( l4.begin(), 120 );

	std::cout << std::endl << std::endl;
	//std::cout << *found << std::endl;

	//std::list<int> l4 = {1, 2, 3, 4, 5, 6};

	/*std::cout << std::endl;

	for(auto j = l2.begin(); j != l2.end(); ++j)
	{
		std::cout << *j << std::endl;
	}*/



	/*l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();*/

	//auto iter = l.begin(); //iter++; iter++; iter++;
	
	//std::cout << *iter << std::endl;

	//l.insert(iter, 100);

	/*l.pop_back();
	l.pop_back();
	l.pop_back();
	l.pop_back();
	l.pop_back();
	l.pop_back();
	l.pop_back();
	l.pop_back();
	l.pop_back();*/


	//std::cout << l.front() << std::endl;
	//std::cout << l.back() << std::endl;

	//l.assign(1);
	//l.assign(1);
	
	//l.clear();

	std::cout << std::endl << std::endl;
	/*

	//std::cout << *(l.begin()) << std::endl;
	

	//l.push_front(14);
	std::cout << l.front() << std::endl;
	std::cout << l.back() << std::endl;
	std::cout << l.size() << std::endl; */
	

	
	return 0;
}