#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file> <search> <replace>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) { perror("open"); return 1; }

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = malloc(sz+1);
    fread(buf, 1, sz, f);
    buf[sz] = 0;
    fclose(f);

    char *out = malloc(sz*2);
    out[0] = 0;

    char *pos = buf;
    while (1) {
        char *p = strstr(pos, argv[2]);
        if (!p) {
            strcat(out, pos);
            break;
        }
        strncat(out, pos, p-pos);
        strcat(out, argv[3]);
        pos = p + strlen(argv[2]);
    }

    f = fopen(argv[1], "w");
    fputs(out, f);
    fclose(f);

    free(buf); free(out);
}
