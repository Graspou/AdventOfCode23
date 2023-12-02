#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 256

char *str_cut(char *str, char separator) {
    char *res = str;
    while (*res != separator && *res != '\n' && *res != '\0') {
        ++res;
    }
    return res;
}

void slice(const char *str, char *result, size_t start, size_t end) {
    strncpy(result, str + start, end - start);
}

int main(int argc, char **argv) {

    FILE *fptr;
    fptr = fopen("../input/day2.txt", "r");

    if (fptr == NULL) {
        printf("ERROR: file could not be opened.");
        return -1;
    }

    int res = 0;

    char *buffer = malloc(MAX_LINE_LENGTH);
    while (fgets(buffer, MAX_LINE_LENGTH, fptr)) {

        bool is_valid = true;
        char *tmp = malloc(MAX_LINE_LENGTH);
        if (tmp == NULL) {
            printf("malloc failed");
            return -1;
        }
        char *sets = str_cut(buffer, ':');
        ptrdiff_t tmp_ptr = -1 * (buffer - sets);
        slice(buffer, tmp, 0, tmp_ptr);
        int game_ID = atoi(tmp + 5); // get rid of Game 

        free(tmp);
        tmp = calloc(MAX_LINE_LENGTH, sizeof(char));
        size_t j = 0;
        int blue = 0;
        int red = 0;
        int green = 0;

        printf("%d \n", game_ID);
        while (is_valid && buffer[j] != '\n' && buffer[j]) {
            red = 0;
            blue = 0;
            green = 0;
            size_t i = 0;
            while (buffer[j] != ';' && buffer[j] != '\n' && buffer[j]) {
                if (buffer[j] == ' ') {
                    if (i != 0) {
                        if (buffer[j + 1] == 'b') {
                            blue += atoi(tmp);
                        } else if (buffer[j + 1] == 'r') {
                            red += atoi(tmp);
                        } else if (buffer[j + 1] == 'g') {
                            green += atoi(tmp);
                        }
                        free(tmp);
                        tmp = calloc(MAX_LINE_LENGTH, sizeof(char));
                        i = 0;
                    }
                }
                if (buffer[j] >= '0' && buffer[j] <= '9') {
                    *(tmp + i) = buffer[j];
                    ++i;
                }
                j++;
            }

            // Ajouter ici, après la fin de l'ensemble de chiffres
            if (i != 0) {
                if (buffer[j] == ' ') {
                    if (buffer[j + 1] == 'b') {
                        blue += atoi(tmp);
                    } else if (buffer[j + 1] == 'r') {
                        red += atoi(tmp);
                    } else if (buffer[j + 1] == 'g') {
                        green += atoi(tmp);
                    }
                }
            }

            printf("blue: %i \n", blue);
            ++j;
            i = 0;
            is_valid = red <= 12 && green <= 13 && blue <= 14;
            printf("%d \n", is_valid);

        }
        if (is_valid)
            res += game_ID;

        buffer[0] = '\0';
        j = 0;
    }
    printf("%i \n", res);

    return 0;
}

