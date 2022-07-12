//
// Created by Bogdan on 08/07/2022.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "constants.h"
#include "utility.h"
#include "errorManagement.h"

const char *BINARY_KEY;
const char *PERMUTED_KEY;

char *M;
char *IP_M;
char C[28];
char D[28];

// One space more for the null character
char L[33];
char R[33];

char keys[16][49];

char *reverse_and_permute(char l[33], char r[33]) {
    char *toPermute = strcat(r, l);
    char *output = malloc(64);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            output[i * 8 + j] = toPermute[IP_1[i][j] - 1];
        }
    }
    return output;
}

char *xorBitString(char *input1, char *input2) {
    char *output = malloc(9);
    for (int i = 0; i < strlen(input1); ++i) {
        int value = (input1[i] - '0') + (input2[i] - '0');
        if (value == 2) {
            output[i] = '0';
        } else if (value == 1) {
            output[i] = '1';
        } else {
            output[i] = '0';
        }
    }
    return output;
}

char *applyFinalE(const char *input) {
    char *output = malloc(33);
    for (int i = 0; i < 32; i++) {
        output[i] = input[P[i] - 1];
    }
    output[32] = '\0';
    return output;
}

char *applyS1(const char *input) {
    char row[3] = {input[0], input[5], '\0'};
    char col[5] = {input[1], input[2], input[3], input[4], '\0'};
    int row_index = toIntFromBitString(row);
    int col_index = toIntFromBitString(col);
    return toBitStringFromInt(S1[row_index][col_index]);
}

char *applyS2(const char *input) {
    char row[3] = {input[0], input[5], '\0'};
    char col[5] = {input[1], input[2], input[3], input[4], '\0'};
    int row_index = toIntFromBitString(row);
    int col_index = toIntFromBitString(col);
    return toBitStringFromInt(S2[row_index][col_index]);
}

char *applyS3(const char *input) {
    char row[3] = {input[0], input[5], '\0'};
    char col[5] = {input[1], input[2], input[3], input[4], '\0'};
    int row_index = toIntFromBitString(row);
    int col_index = toIntFromBitString(col);
    return toBitStringFromInt(S3[row_index][col_index]);
}

char *applyS4(const char *input) {
    char row[3] = {input[0], input[5], '\0'};
    char col[5] = {input[1], input[2], input[3], input[4], '\0'};
    int row_index = toIntFromBitString(row);
    int col_index = toIntFromBitString(col);
    return toBitStringFromInt(S4[row_index][col_index]);
}

char *applyS5(const char *input) {
    char row[3] = {input[0], input[5], '\0'};
    char col[5] = {input[1], input[2], input[3], input[4], '\0'};
    int row_index = toIntFromBitString(row);
    int col_index = toIntFromBitString(col);
    return toBitStringFromInt(S5[row_index][col_index]);
}

char *applyS6(const char *input) {
    char row[3] = {input[0], input[5], '\0'};
    char col[5] = {input[1], input[2], input[3], input[4], '\0'};
    int row_index = toIntFromBitString(row);
    int col_index = toIntFromBitString(col);
    return toBitStringFromInt(S6[row_index][col_index]);
}

char *applyS7(const char *input) {
    char row[3] = {input[0], input[5], '\0'};
    char col[5] = {input[1], input[2], input[3], input[4], '\0'};
    int row_index = toIntFromBitString(row);
    int col_index = toIntFromBitString(col);
    return toBitStringFromInt(S7[row_index][col_index]);
}

char *applyS8(const char *input) {
    char row[3] = {input[0], input[5], '\0'};
    char col[5] = {input[1], input[2], input[3], input[4], '\0'};
    int row_index = toIntFromBitString(row);
    int col_index = toIntFromBitString(col);
    return toBitStringFromInt(S8[row_index][col_index]);
}


