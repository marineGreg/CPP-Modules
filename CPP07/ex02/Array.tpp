#ifndef ARRAY_TPP
#define ARRAY_TPP


template <typename T>
Array<T>::Array() : _data(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _size(n) {
    // Le sujet précise d'utiliser new[]
    // Les parenthèses () à la fin forcent l'initialisation par défaut (ex: 0 pour les int)
    if (n > 0)
        _data = new T[n]();
    else
        _data = NULL;
}

// --- Constructeur de copie ---
template <typename T>
Array<T>::Array(const Array & src) : _data(NULL), _size(0) {
    // On réutilise l'opérateur d'affectation pour éviter la duplication de code
    *this = src;
}

// --- Opérateur d'affectation ---
template <typename T>
Array<T>& Array<T>::operator=(const Array & other) {
    if (this != &other) {
		T* newData = NULL;
		if (other._size > 0) {
			newData = new T[other._size];
			for (unsigned int i = 0; i < other._size; i++) {
				newData[i] = other._data[i];
			}
		}
		delete[] _data;
		_data = newData;
		_size = other._size;
    }
    return *this;
}

// --- Destructeur ---
template <typename T>
Array<T>::~Array() {
    delete[] _data;
}

// --- Opérateur [] (Version normale) ---
template <typename T>
T& Array<T>::operator[](unsigned int i) {
    if (i >= _size)
        throw OutOfBoundsException();
    return _data[i];
}

// --- Opérateur [] (Version constante) ---
template <typename T>
const T& Array<T>::operator[](unsigned int i) const {
    if (i >= _size)
        throw OutOfBoundsException();
    return _data[i];
}

template <typename T>
unsigned int Array<T>::size() const {
    return _size;
}

template <typename T>
std::ostream& operator<<(std::ostream & os, const Array<T> & array) {
    os << "[";
    for (unsigned int i = 0; i < array.size(); i++) {
        os << array[i];
        if (i < array.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

#endif