#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

// TARGET : 251927063

#define HAND_SIZE 1000
#define LINE_SIZE 256

enum HandType {
    HIGH, 
    ONE,
    TWO,
    THREE,
    FULL,
    FOUR,
    FIVE
};

int countChars( char* s, char c ){
    return *s == '\0'
              ? 0
              : countChars( s + 1, c ) + (*s == c);
}


enum HandType find_type(char *val) { 
    int occ[5] = {0, 0, 0, 0, 0};

    for (size_t i = 0; i<5; ++i) { 
        for (size_t j = 0; j<=i; ++j) { 
            if (val[i] == val[j]) { 
                occ[j]++;
                break;
            }
        }
    }
    for (size_t i = 0; i<5; ++i) { 
        if (occ[i] == 5) { 
            return FIVE;
        }
        if (occ[i] == 4)
            return FOUR;
        if (occ[i] == 3) { 
            for (size_t j = 0; j<5; ++j) { 
                if (occ[j] == 1)
                    return THREE;
                if (occ[j] == 2)
                    return FULL;
            }
        }
        if (occ[i] == 2) { 
            for (size_t j = 0; j<5; ++j) { 
                if (occ[j] == 2 && j!=i)
                    return TWO;
                if (occ[j] == 3)
                    return FULL;
            }
            return ONE;
        }
    }
    return HIGH;
}

struct Hand { 
    char *value;
    int bid;
    enum HandType type;
};

typedef int (*comp_func_t)(struct Hand* h1, struct Hand *h2);
int compare_hands(struct Hand *h1, struct Hand *h2) { 
    if (h1->type != h2->type) 
        return h2->type - h1->type;
    char str[14] = "AKQJT98765432";
    int val1 = 0;
    int val2 = 0;
    size_t j = 0;
    while (val1 == val2){
    for (size_t i = 0; i<14; ++i) { 
        if (h2->value[j] == str[i])
            val2 = 14-i;
        if (h1->value[j] == str[i]) 
            val1 = 14-i;
    }
    ++j;
    }
    return val2 - val1;
}

char *str_cut(char *str, char separator) {
    char *res = str;
    while (*res != separator && *res != '\n' && *res != '\0') {
        ++res;
    }
    return res;
}

char *str_cut_inv(char *str, char separator) {
    char *res = calloc(LINE_SIZE, sizeof(char));
    size_t i = 0;
    while (str[i] != separator && str[i] != '\n' && str[i] != '\0') { 
        res[i] = str[i];
        ++i;
    }
    return res;
}



void _Hand_swap(struct Hand **self, size_t i, size_t j) { 
    struct Hand *tmp = self[i];
    self[i] = self[j];
    self[j] = tmp;
}

ptrdiff_t _Hand_partition(struct Hand **self, ptrdiff_t i, ptrdiff_t j, comp_func_t func){
	ptrdiff_t pivot_index = i;
        struct Hand *pivot = self[pivot_index];
	_Hand_swap(self, pivot_index, j);
	ptrdiff_t l = i;
	for(ptrdiff_t k = i; k < j; ++k){
		if(func(self[k], pivot) > 0){
			_Hand_swap(self, k, l);
			++l;
		}
	}
	_Hand_swap(self, l, j);
	return l;
}



void _Hand_quick_sort_partial(struct Hand **self, ptrdiff_t i, ptrdiff_t j, comp_func_t func){
	if(i < j){
		ptrdiff_t p = _Hand_partition(self, i, j, func);
		_Hand_quick_sort_partial(self, i, p - 1, func);
		_Hand_quick_sort_partial(self, p + 1, j, func);
	}
}


void _Hand_quick_sort(struct  Hand**self, comp_func_t func, size_t size){
	_Hand_quick_sort_partial(self, 0, size - 1, func);
}

int main(int argc, char **argv) {

    FILE *fptr;
    fptr = fopen("../input/day7.txt", "r");
    if (fptr == NULL) return -1;

    struct Hand* hands[HAND_SIZE]; 
    for (size_t i= 0; i<HAND_SIZE; ++i) {
        hands[i] = calloc(1, sizeof(struct Hand));
    }
    char buffer[LINE_SIZE];
    size_t i = 0;
    while (fgets(buffer, LINE_SIZE, fptr)) { 
        buffer[strcspn(buffer, "\n")] = '\0';
        hands[i]->bid = atoi(str_cut(buffer, ' '));
        hands[i]->value = calloc(5, sizeof(char));
        hands[i]->value = str_cut_inv(buffer, ' ');
        hands[i]->type = find_type(hands[i]->value);
        i++;
    }

    _Hand_quick_sort(hands, compare_hands, HAND_SIZE);
    long res = 0;
    for (int i= 0; i<HAND_SIZE; ++i) {
        res += hands[i]->bid * (i+1);
        free(hands[i]->value);
        free(hands[i]);
    }
    
    printf("res: %ld \n", res);

    return 0;
}
