/**
 * @file    vector.cpp
 * @brief   Testing functions implemented in vector.h
 * @author  Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @date    21/10/2017
 */

#include "vector.h"

int main(){
	
	std::cout << std::endl;
	{
		std::cout << "Test - Constructor | Push_Back() | Push_Front() " << std::endl << std::endl;
		sc::vector<char> a;
		std::cout << "Pushing back to vector char a, e, i, o, u." << std::endl;
		a.push_back('a'); a.push_back('e'); a.push_back('i'); a.push_back('o'); a.push_back('u');
		
		std::cout << ">>> Vector A: " << std::endl;
		std::cout << a << std::endl;
		
		std::cout << "Now, pushing front value B" << std::endl;
		a.push_front('B');
		
		std::cout << ">>> Vector A: " << std::endl;
		std::cout << a << std::endl;		
	}
	
	std::cout << std::endl;
	{
		std::cout << "Testing - Copy Constructors:" << std::endl << std::endl;
		sc::vector<std::string> a;
		
		std::cout << "Pushing back to vector A strings Pen, Apple, Applepen, Penpinapplepen." << std::endl;
		a.push_back("Pen"); a.push_back("Apple"); a.push_back("Applepen"); a.push_back("Penpinapplepen");
		std::cout << ">>> Vector A: " << std::endl;
		std::cout << a << std::endl;
		
		std::cout << "Creating vector B with vector A passed to B's copy constructor." << std::endl;
		sc::vector<std::string> b(a);
		std::cout << ">>> Vector B: " << std::endl;
		std::cout << b << std::endl;

		std::cout << "Creating vector C with vector A passed to C's assignment operator." << std::endl;
		sc::vector<std::string> c = a;
		std::cout << ">>> Vector C: " << std::endl;
		std::cout << c << std::endl;

		std::cout << "Creating vector D passing range [ C.begin(), C.end() ) to D's constructor." << std::endl;
		sc::vector<std::string> d( c.begin() , c.end() );
		std::cout << ">>> Vector D: ";
		std::cout << d << std::endl;
	}

	std::cout << std::endl;
	{
		std::cout << "Testing - Pop_Front() | Pop_Back() | Front() | Back():" << std::endl << std::endl;
		std::cout << "Creating same vector A from last topic." << std::endl;		
		sc::vector<int> a;
		for(auto i(0); i < 50; ++i)	a.push_back(i * 3);

		std::cout << ">>> Vector A: " << std::endl;
		std::cout << a << std::endl;

		std::cout << "Applying pop_back on A: " << std::endl;
		a.pop_back();
		std::cout << a << std::endl;

		std::cout << "Applying pop_front on A: " << std::endl;
		a.pop_front();
		std::cout << a << std::endl;

		std::cout << ">>> Front element of A: " << a.front() << std::endl;
		std::cout << ">>> Back element of A: " << a.back() << std::endl;
	}

	std::cout << std::endl;
	{
		std::cout << "Testing - Clear():" << std::endl << std::endl;
		std::cout << "Pushing back to vector A each element in [0, ..., 50) multiplied by 4." << std::endl;
		sc::vector<int> a;
		for(auto i(0); i < 50; ++i) a.push_back(i * 4);
		
		std::cout << ">>> Vector A: " << std::endl;
		std::cout << a << std::endl;

		std::cout << "Applying clear() on vector A: " << std::endl;
		a.clear();
		std::cout << a << std::endl;		
	}

	std::cout << std::endl;
	{
		std::cout << "Testing - Assign():" << std::endl << std::endl;
		sc::vector<std::string> a;
		
		std::cout << "Pushing back to vector A strings SYMPATHY, FOR, THE:" << std::endl;
		a.push_back("SYMPATHY"); a.push_back("FOR"); a.push_back("THE");

		std::cout << ">>> Vector A: " << std::endl;
		std::cout << a << std::endl;

		std::cout << "Assigning a list of strings {8, 9, 10} to vector A. " << std::endl;
		a.assign( {"8","9","10"} );

		std::cout << ">>> Vector A after assign(): " << std::endl;
		std::cout << a << std::endl;;
	}

	std::cout << std::endl;
	{
		std::cout << "Testing Operators '==' and '!='" << std::endl << std::endl;
		std::cout << "Creating two vectors: A and B with equal values: " << std::endl;
		
		sc::vector<int> a;
		for(auto i(0); i < 10; ++i)	a.push_back(i);
		sc::vector<int> b(a);

		std::cout << ">>> Vector A: " << std::endl;
		std::cout << a << std::endl;

		std::cout << ">>> Vector B: " << std::endl;
		std::cout << b << std::endl;

		std::cout << "Comparing if A equals B with operator ==" << std::endl;

		a == b ? std::cout << ">>> Equal vectors!" : std::cout << ">>> Different vectors!";

		std::cout << std::endl << std::endl << "Now, popping back A's last element and comparing again: " << std::endl;
		a.pop_back();
		a == b ? std::cout << ">>> Equal vectors!" : std::cout << ">>> Different vectors!";

		std::cout << std::endl;
	}
	
	std::cout << std::endl;
	{
		std::cout << "Testing - Erase():" << std::endl << std::endl;
		std::cout << "Pushing back to vector A each element in [0, ..., 50) multiplied by 6." << std::endl;
		sc::vector<float> a;
		for(auto i(0); i < 50; ++i)	a.push_back(i * 6.0);

		std::cout << ">>> Vector A: ";
		std::cout << a << std::endl;

		std::cout << "Applying erase() on first 4 elements of vector A. " << std::endl;
		auto last = a.begin(); last++; last++; last++; last++;
		a.erase( a.begin(), last );

		std::cout << ">>> Vector A after erase(): " << std::endl;
		std::cout << a << std::endl;;
	}

	std::cout << std::endl;
	{
		std::cout << "Testing - Insert():" << std::endl << std::endl;
		std::cout << "Pushing back to vector A each element in [0, ..., 20) multiplied by 0.5" << std::endl;
		sc::vector<double> a;
		for(auto i(0); i < 20; ++i)	a.push_back(i * 0.5);
		
		std::cout << ">>> Vector A: " << std::endl;
		std::cout << a << std::endl;

		std::cout << "Inserting range [2, ..., 15) on vector A at position a.begin()" << std::endl;
		a.insert( a.begin(), 2, 15 );
		
		std::cout << ">>> Vector A after insert(): " << std::endl;
		std::cout << a << std::endl;

		std::cout << "Creating a vector B with vector A passed to B's copy constructor: " << std::endl;
		sc::vector<double> b (a);
		std::cout << ">>> Vector B: " << std::endl;
		std::cout << b << std::endl;

		std::cout << "Inserting a list of elements {26, 89, 48} on vector B at position b.end():" << std::endl;
		b.insert( b.end(), {26, 89, 48} );
		
		std::cout << ">>> Vector B after insert(): " << std::endl;
		std::cout << b << std::endl;
	}
	
	std::cout << std::endl;
	{
		std::cout << "Testing - Swap():" << std::endl << std::endl;
		std::cout << "Pushing back to vector A chars l, u, c, a, s:" << std::endl;
		sc::vector<char> a;
		a.push_back('l'); a.push_back('u'); a.push_back('c'); a.push_back('a'); a.push_back('s');

		std::cout << ">>> Vector A: " << std::endl;
		std::cout << a << std::endl;

		std::cout << "Pushing back to vector B chars g, o, m, e, s:" << std::endl;
		sc::vector<char> b;
		b.push_back('g'); b.push_back('o'); b.push_back('m'); b.push_back('e'); b.push_back('s');

		std::cout << ">>> Vector B: " << std::endl;
		std::cout << b << std::endl;

		std::cout << "Swaping elements of vector A with vector B." << std::endl;
		swap(a, b);

		std::cout << ">>> Vector A after swap():" << std::endl;
		std::cout << a << std::endl;

		std::cout << ">>> Vector B after swap():" << std::endl;
		std::cout << b << std::endl;
	}
}