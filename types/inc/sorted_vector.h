#pragma once

#include <vector>

namespace filesync::types {

template <typename T>
class SortedVector {
    std::vector<T> data;

public:
    SortedVector() = default;
    ~SortedVector() = default;
    SortedVector(const SortedVector&) noexcept;
    SortedVector& operator=(const SortedVector&) noexcept;
    SortedVector(SortedVector&&) noexcept;
    SortedVector& operator=(SortedVector&&) noexcept;

    std::vector<T>::const_iterator begin() const;
    std::vector<T>::const_iterator end() const;
    size_t size() const;
    void clear();

    void insert(const T& element);
    void insert(const std::vector<T>::const_iterator& begin, const std::vector<T>::const_iterator& end);
};

}
