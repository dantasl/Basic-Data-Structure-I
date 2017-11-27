/**
 * @file    driver_list.cpp
 * @brief   Testing functions implemented in list.h
 * @author  Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @date    27/11/2017 
 * @since   26/11/2017
 */

#include <iostream>
#include <cassert>
#include <initializer_list>
#include "list.h"

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
	// Testing constructors and assignment operators
	{
		// Constructor with default T () instances.
		ls::list<std::string> l(5);
		for (auto i = l.begin(); i != l.end(); ++i) assert( (*i).empty() );

		// Constructor with initializer list.
		ls::list<int> l2( { 1, 2, 3, 4, 5 } );
		int c(1);
		for (auto i = l2.begin(); i != l2.end(); ++i, ++c) assert( (*i) == c );

		// Deep copy constructor.
		ls::list<int> l3( l2 );
		for (auto i = l3.begin(), j = l2.begin(); i != l3.end(), j != l2.end(); ++i, ++j)
			assert( (*i) == (*j) );

		// Constructor with range.
		ls::list<int> l4( l3.begin(), l3.end() );
		for (auto i = l4.begin(), j = l3.begin(); i != l4.end(), j != l3.end(); ++i, ++j)
			assert( (*i) == (*j) );

		// List assignment operator
		ls::list<int> l5;
		l5 = l4;
		for (auto i = l5.begin(), j = l4.begin(); i != l5.end(), j != l4.end(); ++i, ++j)
			assert( (*i) == (*j) );

		// Initializer list assignment operator
		ls::list<int> l6;
		l6 = { 1, 2, 3, 4, 5 };
		c = 1;
		for (auto i = l6.begin(); i != l6.end(); ++i, ++c) assert( (*i) == c );
	}
	
	// Testing Capacity and Modifiers
	{
		// Testing push_back, push_front, front(), back(), size() and empty()
		ls::list<double> l;
		for (auto i = 0; i < 9.0; ++i) l.push_back( i * 2.0 );
		for (auto i = 0; i < 9.0; ++i) l.push_front(i * 3.0 );
		assert( l.front() == 24.0 );
		assert( l.back() == 16.0 );
		assert( l.size() == 18 );
		assert( not l.empty() );

		// Testing pop_front() and pop_back()
		l.pop_front();
		l.pop_back();
		assert( l.front() == 21.0 );
		assert( l.back() == 14.0 );
		assert( l.size() == 16 );

		// Testing assign()
		l.assign(10.0);
		for (auto i = l.begin(); i != l.end(); ++i) assert( (*i) == 10.0 );

		// Testing clear()
		l.clear();
		assert( l.size() == 0 );
		assert( l.empty() );
	}

	// Testing Modifiers with Iterators
	{
		// Testing assign() with range
		ls::list<int> l( { 1, 2, 3, 4, 5, 6, 7 } );
		ls::list<int> l2( { 14, 15, 16 } );
		l2.assign( l.begin(), l.end() );
		for ( auto i = l2.begin(), j = l.begin(); i != l2.end(), j != l.end(); ++i, ++j )
			assert( (*i) == (*j) );

		// Testing assign() with initializer_list
		l2.assign( { 10, 20, 30 } );
		int c(10);
		for (auto i = l2.begin(); i != l2.end(); ++i, c += 10) assert( (*i) == c );

		// Testing insert() with value
		l2.insert( l2.begin(), 5 );
		assert( l2.front() == 5 );
		l2.insert( l2.end(), 35 );
		assert( l2.back() == 35 );

		// Testing insert() with initializer list
		auto add = l2.begin(); add++; add++; add++;
		l2.insert( add, { 1, 2, 89, 3 }  );

		// These are the elements that should be stored on l2.
		std::initializer_list<int> check = { 5, 10, 20, 1, 2, 89, 3, 30, 35 };
		auto j = check.begin();

		// Testing if the elements are really stored here
		for( auto i = l2.cbegin(); i != l2.cend(); ++i, ++j ) assert( (*i) == (*j) );

		// Testing find()
		auto f = l2.find(89);
		assert( *f == 89 );
		f = l2.find(1200);
		assert( f == l2.end() );

		// Testing erase()
		l2.erase( l2.begin() );
		assert( l2.size() == 8 );
		assert( l2.front() == 10 );
		l2.erase( --l2.end() );
		assert( l2.size() == 7 );
		assert( l2.back() == 30 );

		// Testing erase() with range
		ls::list<int>::iterator er = l2.begin(); er++; er++; er++;
		l2.erase( l2.begin(), er );

		check = { 2, 89, 3, 30 };
		j = check.begin();

		for(auto i = l2.begin(); i != l2.end(); ++i, ++j) assert( (*i) == (*j) );
	}

	cout << endl << "If you are seeing this message, my ls::list passed all the tests." << endl << endl;
}