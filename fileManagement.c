//
// Created by bogda on 13/07/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "fileManagement.h"

void readFile(char *fileName, char *output) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", fileName);
        exit(1);
    }
    fscanf(file, "%[^\n]s", output);
    fclose(file);
}