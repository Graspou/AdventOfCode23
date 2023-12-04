#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 256

int two_to_power(int n) { 
    return 1 << n;
}

char *str_cut(char *str, char separator) {
    char *res = str;
    while (*res != separator && *res != '\n' && *res != '\0') {
        ++res;
    }
    return res;
}

char *str_cut_inv(char *str, char separator) {
    char *res = calloc(MAX_LINE_LENGTH, sizeof(char));
    size_t i = 0;
    while (str[i] != separator && str[i] != '\n' && str[i] != '\0') { 
        res[i] = str[i];
        ++i;
    }
    return res;
}

void slice(const char *str, char *result, size_t start, size_t end) {
    strncpy(result, str + start, end - start);
}

void parse_to_arr(const char *win_pts, int *win_pts_arr, size_t size) { 
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    char *tmp = calloc(MAX_LINE_LENGTH, sizeof(char));
    while (i <= size && win_pts[j] != '|' && win_pts[j-1] != '\n') { 
        if (win_pts[j] == ' ' && k > 0 || win_pts[j] == '\n') { 
            win_pts_arr[i] = atoi(tmp);
            free(tmp);
            tmp = calloc(MAX_LINE_LENGTH, sizeof(char));
            i++;
            j++;
            k = 0;
        } 
        else if (win_pts[j] >= '0' && win_pts[j] <= '9'){ 
            tmp[k] = win_pts[j];
            k++;
            j++;
        } else { 
            ++j;
        }
    }
    free(tmp);
}




int main(int argc, char **argv) {
    
    FILE *fptr;
    fptr = fopen("../input/day4.txt", "r");

    if (fptr == NULL) {
        fprintf(stderr, "ERROR: could not open file.");
        return -1;
    }


    int res = 0;

    char buffer[MAX_LINE_LENGTH];
    int s1 = 10;
    int s2 = 25;
    int s3 = 202;
    int histogramme[s3] ;
    //histogramme[0] = 1;
    
    for (size_t i = 0; i<s3; ++i) { 
        histogramme[i] = 1;
    }
    while (fgets(buffer, MAX_LINE_LENGTH, fptr)) { 


        char *game = str_cut(buffer, ':');
        char *sets = str_cut(game, '|');
        char *win_pts = str_cut_inv(game, '|');
        win_pts++;
        sets++;
        
       

        int *win_pts_arr = malloc(s1 * sizeof(int));
        int *set_pts = malloc(s2 * sizeof(int));
        parse_to_arr(win_pts, win_pts_arr, s1);
        parse_to_arr(sets, set_pts, s2);


        int res_tmp = atoi(str_cut_inv(buffer, ':') + 5);
        printf("%i \n", res_tmp);
        int tmpp = res_tmp;
        //printf("%i \n", res_tmp);
        int times = histogramme[res_tmp-1];

        /*
        printf("\n %s \n", sets);
        for (size_t i = 0; i<s2; ++i) { 
            printf("%i \n", set_pts[i]);
        }
        
        printf("\n %s \n", sets);
        for (size_t i = 0; i<s1; ++i) { 
            printf("%i \n", win_pts_arr[i]);
        }
        */

        for (size_t i=0; i<s1; ++i) { 
            for (size_t j=0; j<s2; ++j) {
                if (set_pts[j] == win_pts_arr[i]) { 
                    res_tmp++;
                    //printf("pow : %i\n", power);
                    //res += two_to_power(power);
                    //
                    //if (b)
                    //    power++;
                    //else 
                    //    b = true;
                }
            }
        }
        
        for (size_t i=tmpp; i<res_tmp; ++i) { 
            histogramme[i] += times;
        }


    }

    for (size_t i = 0; i<s3; ++i) { 
        res += histogramme[i];
        printf("%lu : %i\n", i+1, histogramme[i]);
    }

    printf("résultat : %i\n", res);

    fclose(fptr);

    return 0;
}
