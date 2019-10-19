#include "lib/src/library.h"
#include <stdio.h>
#include "main.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        FILE *input_file = fopen(argv[1], "r");
        if (input_file == NULL) return 1;
        FILE *write_file = fopen(argv[2], "w");
        if (write_file == NULL) {
            fclose(input_file);
            return 1;
        }


    } else {
        printf("Wrong input in command row\n");
    }
    return 0;
}