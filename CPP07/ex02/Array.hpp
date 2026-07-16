#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <exception>

template <typename T>
class Array
{
    private:
        T*				_data;
        unsigned int	_size;

    public:
        Array();
        Array(unsigned int n);
        Array(const Array & src);
        Array& operator=(const Array & other);
        ~Array();


        T& operator[](unsigned int i);
        const T& operator[](unsigned int i) const;
        
		// --- Fonction membre ---
        unsigned int size() const;

        // --- Exception personnalisée ---
        class OutOfBoundsException : public std::exception {
            public:
                virtual const char* what() const throw() {
					return "Index out of bounds";
				}
        };
};

#include "Array.tpp"

#endif