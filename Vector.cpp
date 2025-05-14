#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* data;          // Pointer to the dynamically allocated array
    size_t capacity;  // Total capacity of the array
    size_t sizeVar;      // Current number of elements in the array


    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < sizeVar; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:

//!member types
    using value_type = T;                // The type of elements stored in the vector
    using allocator_type = std::allocator<T>;
    using size_type = size_t;            // Type for sizes and indices
    using difference_type = std::ptrdiff_t;
    using reference = T&;                // Reference to an element
    using const_reference = const T&;    // Const reference to an element
    using pointer = T*;                  // Pointer to an element
    using const_pointer = const T*;      // Const pointer to an element

    class Iterator {
    private:
        T* current; // Pointer to the current element
    public:
        // Constructor
        explicit Iterator(T* ptr) : current(ptr) {}

        // Dereference operator
        T& operator*() const { return *current; }

        // Arrow operator
        T* operator->() const { return current; }

        // Pre-increment
        Iterator& operator++() {
            ++current;
            return *this;
        }

        // Post-increment
        Iterator operator++(int) {
            Iterator temp = *this;
            ++current;
            return temp;
        }

        // Equality comparison
        bool operator==(const Iterator& other) const { return current == other.current; }

        // Inequality comparison
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    using iterator = Iterator;
    using const_iterator = const Iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

//!member functions

    // Constructor
    Vector() : data(nullptr), capacity(0), sizeVar(0) {}

    // Destructor
    ~Vector() {
        delete[] data;
    }

    //copy assignment
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
    
        delete[] data;
    
        sizeVar = other.sizeVar;
        capacity = other.capacity;
        data = new T[capacity];
        for (size_t i = 0; i < sizeVar; ++i) {
            data[i] = other.data[i];
        }
    
        return *this;
    }

    // Copy constructor
    Vector(const Vector& other) 
        : data(new T[other.capacity]), capacity(other.capacity), sizeVar(other.sizeVar) {
        // Copy elements from the other vector
        for (size_t i = 0; i < sizeVar; ++i) {
            data[i] = other.data[i];
        }
    }

    //move assignment
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) {
            return *this;
        }
    
        delete[] data;
    
        data = other.data;
        sizeVar = other.sizeVar;
        capacity = other.capacity;
    
        other.data = nullptr;
        other.sizeVar = 0;
        other.capacity = 0;
    
        return *this;
    }

    //innitializer list assignment
    Vector& operator=(std::initializer_list<T> ilist) {
        delete[] data;
    
        sizeVar = ilist.size();
        capacity = sizeVar;
        data = new T[capacity];
    
        size_t i = 0;
        for (const T& value : ilist) {
            data[i++] = value;
        }
    
        return *this;
    }


    //Assign from a Range
    template <typename InputIt>
    void assign(InputIt first, InputIt last) {
        // Calculate the new size
        size_t newSize = std::distance(first, last);

        // Free existing resources if necessary
        delete[] data;

        // Allocate new memory
        data = new T[newSize];
        capacity = newSize;
        sizeVar = newSize;

        // Copy elements from the range
        size_t i = 0;
        for (InputIt it = first; it != last; ++it) {
            data[i++] = *it;
        }
    }


    //Assign with a Specific Value
    void assign(size_t count, const T& value) {
        // Free existing resources if necessary
        delete[] data;
    
        // Allocate new memory
        data = new T[count];
        capacity = count;
        sizeVar = count;
    
        // Fill the vector with the specified value
        for (size_t i = 0; i < count; ++i) {
            data[i] = value;
        }
    }


    //Assign from an initializer_list
    void assign(std::initializer_list<T> ilist) {
        // Free existing resources if necessary
        delete[] data;
    
        // Allocate new memory
        sizeVar = ilist.size();
        capacity = sizeVar;
        data = new T[capacity];
    
        // Copy elements from the initializer list
        size_t i = 0;
        for (const T& value : ilist) {
            data[i++] = value;
        }
    }

    //assign values from a container
    template <typename Range>
    void assign_range(Range&& rg) {
        // Use std::ranges::begin and std::ranges::end to get iterators
        auto first = std::ranges::begin(rg);
        auto last = std::ranges::end(rg);

        // Calculate the new size
        size_t newSize = std::distance(first, last);

        // Free existing resources
        delete[] data;

        // Allocate new memory
        data = new T[newSize];
        capacity = newSize;
        sizeVar = newSize;

        // Copy elements from the range
        size_t i = 0;
        for (auto it = first; it != last; ++it) {
            data[i++] = *it;
        }
    }

    allocator_type get_allocator() const {
        return allocator_type();
    }

