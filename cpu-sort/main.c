#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int pid;
    double utime;
} procinfo;

int cmp(const void *a, const void *b) {
    procinfo *x = (procinfo *)a, *y = (procinfo *)b;
    return (y->utime - x->utime);
}

int main() {
    DIR *d = opendir("/proc");
    if (!d) { perror("opendir"); return 1; }

    procinfo list[1024];
    int n = 0;

    struct dirent *ent;
    while ((ent = readdir(d))) {
        if (!isdigit(ent->d_name[0])) continue;

        char path[256];
        snprintf(path, sizeof(path), "/proc/%s/stat", ent->d_name);
        FILE *f = fopen(path, "r");
        if (!f) continue;

        int pid; char comm[64]; char state;
        unsigned long utime;
        fscanf(f, "%d %s %c", &pid, comm, &state);
        for (int i = 0; i < 10; i++) fscanf(f, "%*s");
        fscanf(f, "%lu", &utime);
        fclose(f);

        list[n].pid = pid;
        list[n].utime = utime;
        n++;
    }
    closedir(d);

    qsort(list, n, sizeof(procinfo), cmp);

    for (int i = 0; i < n && i < 10; i++) {
        printf("PID %d CPU %f\n", list[i].pid, list[i].utime);
    }
}
