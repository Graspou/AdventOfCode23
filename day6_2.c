#include <stdio.h>



long day6_partial(long time, long distance) {
    long res = 0;
    for (size_t i = 0; i<time; ++i) {
        if (i*(time-i) > distance) 
            res++;
    }
    return res;
}




int main(int argc, char **argv) {

    long res;
    res = day6_partial(53897698, 313109012141201);
    printf("%ld \n", res);

    return 0;
}
