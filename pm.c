#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 10

int main() {
    pid_t pids[NUM_CHILDREN];
    int i;

    // Tasks for each child process
    char *tasks[NUM_CHILDREN][3] = {
        {"echo", "Hello + Jesús", NULL},
        {"date", NULL},
        {"pwd", NULL},
        {"whoami", NULL},
        {"ls", NULL},
        {"du", NULL},
        {"uname", NULL},
        {"hostname", NULL},
        {"ps", NULL},
        {"uptime", NULL}

    };

    for (i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            // fork failure
            perror("fork");
            exit(EXIT_FAILURE);

        } 
        else if (pids[i] == 0) {
            // Child process
            printf("Child %d (PID: %d) is executing.\n", i + 1, getpid());

            execvp(tasks[i][0], tasks[i]);

            // execvp failure
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process
    for (i = 0; i < NUM_CHILDREN; i++) {
        int status;
        pid_t child_pid = wait(&status);

        if (WIFEXITED(status)) {
            printf("Child %d (PID: %d) exited normally with status %d.\n", i + 1, child_pid, WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)) {
            printf("Child %d (PID: %d) was terminated by signal %d.\n", i + 1, child_pid, WTERMSIG(status));
        }
    }

    printf("All child processes have completed.\n");
    return 0;

}