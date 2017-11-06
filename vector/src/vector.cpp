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
		sc::vector<int> a;
		std::cout << "Pushing back to vector [10, ..., 50)" << std::endl;
		for(auto i(10); i < 50; ++i)
			a.push_back(i);
		
		std::cout << ">>> A: " << std::endl;
		std::cout << a << std::endl;
		
		std::cout << "Now, pushing front value 5" << std::endl;
		a.push_front(5);
		
		std::cout << ">>> A: " << std::endl;
		std::cout << a << std::endl;		
	}
	
	std::cout << std::endl;
	{
		std::cout << "Testing - Copy Constructors:" << std::endl << std::endl;
		sc::vector<int> a;
		
		std::cout << "Pushing back to vector A each element in [0, ..., 50) multiplied by 3." << std::endl;
		for(auto i(0); i < 50; i++)
			a.push_back(i * 3);
		std::cout << ">>> Vector A: " << std::endl;
		std::cout << a << std::endl;
		
		std::cout << "Creating vector B with vector A passed to B's copy constructor." << std::endl;
		sc::vector<int> b(a);
		std::cout << ">>> Vector B: " << std::endl;
		std::cout << b << std::endl;

		std::cout << "Creating vector C with vector A passed to C's assignment operator." << std::endl;
		sc::vector<int> c = a;
		std::cout << ">>> Vector C: " << std::endl;
		std::cout << c << std::endl;

		std::cout << "Creating vector D passing range [ C.begin(), C.end() ) to D's constructor." << std::endl;
		sc::vector<int> d( c.begin() , c.end() );
		std::cout << ">>> Vector D: ";
		std::cout << d << std::endl;
	}

	/*
	std::cout << std::endl;
	{
		std::cout << "Testing - Pop_Front(), Pop_Back(), Front(), Back():\n";
		
		sc::vector<int> a;
		for(auto i(0); i < 10; i++){
			a.push_back((i+1)*4);
		}

		std::cout << ">>> A: ";
		std::cout << a << std::endl;;

		a.pop_front();
		a.pop_back();

		std::cout << ">>> A*: ";
		std::cout << a << std::endl;;
		std::cout << ">>> Front: " << a.front() << "\n";
		std::cout << ">>> Back: " << a.back() << "\n";
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Clear():\n";
		sc::vector<int> a;
		for(auto i(0); i < 10; i++){
			a.push_back((i+1)*5);
		}
		a.clear();

		std::cout << ">>> A: ";
		std::cout << a << std::endl;;
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Assign():\n";
		sc::vector<int> a;
		for(auto i(0); i < 10; i++){
			a.push_back((i+1)*6);
		}
		a.assign({8,9,10});

		std::cout << ">>> A: ";
		std::cout << a << std::endl;;
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Operators == and !=:\n";
		sc::vector<int> a, b;
		for(auto i (0); i < 10; i++){
			a.push_back(i+1);
		}
		for(auto i (0); i < 10; i++){
			b.push_back(i+1);
		}
		if(a==b){
			std::cout << ">>> Equal\n";
		}else{
			std::cout << ">>> Different\n";
		}
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Erase():\n";
		sc::vector<int> a;
		for(auto i (0); i < 10; i++){
			a.push_back(i+1);

		}
		auto x = a.begin();
		auto y = a.begin();
		y++;y++;y++;y++;

		std::cout << "A: ";
		std::cout << a << std::endl;;

		a.erase(x, y);

		std::cout << "A*: ";
		std::cout << a << std::endl;;
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Insert():\n";
		sc::vector<int> a(1, 10);
		std::cout << "A: ";
		std::cout << a << std::endl;;

		// Insert range
		a.insert(a.begin(), 2, 15);
		std::cout << "A*: ";
		std::cout << a << std::endl;;
		
		sc::vector<int> b(1, 5);
		std::cout << "B: ";
		std::cout << b << std::endl;;

		// Insert list
		b.insert(b.end(), {5, 6, 7});
		std::cout << "B*: ";
		std::cout << b << std::endl;;

		sc::vector<int> c(1, 6);
		std::cout << "C: ";
		std::cout << c << std::endl;;

		// Insert element
		c.insert(c.begin(), 0);
		std::cout << "C*: ";
		std::cout << c << std::endl;;

	}
	std::cout << std::endl;*/
}