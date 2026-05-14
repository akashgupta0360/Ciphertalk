#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void caesar_encrypt(char *text, int shift);
void caesar_decrypt(char *text, int shift);
#define MAX_BODY 4096
static void url_decode(char *s) {
    char *r = s, *w = s;
    while (*r) {
        if (*r == '+') { *w++ = ' '; r++; }
        else if (*r == '%' && r[1] && r[2]) {
            char hex[3] = { r[1], r[2], 0 };
            *w++ = (char) strtol(hex, NULL, 16);
            r += 3;
        } else {
            *w++ = *r++;
        }
    }
    *w = '\0';
}
static char *find_field(char *body, const char *key) {
    size_t klen = strlen(key);
    char *p = body;
    while (p && *p) {
        if (strncmp(p, key, klen) == 0 && p[klen] == '=') {
            char *val = p + klen + 1;
            char *amp = strchr(val, '&');
            if (amp) *amp = '\0';
            return val;
        }
        p = strchr(p, '&');
        if (p) p++;
    }
    return NULL;
}
int main(void) {
    char body[MAX_BODY + 1] = {0};
    const char *clen_s = getenv("CONTENT_LENGTH");
    int clen = clen_s ? atoi(clen_s) : 0;
    if (clen > MAX_BODY) clen = MAX_BODY;
    if (clen > 0) fread(body, 1, (size_t) clen, stdin);
    body[clen] = '\0';
    char *mode  = find_field(body, "mode");
    char *shift = find_field(body, "shift");
    char *text  = find_field(body, "text");
    printf("Content-Type: text/plain; charset=utf-8\r\n\r\n");
    if (!mode || !text) {
        printf("ERROR: missing 'mode' or 'text' field.\n");
        return 0;
    }
    url_decode(mode);
    url_decode(text);
    int s = shift ? atoi(shift) : 3;
    if (strcmp(mode, "encrypt") == 0)      caesar_encrypt(text, s);
    else if (strcmp(mode, "decrypt") == 0) caesar_decrypt(text, s);
    else { printf("ERROR: mode must be 'encrypt' or 'decrypt'.\n"); return 0; }
    printf("%s\n", text);
    return 0;
}
