#include <stdio.h>



int day6_partial(int time, int distance) {
    int res = 0;
    for (size_t i = 0; i<time; ++i) {
        if (i*(time-i) > distance) 
            res++;
    }
    return res;
}




int main(int argc, char **argv) {

    int res;
    res = day6_partial(53, 313);
    res *= day6_partial(89, 1090);
    res *= day6_partial(76, 1214);
    res *= day6_partial(98, 1201);
    printf("%i \n", res);

    return 0;
}
