//
// Created by Bogdan on 08/07/2022.
//

#ifndef DES_OFFICIAL_DES_H
#define DES_OFFICIAL_DES_H

void fill_CD();

void apply_shift_and_permute();

void generate_permuted_key(const char *binary_key);
// Metodo che imposta la chiave di cifratura
void set_key(char *key);

void init_des(char *input, char *key);

#endif //DES_OFFICIAL_DES_H
