#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "des.h"
#include "utility.h"
#include "fileManagement.h"

int main() {

    char *key = "133457799BBCDFF1";
    char *messageC = malloc(sizeof(char) * 33);
    char *output = malloc(sizeof(char) * 33);

    printf("Scegliere opzione:\n");
    printf("1. Cifrare da file\n");
    printf("2. Cifrare da console\n");
    int choice;
    int selectedFile = 0;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Inserire il nome del file da cifrare: \n");
        char *fileName = malloc(sizeof(char) * 100);
        scanf(" %s", fileName);
        fileName[strlen(fileName)] = '\0';
        readFile(fileName, output);
        printf("Contenuto file: %s\n", output);
        messageC = output;
        free(fileName);
        selectedFile = 1;
    } else if (choice == 2) {
        printf("Inserire il messaggio da crittare: ");
        scanf(" %[^\n]s", messageC);
    }
    // Traduzione del messaggio in esadecimale e divisione in blocchi qualora sia più lungo di 8 caratteri



    char *mallocM;

    messageC[strlen(messageC)] = '\0';
    printf("Messaggio Letto: %s\n", messageC);
    int size = (int) strlen(messageC);
    int i = 0;
    char *messageHex;
    char *cyperText = malloc(sizeof(char) * 33);
    printf("Size: %d\n", size);
    do {
        mallocM = cut(messageC, i * 8, (i + 1) * 8 - 1);
        mallocM[8] = '\0';
        messageHex = message_to_hex(mallocM);
        char *temp = init_des(messageHex, key);
        printf("Generated: %s\n", temp);
        strcat(cyperText, temp);
        size = size - 8;
        i++;
    } while (size > 0);
    cyperText[strlen(cyperText) + 1] = '\0';
    cyperText = cut(cyperText, 2, strlen(cyperText) - 1);

    if (selectedFile == 1) {
        cyperText = cut(cyperText, 3, strlen(cyperText) - 1);
        printf("Cifrato: %s\n", cyperText);
    } else {
        printf("CyperText: %s\n", cyperText);
    }

    // To UPPER
    for (int j = 0; j < strlen(cyperText); j++) {
        cyperText[j] = toupper(cyperText[j]);
    }



    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("DES - Algorithm Development and Implementation\n");
    printf("--------------------------------------------\n");
    printf("Message to encode: %s\n", messageC);
    printf("Key: %s\n", key);
    printf("Encoded Message: %s\n", cyperText);
    printf("--------------------------------------------\n");
    printf("Desidera salvare l'output su file?\n");
    printf("1. Si\n");
    printf("2. No\n");
    choice = 0;
    scanf("%d", &choice);
    if (choice == 1) {
        FILE *file = fopen("output.txt", "ab+");
        fprintf(file, "%s", cyperText);
        fclose(file);
    }
    exit(1);
    return 0;

}
