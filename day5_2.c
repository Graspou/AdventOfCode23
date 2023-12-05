#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_LINE_LENGTH 256
#define SEED_NBR 20

struct Map { 
    long dest_start;
    long origin_start;
    long range;
};

long *parse_to_array(const char *line, size_t size) {
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    char *str = malloc(32 * sizeof(char));
    long *res = malloc(size * sizeof(long));
    while (line[i] != '\n' && line[i] != '\0') {
        if (line[i] >= '0' && line[i] <= '9') {
            str[k] = line[i];
            ++k;
        }
        else if (k > 0) {
            str[k] = '\0';  
            res[j] = atol(str);
            k = 0;
            ++j;
        }
        i++;
    }
    if (k > 0) {
        str[k] = '\0';  
        res[j] = atol(str);
    }
    free(str);  
    return res;
}

char *str_cut(char *str, char separator) {
    char *res = str;
    while (*res != separator && *res != '\n' && *res != '\0') {
        ++res;
    }
    return res;
}



struct Map *get_map(char *line) { 
    long *arr = parse_to_array(line, 3);
    struct Map *m = calloc(1, sizeof(struct Map));
    m->dest_start = arr[0];
    m->origin_start = arr[1];
    m->range = arr[2];
    return m;
}



int main() {

    FILE *fptr;
    fptr = fopen("../input/day5.txt", "r");
    if (fptr == NULL) {
        printf("could not open file");
        return -1;
    }

    bool done_seeds = false;
    
    long *seeds = NULL;
    struct Map *maps[7][50];
    for (size_t i = 0; i<7; ++i) { 
        for (size_t j =0; j<50; ++j) { 
            maps[i][j] = NULL;
        }
    }
    size_t map = 0;
    size_t map_ = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, fptr)) { 
        if (!done_seeds) { 
            char *seeds_str = str_cut(buffer, ':');
            seeds = parse_to_array(seeds_str, SEED_NBR);
            done_seeds = true;
        } 
        else { 
            if(buffer[0] < '0' || buffer[0] > '9') {
                map++;
                map_ = 0;
            } else {
                maps[map][map_] = get_map(buffer);
                map_++;
            }
        }
    }

    long min = 2147483647;
    for (size_t s = 0; s<SEED_NBR; s+=2) { 
        long seed_start = seeds[s];
        long seed_range = seeds[s+1];
        for (long sd = seed_start; sd < seed_start + seed_range; sd++) { 
            long seed = sd;
            for (size_t i=0; i<7; ++i) { 
                size_t j = 0;
                bool done = false;
                while (!done && maps[i][j] != NULL){ //&& maps[i][j+1] != 0) { 
                    struct Map *m = maps[i][j];
                    if (seed >= m->origin_start && seed < m->origin_start + m->range) { 
                        seed = (seed-m->origin_start) + m->dest_start;
                        done = true;
                    }
                    ++j;
                } 
            }
                if (seed < min ) {
                    min = seed;
                }
        }

    }
    
    printf("res : %ld \n", min);
    fclose(fptr);


    return 0;
}
