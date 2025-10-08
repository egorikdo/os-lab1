#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int run_command(char *cmd) {
    char *args[64];
    int argc = 0;
    char *token = strtok(cmd, " \t\n");
    while (token && argc < 63) {
        args[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[argc] = NULL;
    if (argc == 0) return 0;

    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(127);
    }
    int status;
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
}

int main() {
    char line[256];
    while (printf("$ "), fflush(stdout), fgets(line, sizeof(line), stdin)) {
        char *cmd1 = strtok(line, "|");
        char *cmd2 = strtok(NULL, "|");

        if (cmd2 && cmd2[0] == '|') cmd2++; // убрать второй |

        if (!cmd2) {
            run_command(cmd1);
        } else {
            int st = run_command(cmd1);
            if (st != 0) run_command(cmd2);
        }
    }
}
