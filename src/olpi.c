#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include "banner.h"
#include "menu.h"

void list_processes(void)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    printf("\nPID\tNAME\n");
    printf("----------------\n");

    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            char path[64], name[256];
            snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
            FILE *f = fopen(path, "r");
            if (f) {
                fgets(name, sizeof(name), f);
                name[strcspn(name, "\n")] = 0;
                fclose(f);
                printf("%s\t%s\n", entry->d_name, name);
            }
        }
    }

    closedir(dir);
}

int main(void)
{
    int option;

    print_banner();

    while (1) {
        printf("[1] List processes\n");
        printf("[2] Attach to process\n");
        printf("[3] Inspect process\n");
        printf("[4] Exit\n");
        printf("\nolpi > ");

        scanf("%d", &option);

        switch (option) {
            case 1:
                list_processes();
                break;

            case 2:
                printf("\n[+] Process attach coming soon...\n\n");
                break;

            case 3:
                printf("\n[+] Process inspection coming soon...\n\n");
                break;

            case 4:
                printf("[*] Exiting...\n");
                return 0;

            default:
                printf("[!] Invalid option\n\n");
        }
    }
    return 0;
}
