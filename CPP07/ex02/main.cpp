#include "Array.hpp"
#include <iostream>
#include <string>

int main()
{
	std::cout << "===== Test 1: constructeur par défaut =====" << std::endl;
	Array<int> empty;
	std::cout << "size = " << empty.size() << std::endl; // doit être 0


	std::cout << "\n===== Test 2: constructeur avec n =====" << std::endl;
	Array<int> nums(5);
	std::cout << "size = " << nums.size() << std::endl; // doit être 5
	std::cout << "nums = " << nums << std::endl; // doit afficher [0, 0, 0, 0, 0]


	std::cout << "\n===== Test 3: copie profonde (constructeur de copie) =====" << std::endl;
	for (unsigned int i = 0; i < nums.size(); i++)
		nums[i] = i * 10;
	std::cout << "nums = " << nums << std::endl; // doit afficher [0, 10, 20, 30, 40]

	Array<int> copy(nums); // constructeur de copie
	nums[0] = 999; // on modifie l'original
	
	std::cout << "nums = " << nums << std::endl; // doit afficher [999, 10, 20, 30, 40]
	std::cout << "copy = " << copy << std::endl; // doit afficher [0, 10, 20, 30, 40]


	std::cout << "\n===== Test 4: opérateur = =====" << std::endl;
	Array<int> assigned;
	assigned = nums; // opérateur d'affectation
	nums[1] = 777; // on modifie l'original

	std::cout << "nums     = " << nums << std::endl;     // doit afficher [999, 777, 20, 30, 40]
	std::cout << "assigned = " << assigned << std::endl; // doit afficher [999, 10, 20, 30, 40]


	std::cout << "\n===== Test 5: accès hors limites =====" << std::endl;
	try
	{
		std::cout << nums[100] << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== Test 6: accès sur tableau vide =====" << std::endl;
	try
	{
		std::cout << empty[0] << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}


	std::cout << "\n===== Test 7: accès en lecture via référence const =====" << std::endl;
	const Array<int> constNums(nums);
	std::cout << "constNums[2] = " << constNums[2] << std::endl;
	// constNums[2] = 5; // ne doit PAS compiler !!!

	
	std::cout << "\n===== Test 8: Array<std::string> =====" << std::endl;
	Array<std::string> words(3);
	words[0] = "hello";
	words[1] = "world";
	words[2] = "42";
	std::cout << words << std::endl;
	return 0;
}
