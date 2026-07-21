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
        
        unsigned int size() const;

        class OutOfBoundsException : public std::exception {
    		public:
        		virtual const char* what() const throw() {
					return "Index out of bounds";
				}
		};
};

template <typename T>
std::ostream& operator<<(std::ostream & out, const Array<T> & array);

#include "Array.tpp"

#endif