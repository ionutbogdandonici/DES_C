//
// Created by Bogdan on 08/07/2022.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "utility.h"

const char *BINARY_KEY;
const char *PERMUTED_KEY;

char *M;
char *IP_M;
char C[28];
char D[28];

char L[32];
char R[32];

const char IP[8][8] = {
        {58, 50, 42, 34, 26, 18, 10, 2},
        {60, 52, 44, 36, 28, 20, 12, 4},
        {62, 54, 46, 38, 30, 22, 14, 6},
        {64, 56, 48, 40, 32, 24, 16, 8},
        {57, 49, 41, 33, 25, 17, 9,  1},
        {59, 51, 43, 35, 27, 19, 11, 3},
        {61, 53, 45, 37, 29, 21, 13, 5},
        {63, 55, 47, 39, 31, 23, 15, 7}
};

const char PC_1[8][7] = {
        {57, 49, 41, 33, 25, 17, 9},
        {1,  58, 50, 42, 34, 26, 18},
        {10, 2,  59, 51, 43, 35, 27},
        {19, 11, 3,  60, 52, 44, 36},
        {63, 55, 47, 39, 31, 23, 15},
        {7,  62, 54, 46, 38, 30, 22},
        {14, 6,  61, 53, 45, 37, 29},
        {21, 13, 5,  28, 20, 12, 4}
};

const char PC_2[8][6] = {
        {14, 17, 11, 24, 1,  5},
        {3,  28, 15, 6,  21, 10},
        {23, 19, 12, 4,  26, 8},
        {16, 7,  27, 20, 13, 2},
        {41, 52, 31, 37, 47, 55},
        {30, 40, 51, 45, 33, 48},
        {44, 49, 39, 56, 34, 53},
        {46, 42, 50, 36, 29, 32}
};

const int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

char keys[16][48];


void fill_LR() {
    for (int i = 0; i < 32; i++) {
        L[i] = IP_M[i];
        R[i] = IP_M[i + 32];
    }
}

void encode() {
    fill_LR();
    printf("L: %s\n", L);
    printf("R: %s\n", R);
}

char *start_inital_permutation(const char *input) {
    char *output = malloc(64 * sizeof(char));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            output[i * 8 + j] = input[IP[i][j] - 1];
        }
    }
    return output;
}

void fill_subkeys(char *c, char *d, int j) {
    char permuted_subkey[48];
    strcat(permuted_subkey, c);
    strcat(permuted_subkey, d);
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 6; ++k) {
            keys[j][i * 6 + k] = permuted_subkey[PC_2[i][k] - 1];
        }
    }
    printf("Permutated subkey[%d]:\t %s (%lu bit)\n", j, keys[j], strlen(keys[j]));
}


void fill_CD() {
    for (int i = 0; i < strlen(PERMUTED_KEY) / 2; i++) {
        C[i] = PERMUTED_KEY[i];
        D[i] = PERMUTED_KEY[i + strlen(PERMUTED_KEY) / 2];
    }
}

void apply_shift_and_permute() {
    fill_CD();
    for (int j = 1; j <= 16; j++) {
        char temp0[28];
        char temp1[28];
        memcpy(temp0, C, 28);
        memcpy(temp1, D, 28);
        int shift = shifts[j - 1];
        while (shift > 0) {
            char temp_char0 = temp0[0];
            char temp_char1 = temp1[0];
            for (int i = 0; i < 28; ++i) {
                temp0[i] = temp0[i + 1];
                temp1[i] = temp1[i + 1];
            }
            temp0[27] = temp_char0;
            temp1[27] = temp_char1;
            shift--;
        }
        memcpy(C, temp0, 28);
        memcpy(D, temp1, 28);
        printf("C[%d]: \t\t\t\t\t %s (%lu bit)\n", j, C, strlen(C));
        printf("D[%d]: \t\t\t\t\t %s (%lu bit)\n", j, D, strlen(D));
        fill_subkeys(C, D, j);
    }
}

void generate_permuted_key(const char *binary_key) {
    char *permuted_key = malloc(sizeof(char) * 56);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++) {
            permuted_key[i * 7 + j] = binary_key[PC_1[i][j] - 1];
        }
    }
    // Because of the last char, we need to remove it
    permuted_key[56] = '\0';
    PERMUTED_KEY = permuted_key;
}

void set_key(char *key) {
    BINARY_KEY = to_bit_string(key);
    printf("Generated KEY:\t\t\t %s (%lu bit)\n", BINARY_KEY, strlen(BINARY_KEY));
    generate_permuted_key(BINARY_KEY);
    printf("\nPermuted KEY:\t\t\t %s (%lu bit)\n", PERMUTED_KEY, strlen(PERMUTED_KEY));
}

void init_des(char *input, char *key) {
    M = to_bit_string(input);
    printf("Message in bit:\t\t\t %s\n", M);
    set_key(key);
    apply_shift_and_permute();
    IP_M = start_inital_permutation(M);
    printf("Initial Permutation: \t %s (%lu bit)\n", IP_M, strlen(IP_M));
    encode();
}