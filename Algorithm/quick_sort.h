//
//  quick_sort
//  Algorithm
//
//  Created by dtysky on 16/9/14.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_QUICK_SORT_H
#define ALGORITHM_QUICK_SORT_H

#include <cstdio>
#include <vector>
#include "insertion_sort.h"


namespace my_algorithm {
    using std::vector;


    template <typename T> inline
    void _swapForQuickSort(vector<T>& t_vector, const size_t i1, const size_t i2) {
        T tmp = t_vector[i1];
        t_vector[i1] = t_vector[i2];
        t_vector[i2] = tmp;
    }

    // median3, prevent the worst condition
    // set the median item to low, and make their three items be sorted
    template <typename T> inline
    size_t _median3ForQuickSort(vector<T>& t_vector, const size_t low, const size_t high, const bool reverse) {
        auto middle = (high + low) / 2;
        if (t_vector[low] < t_vector[middle]) {
            _swapForQuickSort(t_vector, low, middle);
        }
        if (t_vector[middle] > t_vector[high]) {
            _swapForQuickSort(t_vector, middle, high);
        }
        if ((!reverse && t_vector[low] > t_vector[high]) || (reverse && t_vector[low] < t_vector[high])) {
            _swapForQuickSort(t_vector, low, high);
        }
        return middle;
    }

    template <typename T> inline
    size_t _partitionForQuickSort(vector<T>& t_vector, const size_t low, const size_t high, const bool reverse = false) {

        auto middle = _median3ForQuickSort(t_vector, low, high, reverse);

        // if the size of elements is less than 3, they are already sorted
//        if (high - low < 3) {
//            _swapForQuickSort(t_vector, low, middle);
//            return middle;
//        }

        auto comparable = t_vector[low];
        auto l = low + 1;
        auto h = high;

        while (l < h) {
            if (reverse) {
                while(t_vector[h] < comparable && h > l) { h--; }
                while(t_vector[l] >= comparable && l < h) { l++; }
            }
            else {
                while(t_vector[h] > comparable && h > l) { h--; }
                while(t_vector[l] <= comparable && l < h) { l++; }
            }
            _swapForQuickSort(t_vector, l, h);
        }
        _swapForQuickSort(t_vector, l, low);
        return l;
    }

    template <typename T> inline
    vector<size_t> _partitionForQuickSort3Way(vector<T>& t_vector, const size_t low, const size_t high, const bool reverse = false) {

        auto middle = _median3ForQuickSort(t_vector, low, high, reverse);

        // if the size of elements is less than 3, they are already sorted
//        if (high - low < 3) {
//            _swapForQuickSort(t_vector, low, middle);
//            return {low, high};
//        }

        auto comparable = t_vector[low];
        auto l = low;
        auto h = high;
        auto e = l + 1;

        while (e <= h) {
            if ((!reverse && (t_vector[e] < comparable)) || (reverse && (t_vector[e] > comparable))) {
                _swapForQuickSort(t_vector, l++, e++);
            }
            else if ((!reverse && t_vector[e] > comparable) || (reverse && t_vector[e] < comparable)) {
                _swapForQuickSort(t_vector, e, h--);
            }
            else {
                e++;
            }
        }
        return {l, h};
    }

    template <typename T>
    void _sortForQuickSort(vector<T>& t_vector, const size_t low, const size_t high, const bool reverse = false) {
        if (high <= low) {
            return;
        }

        // if the size of elements will be sorted is less than 20, we may use insertion sort to make it quicker like this:
        if (high - low < 20) {
            insertionSort(t_vector, reverse, low, high);
            return;
        }

        auto middle = _partitionForQuickSort(t_vector, low, high, reverse);
        _sortForQuickSort(t_vector, low, middle - 1, reverse);
        _sortForQuickSort(t_vector, middle + 1, high, reverse);
    }

    template <typename T>
    void _sortForQuickSort3Way(vector<T>& t_vector, const size_t low, const size_t high, const bool reverse = false) {
        if (high <= low) {
            return;
        }

        // if the size of elements will be sorted is less than 20, we may use insertion sort to make it quicker like this:
        if (high - low < 20) {
            insertionSort(t_vector, reverse, low, high);
            return;
        }

        // 3way, this method is optimize for vector has many repeated elements
        auto lh = _partitionForQuickSort3Way(t_vector, low, high, reverse);
        if (lh[0] - low > 1) {
            _sortForQuickSort3Way(t_vector, low, lh[0] - 1, reverse);
        }
        if (high - lh[1] > 1) {
            _sortForQuickSort3Way(t_vector, lh[1] + 1, high, reverse);
        }
    }

    // time: O(n * log(n))
    // space: O(n)
    template <typename T>
    void quickSort(vector<T>& t_vector, const bool reverse = false, const bool use3Way = true) {
        // randomly all elements in vector, prevent the worst condition
        std::random_shuffle(t_vector.begin(), t_vector.end());
        if (use3Way) {
            _sortForQuickSort3Way(t_vector, 0, t_vector.size() - 1, reverse);
        }
        else {
            _sortForQuickSort(t_vector, 0, t_vector.size() - 1, reverse);
        }
    }
}

#endif //ALGORITHM_QUICK_SORT_H
