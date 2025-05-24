#pragma once

#include <vector>
#include <algorithm>

namespace filesync::types {

template <typename T>
class SortedVector {
    std::vector<T> data;

public:
    SortedVector() = default;
    ~SortedVector() = default;

    SortedVector(const SortedVector& o) : data{o.data} {}
    SortedVector& operator=(const SortedVector& o) {
        if (this != &o) {
            data = o.data;
        }
        return *this;
    }
    SortedVector(SortedVector&& o) : data{std::move(o.data)} {}
    SortedVector& operator=(SortedVector&& o) {
        if (this != &o) {
            data = std::move(o.data);
        }
        return *this;
    }

    typename std::vector<T>::const_iterator begin() const { return data.begin(); }
    typename std::vector<T>::const_iterator end() const { return data.end(); }
    size_t size() const { return data.size(); }
    void clear() { data.clear(); }

    void insert(const T& element) {
        data.insert(std::upper_bound(data.begin(), data.end(), element), element);
    }

    void insert(typename std::vector<T>::const_iterator begin,
                typename std::vector<T>::const_iterator end) {
        if (data.size() > static_cast<size_t>(std::distance(begin, end))) {
            for (auto it = begin; it != end; ++it) {
                insert(*it);
            }
        }
        else {
            data.insert(data.end(), begin, end);
            std::sort(data.begin(), data.end());
        }
    }
};

}
