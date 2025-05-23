#include "Vector.h"

//!constuctors
// Default constructor
template <typename T>
Vector<T>::Vector() : dataVar(nullptr), capacityVar(0), sizeVar(0) {}

// Fill constructor
template <typename T>
Vector<T>::Vector(size_t count)
    : dataVar(count ? new T[count] : nullptr), capacityVar(count), sizeVar(count) {
    for (size_t i = 0; i < count; ++i)
        dataVar[i] = T();
}

// Fill with value constructor
template <typename T>
Vector<T>::Vector(size_t count, const T& value)
    : dataVar(count ? new T[count] : nullptr), capacityVar(count), sizeVar(count) {
    for (size_t i = 0; i < count; ++i)
        dataVar[i] = value;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init)
    : dataVar(new T[init.size()]), capacityVar(init.size()), sizeVar(init.size()) {
    std::copy(init.begin(), init.end(), dataVar);
}

// Destructor
template <typename T>
Vector<T>::~Vector() {
    for (size_t i = 0; i < sizeVar; ++i)
        dataVar[i].~T();
    delete[] dataVar;
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& other)
    : dataVar(nullptr), capacityVar(other.capacityVar), sizeVar(other.sizeVar) {
    if (capacityVar > 0) {
        if (other.dataVar == nullptr && sizeVar > 0)
            throw std::logic_error("Source vector data is null with nonzero size");
        dataVar = new T[capacityVar];
        std::copy(other.dataVar, other.dataVar + sizeVar, dataVar);
    }
}

// Copy assignment
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] dataVar;
        capacityVar = other.capacityVar;
        sizeVar = other.sizeVar;
        dataVar = (capacityVar > 0) ? new T[capacityVar] : nullptr;
        if (capacityVar > 0 && (other.dataVar == nullptr && sizeVar > 0))
            throw std::logic_error("Source vector data is null with nonzero size");
        std::copy(other.dataVar, other.dataVar + sizeVar, dataVar);
    }
    return *this;
}

// Move constructor
template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : dataVar(other.dataVar), capacityVar(other.capacityVar), sizeVar(other.sizeVar) {
    other.dataVar = nullptr;
    other.capacityVar = 0;
    other.sizeVar = 0;
}

template <typename T>
template <std::input_iterator InputIt>
Vector<T>::Vector(InputIt first, InputIt last)
    : dataVar(nullptr), capacityVar(0), sizeVar(0)
{
    size_t count = std::distance(first, last);
    if (count > 0) {
        dataVar = new T[count];
        capacityVar = sizeVar = count;
        size_t i = 0;
        for (auto it = first; it != last; ++it, ++i)
            dataVar[i] = *it;
    }
}

// Move assignment
template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] dataVar;
        dataVar = other.dataVar;
        capacityVar = other.capacityVar;
        sizeVar = other.sizeVar;
        other.dataVar = nullptr;
        other.capacityVar = 0;
        other.sizeVar = 0;
    }
    return *this;
}

// Initializer list assignment
template <typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> init) {
    delete[] dataVar;
    capacityVar = init.size();
    sizeVar = init.size();
    dataVar = (capacityVar > 0) ? new T[capacityVar] : nullptr;
    std::copy(init.begin(), init.end(), dataVar);
    return *this;
}

//!member functions
// 1. Assign count copies of value
template <typename T>
void Vector<T>::assign(size_t count, const T& value) {
    if (count > capacityVar)
        reserve(count);
    for (size_t i = 0; i < count; ++i)
        dataVar[i] = value;
    sizeVar = count;
}

// 2. Assign from range [first, last)
template <typename T>
template <std::input_iterator InputIt>
void Vector<T>::assign(InputIt first, InputIt last) {
    size_t count = std::distance(first, last);
    if (count > capacityVar)
        reserve(count);
    size_t i = 0;
    for (auto it = first; it != last; ++it, ++i)
        dataVar[i] = *it;
    sizeVar = count;
}

// 3. Assign from initializer_list
template <typename T>
void Vector<T>::assign(std::initializer_list<T> ilist) {
    assign(ilist.begin(), ilist.end());
}
//!capacity
template <typename T>
bool Vector<T>::empty() const noexcept {
    return sizeVar == 0;
}

// Size accessor
template <typename T>
size_t Vector<T>::size() const noexcept {
    return sizeVar;
}

template <typename T>
size_t Vector<T>::max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(T);
}

// Capacity accessor
template <typename T>
size_t Vector<T>::capacity() const noexcept {
    return capacityVar;
}

template <typename T>
void Vector<T>::reserve(size_t new_cap) {
    if (new_cap > capacityVar) {
        T* newData = new T[new_cap];
        for (size_t i = 0; i < sizeVar; ++i)
            newData[i] = dataVar[i];
        delete[] dataVar;
        dataVar = newData;
        capacityVar = new_cap;
    }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (capacityVar > sizeVar) {
        T* newData = (sizeVar > 0) ? new T[sizeVar] : nullptr;
        for (size_t i = 0; i < sizeVar; ++i)
            newData[i] = dataVar[i];
        delete[] dataVar;
        dataVar = newData;
        capacityVar = sizeVar;
    }
}

