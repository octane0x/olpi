#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "banner.h"
#include "colors.h"

void clear_stdin(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int read_int(const char *prompt, int *out){
    printf("%s", prompt);
    if (scanf("%d", out) != 1) {
        clear_stdin();
        return 0;
    }
    clear_stdin();
    return 1;
}

void list_processes(void){
    DIR *dir;
    struct dirent *entry;
    dir = opendir("/proc");
    if (dir == NULL) {
        perror(C_RED "[!] opendir" C_RESET);
        return;
    }
    printf(C_CYAN "\nPID\tNAME\n" C_RESET);
    printf(C_GRAY "----------------\n" C_RESET);
    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            char path[64], name[256];
            snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
            FILE *f = fopen(path, "r");
            if (f) {
                fgets(name, sizeof(name), f);
                name[strcspn(name, "\n")] = 0;
                fclose(f);
                printf(C_WHITE "%s\t%s\n" C_RESET, entry->d_name, name);
            }
        }
    }
    closedir(dir);
}

void attach_process(void){
    int pid;
    int status;
    if (!read_int(C_CYAN "\nEnter target PID: " C_RESET, &pid)) {
        printf(C_RED "[!] PID must be a number, run option [1] to check for processes' PID\n\n" C_RESET);
        return;
    }
    if (pid <= 0) {
        printf(C_RED "[!] PID must be a positive number, maybe you added - unintentionally\n\n" C_RESET);
        return;
    }
    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
        printf(C_RED "[!] Failed to attach to PID %d: %s\n\n" C_RESET,
               pid, strerror(errno));
        return;
    }
    if (waitpid(pid, &status, 0) == -1) {
        printf(C_RED "[!] waitpid failed: %s\n\n" C_RESET, strerror(errno));
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return;
    }
    printf(C_GREEN "[+] Successfully attached to PID %d\n" C_RESET, pid);
    if (ptrace(PTRACE_DETACH, pid, NULL, NULL) == -1) {
        printf(C_RED "[!] Couldn't detach from PID %d: %s\n\n" C_RESET,
               pid, strerror(errno));
        return;
    }
    printf(C_GREEN "[+] Detached from PID %d\n\n" C_RESET, pid);
}

int main(void){
    int option;

    print_banner();
    while (1) {
        printf(C_YELLOW "[1] List processes\n" C_RESET);
        printf(C_YELLOW "[2] Attach to process\n" C_RESET);
        printf(C_YELLOW "[3] Inspect process\n" C_RESET);
        printf(C_YELLOW "[4] Exit\n" C_RESET);
        printf(C_CYAN "\nolpi > " C_RESET);
        if (!read_int("", &option)) {
            printf(C_RED "[!] Invalid input, please enter a number\n\n" C_RESET);
            continue;
        }
        switch (option) {
            case 1:
                list_processes();
                break;
            case 2:
                attach_process();
                break;
            case 3:
                printf(C_YELLOW "\n[+] Process inspection coming soon...\n\n" C_RESET);
                break;
            case 4:
                printf(C_GREEN "[*] Exiting...\n" C_RESET);
                return 0;
            default:
                printf(C_RED "[!] Invalid option\n\n" C_RESET);
        }
    }
    return 0;
}