char *applySBox(char *input) {
    char *output = malloc(sizeof(char) * 48);
    strcat(output, applyS1(cut(input, 0, 5)));
    strcat(output, applyS2(cut(input, 6, 11)));
    strcat(output, applyS3(cut(input, 12, 17)));
    strcat(output, applyS4(cut(input, 18, 23)));
    strcat(output, applyS5(cut(input, 24, 29)));
    strcat(output, applyS6(cut(input, 30, 35)));
    strcat(output, applyS7(cut(input, 36, 41)));
    strcat(output, applyS8(cut(input, 42, 47)));
    output[48] = '\0';
    return output;
}

char *applyXOR(const char *input, const char *key) {
    char *output = malloc(sizeof(char) * 48);
    printf("XOR-I:\t\t\t\t\t %s\n", input);
    printf("XOR-K:\t\t\t\t\t %s\n", key);
    for (int i = 0; i <= 48; i++) {
        int in = input[i] - '0';
        output[i] = in ^ key[i];
    }
    output[48] = '\0';
    return output;
}

char *applyE_function(const char *input) {
    char *output = malloc(sizeof(char) * 48);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; ++j) {
            output[i * 6 + j] = input[E[i][j] - 1];
        }
    }
    if (strlen(output) > 48) {
        output[strlen(output) - 1] = '\0';
    } else {
        output[48] = '\0';
    }
    return output;
}

void fill_LR() {
    for (int i = 0; i < 32; i++) {
        L[i] = IP_M[i];
        R[i] = IP_M[i + 32];
    }
    L[32] = '\0';
    R[32] = '\0';
}

char *encode() {
    fill_LR();
    printf("L[0]:\t\t\t\t\t %s (%lu bit)\n", L, strlen(L));
    printf("R[0]:\t\t\t\t\t %s (%lu bit)\n", R, strlen(R));
    char L_n_1[33];
    for (int i = 1; i <= 16; i++) {
        strcpy(L_n_1, L);
        L_n_1[32] = '\0';
        strcpy(L, R);
        char *ER = applyE_function(R);
        char *XOR = applyXOR(ER, keys[i]);
        printf("KEY-[%d]:\t\t\t\t %s (%lu bit)\n", i, keys[i], strlen(keys[i]));
        printf("X[%d]:\t\t\t\t\t %s (%lu bit)\n", i, XOR, strlen(XOR));
        char *applyedSBOX = applySBox(XOR);
        strcpy(R, xorBitString(applyFinalE(applyedSBOX), L_n_1));
        printf("L[%d-1]:\t\t\t\t %s \n", i, L_n_1);
        printf("L[%d]:\t\t\t\t\t %s (%lu bit)\n", i, L, strlen(L));
        printf("f[%d]:\t\t\t\t\t %s\n", i, applyFinalE(applyedSBOX));
        printf("R[%d]:\t\t\t\t\t %s (%lu bit)\n", i, R, strlen(R));
        printf("-------------------------------------------\n");
    }
    char *toHex = reverse_and_permute(L, R);
    char *hexedL = cut(toHex, 0, 31);
    char *hexedR = cut(toHex, 32, 63);


    char *hexString = malloc(sizeof(char) * 33);
    sprintf(hexString, "%x", bit_to_hex(hexedL));
    char *hexString2 = malloc(sizeof(char) * 33);
    sprintf(hexString2, "%x", bit_to_hex(hexedR));
    strcat(hexString, hexString2);
    hexString[32] = '\0';
    return hexString;
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
    char permuted_subkey[49];
    strcat(permuted_subkey, c);
    strcat(permuted_subkey, d);
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 6; ++k) {
            keys[j][i * 6 + k] = permuted_subkey[PC_2[i][k] - 1];
        }
    }
    permuted_subkey[48] = '\0';
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

char *init_des(char *input, char *key) {
    printf("Validation: %s\n", validateMessage(input));
    M = to_bit_string(validateMessage(input));
    printf("Message in bit:\t\t\t %s\n", M);
    set_key(key);
    apply_shift_and_permute();
    IP_M = start_inital_permutation(M);
    printf("Initial Permutation: \t %s (%lu bit)\n", IP_M, strlen(IP_M));
    return encode();
}
