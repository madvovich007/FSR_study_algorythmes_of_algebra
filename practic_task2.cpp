#include <iostream>

template <class Container, class Comparator>
void quick_sort(Container& c, int n, int left, int right){
    if (left >= right){
        return;
    }
    auto pivot = c[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j){
        while (Comparator::compare(c[i], pivot)){
            i++;
        }
        while (Comparator::compare(pivot, c[j])){
            j--;
        }
        if (i <= j){
            c.swap(i, j);
            i++;
            j--;
        }
    }
    quick_sort<Container, Comparator>(c, n, left, j);
    quick_sort<Container, Comparator>(c, n, i, right);
}