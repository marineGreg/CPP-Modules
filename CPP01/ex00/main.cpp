
#include "Zombie.hpp"

int	main() {

	Zombie stackZombie("StackZombie");
    stackZombie.announce();
	
	randomChump("RandomStackZombie");
	
	Zombie* heapZombie = newZombie("HeapZombie");
	
	heapZombie->announce();

	delete heapZombie;
	
	return 0;
}
