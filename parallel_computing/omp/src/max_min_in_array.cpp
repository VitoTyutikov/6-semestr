#include <cstdio>
#include <omp.h>

int main() {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a_min = a[0];
    int b_max = b[0];
#pragma omp parallel num_threads(2) shared(a_min, b_max, a, b) default(none)
    {
        if (omp_get_thread_num() == 0) {
            for (size_t i = 0; i < 10; i++) {
                if (a_min > a[i]) {
                    a_min = a[i];
                }
            }
        } else {
            for (size_t i = 0; i < 10; i++) {
                if (b_max < b[i]) {
                    b_max = b[i];
                }
            }
        }
    }
    printf("min in a = %d\tmax in b = %d", a_min, b_max);
    return 0;
}