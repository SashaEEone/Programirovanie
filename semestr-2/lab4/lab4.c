#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Используйте файл\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
    perror("Error opening file");
    exit(1);
    }

    printf("%-23s | %-10s | %-10s\n", "ФИО", "ID", "Уровень");
    printf("------------------------------------------------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, ";");
        char *id = strtok(NULL, ";");
        char *level = strtok(NULL, ";");

        if (name && id && level) {
            printf("%-20s | %-10s | %-10s\n", name, id, level);
        }
    }

    fclose(file);
    return 0;
}
