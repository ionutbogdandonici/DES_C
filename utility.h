//
// Created by Bogdan on 08/07/2022.
//

#ifndef DES_OFFICIAL_UTILITY_H
#define DES_OFFICIAL_UTILITY_H

char * message_to_hex(char *message);

int bit_to_hex(char *binaryval);

char *cut(const char *input, int start, int end);

int toIntFromBitString(char *input);

char *toBitStringFromInt(int input);

char *to_bit_string(char *input);

#endif //DES_OFFICIAL_UTILITY_H
