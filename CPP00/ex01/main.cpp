
#include "PhoneBook.hpp"

# define PB_LINE " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
# define PB_TITLE "/             My Awesome PhoneBook            /\n"

int main()
{
    PhoneBook       phoneBook;
    std::string     command;
    
	std::cout << PB_LINE << PB_TITLE << PB_LINE;
    while (true)
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, command))
        {
            std::cout << std::endl;
            break;
        }
        
        if (command == "ADD")
            phoneBook.addContact();
        else if (command == "SEARCH")
            phoneBook.searchContact();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Invalid command !" << std::endl;
    }
    
    return 0;
}
