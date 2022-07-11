//
// Created by Bogdan on 08/07/2022.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// Per ora non ne abbiamo bisogno, i messaggi che sto dando sono già in esadecimale
char *to_hex_string(char *input) {
    if (strlen(input) > 16) {
        perror("Input too long");
        return NULL;
    }
    char *output = malloc(sizeof(char) * (strlen(input) * 2 + 1));
    int i;
    for (i = 0; i < strlen(input); i++) {
        sprintf(output + (i * 2), "%02x", input[i]);
    }
    return output;
}

char * to_bit_string(char *input){
    if (strlen(input) > 64) {
        perror("Input too long");
        return NULL;
    }
    char *output = malloc(sizeof(char) * (strlen(input) * 4 + 1));
    for (int i = 0; i < strlen(input); i++) {
        switch (input[i]) {
            case '0':
                sprintf(output + (i * 4), "0000");
                break;
            case '1':
                sprintf(output + (i * 4), "0001");
                break;
            case '2':
                sprintf(output + (i * 4), "0010");
                break;
            case '3':
                sprintf(output + (i * 4), "0011");
                break;
            case '4':
                sprintf(output + (i * 4), "0100");
                break;
            case '5':
                sprintf(output + (i * 4), "0101");
                break;
            case '6':
                sprintf(output + (i * 4), "0110");
                break;
            case '7':
                sprintf(output + (i * 4), "0111");
                break;
            case '8':
                sprintf(output + (i * 4), "1000");
                break;
            case '9':
                sprintf(output + (i * 4), "1001");
                break;
            case 'a':
                sprintf(output + (i * 4), "1010");
                break;
            case 'b':
                sprintf(output + (i * 4), "1011");
                break;
            case 'c':
                sprintf(output + (i * 4), "1100");
                break;
            case 'd':
                sprintf(output + (i * 4), "1101");
                break;
            case 'e':
                sprintf(output + (i * 4), "1110");
                break;
            case 'f':
                sprintf(output + (i * 4), "1111");
                break;
            default:
                perror("Invalid input");
                return NULL;
        }
    }
    return output;
}