#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <limits>
#include <iterator>
#include <iostream>

template <typename T>
class Vector {
private :
    T* dataVar;
    size_t capacityVar;
    size_t sizeVar;

public:

//! Member types
    using value_type             = T;
    using size_type              = size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = T*;
    using const_pointer          = const T*;
    using iterator               = T*;
    using const_iterator         = const T*;


//!constuctors
    // Constructors
    Vector(); // Default constructor
    explicit Vector(size_t count); // Fill constructor
    Vector(size_t count, const T& value); // Fill with value
    Vector(std::initializer_list<T> init); // Initializer list constructor
    Vector(const Vector& other); // Copy constructor
    Vector(Vector&& other) noexcept; // Move constructor

    // Destructor
    ~Vector();

    // Assignment operators
    Vector& operator=(const Vector& other); // Copy assignment
    Vector& operator=(Vector&& other) noexcept; // Move assignment
    Vector& operator=(std::initializer_list<T> init); // Initializer list assignment

//!member functions

//!capacity
    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;

    void reserve(size_t new_cap);
    void resize(size_t new_size);

//!modifiers
    void clear();
    
    iterator insert(iterator pos, const T& value);
    iterator insert(iterator pos, size_t count, const T& value);
    template <typename InputIt>
    iterator insert(iterator pos, InputIt first, InputIt last);
    iterator insert(iterator pos, T&& value);
    iterator insert(iterator pos, std::initializer_list<T> ilist);

    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(iterator first, iterator last);
    iterator erase(const_iterator first, const_iterator last);
    
    void push_back(const T& value);
    void pop_back();

//!element access
    T& at(size_t index);
    const T& at(size_t index) const;

    T& front();
    T& back();
    const T& front() const;
    const T& back() const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T* data() noexcept;
    const T* data() const noexcept;


//!iterators
    T* begin() noexcept;
    T* end() noexcept;
    const T* begin() const noexcept;
    const T* end() const noexcept;
};

//!non-member functions
// Non-member function declarations:
template <typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);

template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs);

template <typename T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs);

template <typename T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs);

template <typename T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs);

template <typename T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs);

template <typename T>
void swap(Vector<T>& a, Vector<T>& b) noexcept;

#include "Vector.tpp"

#endif