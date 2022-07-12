//
// Created by Bogdan on 08/07/2022.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

char *message_to_hex(char *message) {
    int loop;
    int i;

    char *hexString = message;
    char *output = malloc(sizeof(char) * 33);
    i=0;
    loop=0;

    while(hexString[loop] != '\0')
    {
        sprintf((char*)(output+i),"%02X", hexString[loop]);
        loop+=1;
        i+=2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
    return output;
}

int bit_to_hex(char *binaryval) {
    char *a = binaryval;
    int num = 0;
    do {
        int b = *a == '1' ? 1 : 0;
        num = (num << 1) | b;
        a++;
    } while (*a);
    return num;
}

char *cut(const char *input, int start, int end) {
    char *output = malloc(sizeof(char) * (end - start + 1));
    int i;
    for (i = start; i <= end; i++) {
        output[i - start] = input[i];
    }
    return output;
}

int toIntFromBitString(char *input) {
    int value = 0;
    for (int i = 0; i < strlen(input); i++) {
        value += (input[i] - '0') * pow(2, strlen(input) - i - 1);
    }
    return value;
}

char *toBitStringFromInt(int input) {
    char *output = malloc(4);
    switch (input) {
        case 0:
            sprintf(output, "0000");
            break;
        case 1:
            sprintf(output, "0001");
            break;
        case 2:
            sprintf(output, "0010");
            break;
        case 3:
            sprintf(output, "0011");
            break;
        case 4:
            sprintf(output, "0100");
            break;
        case 5:
            sprintf(output, "0101");
            break;
        case 6:
            sprintf(output, "0110");
            break;
        case 7:
            sprintf(output, "0111");
            break;
        case 8:
            sprintf(output, "1000");
            break;
        case 9:
            sprintf(output, "1001");
            break;
        case 10:
            sprintf(output, "1010");
            break;
        case 11:
            sprintf(output, "1011");
            break;
        case 12:
            sprintf(output, "1100");
            break;
        case 13:
            sprintf(output, "1101");
            break;
        case 14:
            sprintf(output, "1110");
            break;
        case 15:
            sprintf(output, "1111");
            break;
        default:
            perror("Invalid input");
            printf("%d\n", input);
            return NULL;

    }
    return output;
}


char *to_bit_string(char *input) {
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
            case 'A':
                sprintf(output + (i * 4), "1010");
                break;
            case 'B':
                sprintf(output + (i * 4), "1011");
                break;
            case 'C':
                sprintf(output + (i * 4), "1100");
                break;
            case 'D':
                sprintf(output + (i * 4), "1101");
                break;
            case 'E':
                sprintf(output + (i * 4), "1110");
                break;
            case 'F':
                sprintf(output + (i * 4), "1111");
                break;
            default:
                perror("Invalid input");
                printf("%c\n", input[i]);
                return NULL;
        }
    }
    return output;
}