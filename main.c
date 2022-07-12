#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include "des.h"
#include "utility.h"

int main() {

    char *key = "133457799BBCDFF1";

    printf("Inserire il messaggio da crittare: ");
    char *messageC = malloc(sizeof(char) * 33);
    scanf("%[^\n]s", messageC);

    // Traduzione del messaggio in esadecimale e divisione in blocchi qualora sia più lungo di 8 caratteri
    char *mallocM;
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
    return 0;
}
