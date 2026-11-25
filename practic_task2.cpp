#include <iostream>

template <class Container, class Compare>
void quick_sort(Container& c, int n){
    if (n <= 1){
        return;
    }
    Container pivot = c[n / 2];
    int i = 0;
    int j = n - 1;
    if (n > 1){
        while (i <= j){
            while (Compare::cmp(c[i], pivot)){
                i++;
            }
            while (!(Compare::cmp(c[j], pivot))){
                j--;
            }
            if (i <= j){
                swap(c[i], c[j]);
                i++;
                j--;
            }
        }
        quick_sort(c, j + 1);
        quick_sort(c + i, n - i);
    }
}