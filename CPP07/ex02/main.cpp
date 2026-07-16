#include "Array.hpp"
#include <iostream>
#include <string>

int main()
{
	// --- 1. Constructeur par défaut : tableau vide ---
	std::cout << "===== Test 1: constructeur par défaut =====" << std::endl;
	Array<int> empty;
	std::cout << "size = " << empty.size() << std::endl; // doit être 0

	// --- 2. Constructeur avec n : initialisation par défaut ---
	std::cout << "\n===== Test 2: constructeur avec n =====" << std::endl;
	Array<int> nums(5);
	std::cout << "size = " << nums.size() << std::endl; // doit être 5
	for (unsigned int i = 0; i < nums.size(); i++)
		std::cout << "nums[" << i << "] = " << nums[i] << std::endl; // doit afficher des 0

	// --- 3. Remplissage puis test de copie profonde ---
	std::cout << "\n===== Test 3: copie profonde (constructeur de copie) =====" << std::endl;
	for (unsigned int i = 0; i < nums.size(); i++)
		nums[i] = i * 10;

	Array<int> copy(nums); // constructeur de copie
	nums[0] = 999; // on modifie l'original

	std::cout << "original[0] = " << nums[0] << std::endl; // 999
	std::cout << "copy[0]     = " << copy[0] << std::endl; // 0 (pas affecté !)

	// --- 4. Test de l'opérateur d'affectation ---
	std::cout << "\n===== Test 4: opérateur = =====" << std::endl;
	Array<int> assigned;
	assigned = nums;
	nums[1] = 777;

	std::cout << "nums[1]     = " << nums[1] << std::endl;     // 777
	std::cout << "assigned[1] = " << assigned[1] << std::endl; // 10 (pas affecté)

	// --- 5. Exception hors limites ---
	std::cout << "\n===== Test 5: accès hors limites =====" << std::endl;
	try
	{
		std::cout << nums[100] << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cout << "Exception attrapée: " << e.what() << std::endl;
	}

	// --- 6. Exception sur tableau vide ---
	std::cout << "\n===== Test 6: accès sur tableau vide =====" << std::endl;
	try
	{
		std::cout << empty[0] << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cout << "Exception attrapée: " << e.what() << std::endl;
	}

	// --- 7. Version const de operator[] ---
	std::cout << "\n===== Test 7: accès en lecture via référence const =====" << std::endl;
	const Array<int> constNums(nums);
	std::cout << "constNums[2] = " << constNums[2] << std::endl;
	// constNums[2] = 5; // ne doit PAS compiler !!!

	// --- 8. Template avec un autre type que int ---
	std::cout << "\n===== Test 8: Array<std::string> =====" << std::endl;
	Array<std::string> words(3);
	words[0] = "hello";
	words[1] = "world";
	words[2] = "42";
	for (unsigned int i = 0; i < words.size(); i++)
		std::cout << words[i] << " ";
	std::cout << std::endl;

	return 0;
}
