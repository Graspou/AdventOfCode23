#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_LINE_LENGTH 256


char firstDigit(const char *str) { 
    size_t i = 0;
    while (*(str + i) != '\n' && *(str + i)) { 
        if (*(str + i) >= '0' && *(str + i) <= '9') 
            return *(str + i);
        i++;
    }
    return 0;
}
char lastDigit(const char *str) { 
    size_t i = 0;
    char res = 0;
    while (*(str + i) != '\n' && *(str + i)) { 
        if (*(str + i) >= '0' && *(str + i) <= '9') 
            res = *(str + i);
        i++;
    }
    return res;
}

int file_lines_nbr(FILE *fptr) { 
    int res = 0;
    char buf[MAX_LINE_LENGTH];
    while (fgets(buf, sizeof(buf), fptr) != NULL)
        res++;
    fseek(fptr, 0, SEEK_SET);
    return res;
}

int parse_nbr(char first, char last) { 
    return (last - '0') + 10 * (first - '0');
}



int main(int argc, char **argv) { 
    printf("%c \n", firstDigit("avec plaisir 3 \n"));
    printf("%c \n", lastDigit("avec plaisir 3, même si bon dinguerie 5 mais non 8 \n"));

    FILE *fptr;

    fptr = fopen("../input/day1_2.txt", "r");

    if (fptr == NULL) { 
        printf("ERROR: file not opened.\n");
        return 1;
    }

    int n = file_lines_nbr(fptr);
    int sum = 0;

    //char **file_str = malloc(n * sizeof(char *));
    for (size_t i = 0; i<n; ++i) {
        //file_str[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
        char *tmp = malloc(MAX_LINE_LENGTH * sizeof(char));
        if (!tmp) { 
            printf("ERROR: malloc failed\n");
            return 1;
        }
        fgets(tmp, MAX_LINE_LENGTH, fptr);
        printf("%s \n", tmp);
        sum += parse_nbr(firstDigit(tmp), lastDigit(tmp));
        free(tmp);
    }

    printf("%i \n", sum);

    fclose(fptr);
    return 0;
}
