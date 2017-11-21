// g++ -Wall -g -O0 -pedantic -ansi -std=c++11 list.cpp -o list

#include <iostream>
#include "list.h"
#include <list>

int main(int argc, char const *argv[])
{
	//std::list<int> li;
	ls::list<int> l;
	/*l.push_front(12);
	l.push_front(13);
	l.push_front(14);
	l.push_front(15);
	l.push_front(16);
	l.push_front(17);
	l.push_front(18);
	l.push_front(19);*/

	for(int a = 0; a < 9; ++a){
		l.push_front(a);
		//li.push_front(a);
	}

	/*l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();*/

	auto iter = l.begin(); //iter++; iter++; iter++;
	
	std::cout << *iter << std::endl;

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


	std::cout << l.front() << std::endl;
	std::cout << l.back() << std::endl;

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
	for(auto i = l.begin(); i != l.end(); ++i)
	{
		std::cout << *i << std::endl;
	}	
	return 0;
}