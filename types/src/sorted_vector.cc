#include "../inc/sorted_vector.h"

#include <algorithm>

namespace filesync::types {

template <typename T>
SortedVector<T>::SortedVector(const SortedVector& o) : data{o.data} {}

template <typename T>
SortedVector<T>& SortedVector<T>::operator=(const SortedVector& o) {
    if (this != &o) {
        data = o.data;
    }
    return *this;
}

template <typename T>
SortedVector<T>::SortedVector(SortedVector&& o) : data{std::move(o.data)} {}

template <typename T>
SortedVector<T>& SortedVector<T>::operator=(SortedVector&& o) {
    if (this != &o) {
        data = std::move(o.data);
    }
    return *this;
}

template <typename T>
typename std::vector<T>::const_iterator SortedVector<T>::begin() const { return data.begin(); }

template <typename T>
typename std::vector<T>::const_iterator SortedVector<T>::end() const { return data.end(); }

template <typename T>
size_t SortedVector<T>::size() const { return data.size(); }

template <typename T>
void SortedVector<T>::clear() { data.clear(); }

template <typename T>
void SortedVector<T>::insert(const T& element) {
    data.insert(std::upper_bound(data.begin(), data.end(), element), element);
}

template <typename T>
void SortedVector<T>::insert(typename std::vector<T>::const_iterator begin, typename std::vector<T>::const_iterator end) {
    if (data.size() > std::distance(begin, end)) {
        for (auto it = begin; it != end; ++it) {
            insert(*it);
        }
    }
    else {
        data.insert(data.end(), begin, end);
        std::sort(data.begin(), data.end());
    }
}

}
