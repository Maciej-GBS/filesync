#pragma once

#include <vector>

namespace filesync::types {

template <typename T>
class SortedVector {
    std::vector<T> data;

public:
    SortedVector() = default;
    ~SortedVector() = default;
    SortedVector(const SortedVector&);
    SortedVector& operator=(const SortedVector&);
    SortedVector(SortedVector&&);
    SortedVector& operator=(SortedVector&&);

    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::const_iterator end() const;
    size_t size() const;
    void clear();

    void insert(const T& element);
    void insert(typename std::vector<T>::const_iterator begin,
                typename std::vector<T>::const_iterator end);
};

}