//!element access

    T& at(size_type pos) {
        if (pos >= sizeVar) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data[pos];
    }

    const T& at(size_type pos) const {
        if (pos >= sizeVar) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data[pos];
    }

    T& operator[](size_type pos) {
        return data[pos];
    }

    const T& operator[](size_type pos) const {
        return data[pos];
    }

    T& front(){
        return data[0];
    }

    const T& front() const {
        return data[0];
    }

    T& back() {
        return data[sizeVar - 1];
    }

    const T& back() const {
        return data[sizeVar - 1];
    }

    T* data() {
        return this->data;
    }

    const T* data() const {
        return this->data;
    }

//!iterators

    iterator begin() {
        return iterator(data);
    }

    const_iterator begin() const {
        return const_iterator(data);
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(data);
    }


    iterator end() {
        return iterator(data+sizeVar);
    }

    const_iterator end() const {
        return const_iterator(data+sizeVar);
    }

    const_iterator cend() const noexcept {
        return const_iterator(data+sizeVar);
    }


    reverse_iterator rbegin() {
        return reverse_iterator(data);
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(data);
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(data);
    }


    reverse_iterator rend() {
        return reverse_iterator(data+sizeVar);
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(data+sizevar);
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(data+sizeVar);
    }

//!Capacity

    bool empty() const {
        return sizeVar == 0;
    }

    size_t size() const {
        return sizeVar;
    }

    size_t max_size() const noexcept {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    size_t capacity() const {
        return capacity;
    }

    void reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            // Allocate new memory with the specified capacity
            T* newData = new T[newCapacity];

            // Copy existing elements to the new memory
            for (size_t i = 0; i < sizeVar; ++i) {
                newData[i] = data[i];
            }

            // Free the old memory
            delete[] data;

            // Update the data pointer and capacity
            data = newData;
            capacity = newCapacity;
        }
        if (newCapacity > max_size())
            throw std::length_error("Vector: capacity bigger than max_size");
    }

    void shrink_to_fit() {
        if (capacity > sizeVar) {
            // Allocate new memory with the current size
            T* newData = new T[sizeVar];

            // Copy existing elements to the new memory
            for (size_t i = 0; i < sizeVar; ++i) {
                newData[i] = data[i];
            }

            // Free the old memory
            delete[] data;

            // Update the data pointer and capacity
            data = newData;
            capacity = sizeVar;
        }
    }

