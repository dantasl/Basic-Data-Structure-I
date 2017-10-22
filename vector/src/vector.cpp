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
		std::cout << "\xe2\x99\xa5\n";
		std::cout << "Testing - Constructors, Push_Back(), Push_Front():\n";
		sc::vector<int> a;

		for(auto i(0); i < 10; i++){
			a.push_back((i+1)*1);
		}
		a.push_front(0);

		std::cout << ">>> A: ";
		std::cout << a << std::endl;;
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Copy Constructors:\n";
		sc::vector<int> a;
		for(auto i(0); i < 10; i++){
			a.push_back((i+1)*2);
		}
		std::cout << ">>> A: ";
		std::cout << a << std::endl;
		std::cout << a << std::endl;;

		// Copying with vector(vector)
		sc::vector<int> b(a);
		std::cout << ">>> B: ";
		std::cout << b << std::endl;;

		// Copying with vector = vector
		sc::vector<int> c = a;
		std::cout << ">>> C: ";
		std::cout << c << std::endl;;

		// Copying with range (10, 43)
		sc::vector<int> d(10, 43);
		std::cout << ">>> D: ";
		std::cout << d << std::endl;;

		// Copying with range of D
		sc::vector<int> e(d.begin(), d.end());
		std::cout << ">>> E: ";
		std::cout << e << std::endl;; 
	}
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
	std::cout << std::endl;
}