//!modifiers
template <typename T>
void Vector<T>::clear() {
    sizeVar = 0;
}

// 1. Insert single element at position
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T& value) {
    size_t idx = pos - dataVar;
    if (idx > sizeVar)
        throw std::out_of_range("Insert position out of range");

    if (sizeVar == capacityVar)
        reserve(capacityVar == 0 ? 1 : capacityVar * 2);

    for (size_t i = sizeVar; i > idx; --i)
        dataVar[i] = dataVar[i - 1];

    dataVar[idx] = value;
    ++sizeVar;
    return dataVar + idx;
}

// 2. Insert count copies of value at position
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, size_t count, const T& value) {
    size_t idx = pos - dataVar;
    if (idx > sizeVar)
        throw std::out_of_range("Insert position out of range");
    if (count == 0)
        return dataVar + idx;

    if (sizeVar + count > capacityVar)
        reserve(std::max(capacityVar * 2, sizeVar + count));

    for (size_t i = sizeVar + count - 1; i >= idx + count; --i)
        dataVar[i] = dataVar[i - count];

    for (size_t i = 0; i < count; ++i)
        dataVar[idx + i] = value;

    sizeVar += count;
    return dataVar + idx;
}

// 3. Insert range [first, last) at position
template <typename T>
template <std::input_iterator InputIt>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, InputIt first, InputIt last) {
    size_t idx = pos - dataVar;
    if (idx > sizeVar)
        throw std::out_of_range("Insert position out of range");

    size_t count = std::distance(first, last);
    if (count == 0)
        return dataVar + idx;

    if (sizeVar + count > capacityVar)
        reserve(std::max(capacityVar * 2, sizeVar + count));

    for (size_t i = sizeVar + count - 1; i >= idx + count; --i)
        dataVar[i] = dataVar[i - count];

    size_t i = 0;
    for (auto it = first; it != last; ++it, ++i)
        dataVar[idx + i] = *it;

    sizeVar += count;
    return dataVar + idx;
}

// 4. Insert element by moving at position
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, T&& value) {
    size_t idx = pos - dataVar;
    if (idx > sizeVar)
        throw std::out_of_range("Insert position out of range");

    if (sizeVar == capacityVar)
        reserve(capacityVar == 0 ? 1 : capacityVar * 2);

    for (size_t i = sizeVar; i > idx; --i)
        dataVar[i] = std::move(dataVar[i - 1]);

    dataVar[idx] = std::move(value);
    ++sizeVar;
    return dataVar + idx;
}

// 5. Insert initializer_list at position
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, ilist.begin(), ilist.end());
}

//1. Erase a single element at position
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator pos) {
    size_t idx = pos - dataVar;
    if (idx >= sizeVar)
        throw std::out_of_range("Erase position out of range");

    for (size_t i = idx; i + 1 < sizeVar; ++i)
        dataVar[i] = std::move(dataVar[i + 1]);

    --sizeVar;
    return dataVar + idx;
}

//2. Erase a single element at position (const_iterator version)
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator pos) {
    return erase(dataVar + (pos - dataVar));
}

//3. Erase a range [first, last)
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last) {
    size_t idx_first = first - dataVar;
    size_t idx_last = last - dataVar;
    if (idx_first > sizeVar || idx_last > sizeVar || idx_first > idx_last)
        throw std::out_of_range("Erase range out of range");

    size_t count = idx_last - idx_first;
    for (size_t i = idx_first; i + count < sizeVar; ++i)
        dataVar[i] = std::move(dataVar[i + count]);

    sizeVar -= count;
    return dataVar + idx_first;
}

//4. Erase a range [first, last) (const_iterator version)
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator first, const_iterator last) {
    return erase(dataVar + (first - dataVar), dataVar + (last - dataVar));
}

// Push back
template <typename T>
void Vector<T>::push_back(const T& value) {
    if (sizeVar > capacityVar)
        throw std::logic_error("Vector size exceeds capacity");
    if (sizeVar == capacityVar) {
        size_t newCapacity = (capacityVar == 0) ? 1 : capacityVar * 2;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < sizeVar; ++i)
            newData[i] = dataVar[i];
        delete[] dataVar;
        dataVar = newData;
        capacityVar = newCapacity;
    }
    dataVar[sizeVar++] = value;
}

template <typename T>
void Vector<T>::push_back(T&& value) {
    if (sizeVar == capacityVar)
        reserve(capacityVar == 0 ? 1 : capacityVar * 2);
    dataVar[sizeVar++] = std::move(value);
}