//!modifiers

    void clear() {
        sizeVar = 0;
    }

    //copies the value
    iterator insert(const_iterator pos, const T& value) {
        size_t index = pos - cbegin(); // Calculate the index from the iterator

        if (sizeVar == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2); // Ensure enough capacity
        }

        // Shift elements to the right
        for (size_t i = sizeVar; i > index; --i) {
            data[i] = data[i - 1];
        }

        data[index] = value; // Insert the new element
        ++sizeVar;

        return iterator(data + index); // Return an iterator to the inserted element
    }

    //moves the value in
    iterator insert(const_iterator pos, T&& value) {
        size_t index = pos - cbegin();

        if (sizeVar == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }

        for (size_t i = sizeVar; i > index; --i) {
            data[i] = std::move(data[i - 1]);
        }

        data[index] = std::move(value);
        ++sizeVar;

        return iterator(data + index);
    }

    //inserts multiple copies of an element
    iterator insert(const_iterator pos, size_type count, const T& value) {
        size_t index = pos - cbegin();

        if (sizeVar + count > capacity) {
            reserve(std::max(capacity * 2, sizeVar + count));
        }

        // Shift elements to the right
        for (size_t i = sizeVar; i > index; --i) {
            data[i + count - 1] = data[i - 1];
        }

        // Insert the new elements
        for (size_t i = 0; i < count; ++i) {
            data[index + i] = value;
        }

        sizeVar += count;

        return iterator(data + index);
    }

    //inserts a range of elements
    template <class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        size_t index = pos - cbegin();
        size_t count = std::distance(first, last);

        if (sizeVar + count > capacity) {
            reserve(std::max(capacity * 2, sizeVar + count));
        }

        // Shift elements to the right
        for (size_t i = sizeVar; i > index; --i) {
            data[i + count - 1] = data[i - 1];
        }

        // Insert the new elements
        for (size_t i = 0; first != last; ++first, ++i) {
            data[index + i] = *first;
        }

        sizeVar += count;

        return iterator(data + index);
    }

    //inserts from an initializer list
    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        return insert(pos, ilist.begin(), ilist.end());
    }

    template <typename Range>
    iterator insert_range(const_iterator pos, Range&& rg) {
        auto first = std::ranges::begin(rg);
        auto last = std::ranges::end(rg);

        size_t index = pos - cbegin(); // Calculate the index from the iterator
        size_t count = std::distance(first, last); // Number of elements in the range

        if (sizeVar + count > capacity) {
            reserve(std::max(capacity * 2, sizeVar + count)); // Ensure enough capacity
        }

        // Shift elements to the right
        for (size_t i = sizeVar; i > index; --i) {
            data[i + count - 1] = data[i - 1];
        }

        // Insert the new elements from the range
        for (size_t i = 0; first != last; ++first, ++i) {
            data[index + i] = *first;
        }

        sizeVar += count;

        return iterator(data + index); // Return an iterator to the first inserted element
    }

    //creates an element directly in the specified location
    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        size_t index = pos - cbegin();

        if (sizeVar == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }

        for (size_t i = sizeVar; i > index; --i) {
            data[i] = std::move(data[i - 1]);
        }

        new (&data[index]) T(std::forward<Args>(args)...);

        ++sizeVar;

        return iterator(data + index);
    }

    //Erase a Single Element
    iterator erase(iterator pos) {
        size_t index = pos - cbegin(); // Calculate the index from the iterator

        if (index >= sizeVar) {
            throw std::out_of_range("Vector::erase: position out of range");
        }

        // Shift elements to the left
        for (size_t i = index; i < sizeVar - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }

        --sizeVar; // Reduce the size of the vector

        return iterator(data + index); // Return an iterator to the next element
    }

    iterator erase(const_iterator pos) {
        size_t index = pos - cbegin(); // Calculate the index from the iterator

        if (index >= sizeVar) {
            throw std::out_of_range("Vector::erase: position out of range");
        }

        // Shift elements to the left
        for (size_t i = index; i < sizeVar - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }

        --sizeVar; // Reduce the size of the vector

        return iterator(data + index); // Return an iterator to the next element
    }

    iterator erase(iterator first, iterator last) {
        size_t startIndex = first - cbegin(); // Calculate the starting index
        size_t endIndex = last - cbegin();   // Calculate the ending index

        if (startIndex >= sizeVar || endIndex > sizeVar || startIndex > endIndex) {
            throw std::out_of_range("Vector::erase: range out of range");
        }

        size_t count = endIndex - startIndex; // Number of elements to erase

        // Shift elements to the left
        for (size_t i = startIndex; i < sizeVar - count; ++i) {
            data[i] = std::move(data[i + count]);
        }

        sizeVar -= count; // Reduce the size of the vector

        return iterator(data + startIndex); // Return an iterator to the next element
    }

    //Erase a Range of Elements
    iterator erase(const_iterator first, const_iterator last) {
        size_t startIndex = first - cbegin(); // Calculate the starting index
        size_t endIndex = last - cbegin();   // Calculate the ending index

        if (startIndex >= sizeVar || endIndex > sizeVar || startIndex > endIndex) {
            throw std::out_of_range("Vector::erase: range out of range");
        }

        size_t count = endIndex - startIndex; // Number of elements to erase

        // Shift elements to the left
        for (size_t i = startIndex; i < sizeVar - count; ++i) {
            data[i] = std::move(data[i + count]);
        }

        sizeVar -= count; // Reduce the size of the vector

        return iterator(data + startIndex); // Return an iterator to the next element
    }


    // Add an element to the end
    void push_back(const T& value) {
        if (sizeVar == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[sizeVar++] = value;
    }

    void push_back(T&& value) {
        if (sizeVar == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2); // Ensure enough capacity
        }
        data[sizeVar++] = std::move(value); // Move the value into the vector
    }


    template <class... Args>
    void emplace_back(Args&&... args) {
        if (sizeVar == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2); // Ensure enough capacity
        }

        // Construct the new element in place at the end
        new (&data[sizeVar]) T(std::forward<Args>(args)...);

        ++sizeVar; // Increase the size of the vector
    }

    template <class... Args>
    reference emplace_back(Args&&... args) {
        if (sizeVar == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }

        new (&data[sizeVar]) T(std::forward<Args>(args)...);

        ++sizeVar;

        return data[sizeVar - 1];
    }

    template <typename Range>
    constexpr void append_range(Range&& rg) {
        auto first = std::ranges::begin(rg);
        auto last = std::ranges::end(rg);

        size_t count = std::distance(first, last); // Number of elements in the range

        if (sizeVar + count > capacity) {
            reserve(std::max(capacity * 2, sizeVar + count)); // Ensure enough capacity
        }

        // Append the elements from the range
        for (; first != last; ++first) {
            new (&data[sizeVar++]) T(*first); // Construct elements in place
        }
    }

    // Remove the last element
    void pop_back() {
        if (sizeVar == 0) {
            throw std::out_of_range("Vector is empty");
        }
        --sizeVar;
    }

    void resize(size_t count) {
        if (count > capacity) {
            reserve(count); // Ensure enough capacity
        }

        if (count > sizeVar) {
            // Default-construct new elements
            for (size_t i = sizeVar; i < count; ++i) {
                new (&data[i]) T();
            }
        } else if (count < sizeVar) {
            // Destroy elements beyond the new size
            for (size_t i = count; i < sizeVar; ++i) {
                data[i].~T();
            }
        }

        sizeVar = count; // Update the size
    }

    void resize(size_t count, const T& value) {
        if (count > capacity) {
            reserve(count); // Ensure enough capacity
        }

        if (count > sizeVar) {
            // Construct new elements with the specified value
            for (size_t i = sizeVar; i < count; ++i) {
                new (&data[i]) T(value);
            }
        } else if (count < sizeVar) {
            // Destroy elements beyond the new size
            for (size_t i = count; i < sizeVar; ++i) {
                data[i].~T();
            }
        }

        sizeVar = count; // Update the size
    }

    void swap(Vector& other) noexcept {
        std::swap(data, other.data);       // Swap the data pointers
        std::swap(sizeVar, other.sizeVar); // Swap the sizes
        std::swap(capacity, other.capacity); // Swap the capacities
    }

    void swap(Vector& other) noexcept(
        std::allocator_traits<std::allocator<T>>::propagate_on_container_swap::value ||
        std::allocator_traits<std::allocator<T>>::is_always_equal::value) {
        std::swap(data, other.data);       // Swap the data pointers
        std::swap(sizeVar, other.sizeVar); // Swap the sizes
        std::swap(capacity, other.capacity); // Swap the capacities
    }






    // Access an element by index
    T& operator[](size_t index) {
        if (index >= sizeVar) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= sizeVar) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    
};

//!non-member functions
    template <typename T>
    bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }

        for (size_t i = 0; i < lhs.size(); ++i) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }

        return true;
    }

    
    template <typename T>
    bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
        return !(lhs == rhs); // Use the negation of operator==
    }


    template <typename T>
    bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
        size_t minSize = std::min(lhs.size(), rhs.size());

        for (size_t i = 0; i < minSize; ++i) {
            if (lhs[i] < rhs[i]) {
                return true; // lhs is less than rhs
            } else if (lhs[i] > rhs[i]) {
                return false; // lhs is not less than rhs
            }
        }

        // If all compared elements are equal, the shorter vector is considered smaller
        return lhs.size() < rhs.size();
    }


    template <typename T>
    bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
        return !(rhs < lhs); // Use the negation of operator< for the reverse comparison
    }


    template <typename T>
    bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
        return rhs < lhs; // Use the reverse of operator<
    }

    template <typename T>
    bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
        return !(lhs < rhs); // Use the negation of operator< for the reverse comparison
    }

int main() {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::cout << "Vector elements: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    vec.pop_back();
    std::cout << "After pop_back, size: " << vec.size() << "\n";

    return 0;
}