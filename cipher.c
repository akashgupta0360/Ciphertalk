#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
static int normalize_shift(int shift) {
    int s = shift % 26;
    if (s < 0) s += 26;
    return s;
}
void caesar_apply(char *text, int shift) {
    int s = normalize_shift(shift);
    for (size_t i = 0; text[i] != '\0'; i++) {
        unsigned char ch = (unsigned char) text[i];
        if (ch >= 'A' && ch <= 'Z') {
            text[i] = (char) (((ch - 'A' + s) % 26) + 'A');
        } else if (ch >= 'a' && ch <= 'z') {
            text[i] = (char) (((ch - 'a' + s) % 26) + 'a');
        }
    }
}
void caesar_encrypt(char *text, int shift) { caesar_apply(text, shift); }
void caesar_decrypt(char *text, int shift) { caesar_apply(text, -shift); }
#ifndef CIPHER_NO_MAIN
int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <encrypt|decrypt> <shift> <text>\n", argv[0]);
        return 1;
    }
    const char *mode = argv[1];
    int shift = atoi(argv[2]);
    size_t len = strlen(argv[3]);
    char *buf = (char *) malloc(len + 1);
    if (!buf) { fprintf(stderr, "out of memory\n"); return 2; }
    memcpy(buf, argv[3], len + 1);
    if (strcmp(mode, "encrypt") == 0) {
        caesar_encrypt(buf, shift);
    } else if (strcmp(mode, "decrypt") == 0) {
        caesar_decrypt(buf, shift);
    } else {
        fprintf(stderr, "Unknown mode: %s\n", mode);
        free(buf);
        return 1;
    }
    printf("%s\n", buf);
    free(buf);
    return 0;
}
