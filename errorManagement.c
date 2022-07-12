//
// Created by bogda on 12/07/2022.
//

#include <string.h>
#include <malloc.h>

char *validateMessage(char *message) {
    char *temp = malloc(sizeof(char) * (strlen(message) + 1));
    temp = strcpy(temp, message);
    while (strlen(temp) < 16) {
        strcat(temp, "0");
    }
    temp[16] = '\0';
    return temp;
}