// Pop back
template <typename T>
void Vector<T>::pop_back() {
    if (sizeVar == 0)
        throw std::out_of_range("Vector is empty");
    --sizeVar;
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::emplace(iterator pos, Args&&... args) {
    size_t idx = pos - dataVar;
    if (idx > sizeVar)
        throw std::out_of_range("Emplace position out of range");

    if (sizeVar == capacityVar)
        reserve(capacityVar == 0 ? 1 : capacityVar * 2);

    for (size_t i = sizeVar; i > idx; --i)
        dataVar[i] = std::move(dataVar[i - 1]);

    dataVar[idx] = T(std::forward<Args>(args)...);
    ++sizeVar;
    return dataVar + idx;
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args&&... args) {
    if (sizeVar == capacityVar)
        reserve(capacityVar == 0 ? 1 : capacityVar * 2);
    dataVar[sizeVar++] = T(std::forward<Args>(args)...);
}

template <typename T>
void Vector<T>::resize(size_t new_size) {
    if (new_size > capacityVar)
        reserve(new_size);
    if (new_size > sizeVar) {
        for (size_t i = sizeVar; i < new_size; ++i)
            dataVar[i] = T();
    }
    sizeVar = new_size;
}

template <typename T>
void Vector<T>::resize(size_t new_size, const T& value) {
    if (new_size > capacityVar)
        reserve(new_size);
    if (new_size > sizeVar) {
        for (size_t i = sizeVar; i < new_size; ++i)
            dataVar[i] = value;
    }
    sizeVar = new_size;
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept {
    using std::swap;
    swap(dataVar, other.dataVar);
    swap(capacityVar, other.capacityVar);
    swap(sizeVar, other.sizeVar);
}

//!element access
template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= sizeVar)
        throw std::out_of_range("Index out of range");
    return dataVar[index];
}

template <typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= sizeVar)
        throw std::out_of_range("Index out of range");
    return dataVar[index];
}

template <typename T>
T& Vector<T>::front() {
    if (sizeVar == 0) throw std::out_of_range("Vector is empty");
    return dataVar[0];
}
template <typename T>
T& Vector<T>::back() {
    if (sizeVar == 0) throw std::out_of_range("Vector is empty");
    return dataVar[sizeVar - 1];
}
template <typename T>
const T& Vector<T>::front() const {
    if (sizeVar == 0) throw std::out_of_range("Vector is empty");
    return dataVar[0];
}
template <typename T>
const T& Vector<T>::back() const {
    if (sizeVar == 0) throw std::out_of_range("Vector is empty");
    return dataVar[sizeVar - 1];
}
// Element access (non-const)
template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= sizeVar)
        throw std::out_of_range("Index out of range");
    if (dataVar == nullptr)
        throw std::logic_error("Vector data is null");
    return dataVar[index];
}

// Element access (const)
template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= sizeVar)
        throw std::out_of_range("Index out of range");
    if (dataVar == nullptr)
        throw std::logic_error("Vector data is null");
    return dataVar[index];
}

template <typename T>
T* Vector<T>::data() noexcept {
    return dataVar;
}

template <typename T>
const T* Vector<T>::data() const noexcept {
    return dataVar;
}

//!iterators
// begin
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
    return dataVar;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept {
    return dataVar;
}

// cbegin
template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept {
    return dataVar;
}

// end
template <typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
    return dataVar + sizeVar;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept {
    return dataVar + sizeVar;
}

// cend
template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept {
    return dataVar + sizeVar;
}

// rbegin
template <typename T>
std::reverse_iterator<typename Vector<T>::iterator> Vector<T>::rbegin() noexcept {
    return std::reverse_iterator<iterator>(end());
}

template <typename T>
std::reverse_iterator<typename Vector<T>::const_iterator> Vector<T>::rbegin() const noexcept {
    return std::reverse_iterator<const_iterator>(end());
}

// crbegin
template <typename T>
std::reverse_iterator<typename Vector<T>::const_iterator> Vector<T>::crbegin() const noexcept {
    return std::reverse_iterator<const_iterator>(cend());
}

// rend
template <typename T>
std::reverse_iterator<typename Vector<T>::iterator> Vector<T>::rend() noexcept {
    return std::reverse_iterator<iterator>(begin());
}

template <typename T>
std::reverse_iterator<typename Vector<T>::const_iterator> Vector<T>::rend() const noexcept {
    return std::reverse_iterator<const_iterator>(begin());
}

// crend
template <typename T>
std::reverse_iterator<typename Vector<T>::const_iterator> Vector<T>::crend() const noexcept {
    return std::reverse_iterator<const_iterator>(cbegin());
}


//!non-member functions
// Equality
template <typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (size_t i = 0; i < lhs.size(); ++i)
        if (!(lhs[i] == rhs[i])) return false;
    return true;
}

template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}

// Lexicographical less-than
template <typename T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
    size_t minSize = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
    for (size_t i = 0; i < minSize; ++i) {
        if (lhs[i] < rhs[i]) return true;
        if (rhs[i] < lhs[i]) return false;
    }
    return lhs.size() < rhs.size();
}

template <typename T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(rhs < lhs);
}

template <typename T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
    return rhs < lhs;
}

template <typename T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs < rhs);
}

// Swap
template <typename T>
void swap(Vector<T>& a, Vector<T>& b) noexcept {
    a.swap(b);
}