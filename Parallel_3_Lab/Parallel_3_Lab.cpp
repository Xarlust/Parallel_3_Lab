#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    int mas[1000];
    int i, max;
    omp_lock_t lock;
    omp_init_lock(&lock);
    for (i = 0; i < 1000; i++)
        mas[i] = rand();
    max = mas[0];

#pragma omp parallel for shared(mas, lock)
    for (i = 0; i < 1000; i++)
    {
        omp_set_lock(&lock);
        if (mas[i] > max)
            max = mas[i];
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
    cout << "Результат: " << max << endl;
    return 0;
}