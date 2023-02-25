#include <cstdio>
#include <omp.h>

int main()
{

    int a = 7;
    int b = 2;

    printf("Before first parallel region\ta = %d\tb = %d\n", a, b);
#pragma omp parallel num_threads(2) private(a) firstprivate(b) default(none)
    {
        a = 0;
        int num_thread = omp_get_thread_num();
        a += num_thread;
        b += num_thread;
        printf("in first parallel region\ta = %d\tb = %d\tthread_num = %d\n", a, b, num_thread);
    }
    printf("After first parallel region\ta = %d\tb = %d\n\n", a, b);
    printf("Before second parallel region\ta = %d\tb = %d\n", a, b);
#pragma omp parallel num_threads(4) shared(a) private(b) default(none)
    {
        b = 0;
        int num_thread = omp_get_thread_num();
        a -= num_thread;
        b -= num_thread;
        printf("in second parallel region\ta = %d\tb = %d\tthread_num = %d\n", a, b, num_thread);
    }
    printf("After second parallel region\ta = %d\tb = %d", a, b);

    return 0;
}