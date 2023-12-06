#include <stdio.h>
#include <time.h>

long day6_partial(long time, long distance) {
    long res = 0;
    for (size_t i = 0; i<time; ++i) {
        if (i*(time-i) > distance) 
            res++;
    }
    return res;
}

int main(int argc, char **argv) {
    clock_t t1, t2;
    long res;
    t1 = clock();
    res = day6_partial(53897698, 313109012141201);
    t2 = clock();
    printf("%ld \n", res);
    printf("%f \n", (double)(t2-t1)/(double)CLOCKS_PER_SEC);
    return 0;
}
