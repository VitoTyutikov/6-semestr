#include <iostream>
#include <omp.h>

int main() {
    omp_set_num_threads(8);
#pragma omp parallel default(none)
    {
        printf("num_thread = %d\t threads_num = %d\t Hello, World!\n", omp_get_thread_num(),
               omp_get_num_threads());
    }
    return 0;
}
