#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/mman.h>

int createFile(char *name) {
    FILE *fd = fopen(name, "w");
    if (fd == NULL) {
        printf("File open failed!\n");
        return 0;
    }
    fputs("gav-gav", fd);
    fclose(fd);
    return 1;
}

char *getFileName(int i, int temp) {
    char *filename = malloc(sizeof("100"));
    if (temp) {
        sprintf(filename, "temp/%03d", i);
    } else {
        sprintf(filename, "%03d", i);
    }
    return filename;
}

int main(int argc, char *argv[]) {
    char *directory_name = "temp";

    printf("Ищем в папке: %s\n", directory_name);

    DIR *dir = opendir(directory_name);

    if (dir != NULL) {
        system("rm -r temp");
    }

    system("mkdir temp");

    char *firstName = getFileName(0, 0);
    if (!createFile(firstName)) {
        free(firstName);
        printf("Ошибка открытия файла!\n");
        exit(1);
    }

    free(firstName);

    int len = 0;

    for (;;) {
        char *fileName = getFileName(len, 1);
        char *nextFileName = getFileName(len + 1, 0);
        if (symlink(fileName, nextFileName)) {
            free(fileName);
            free(nextFileName);
            printf("Symlink error\n");
            printf("Глубина рекурсии: %d\n", len);
            exit(-1);
        }
        FILE *nextFile = fopen(nextFileName, "r");
        if (nextFile == NULL) {
            printf("Глубина рекурсии: %d\n", len);
            free(fileName);
            free(nextFileName);
            exit(1);
        }
        fclose(nextFile);
        free(fileName);
        free(nextFileName);
        len++;
    }

    if (closedir(dir) != 0) {
        printf("Ошибка закрытия директории!\n");
        return (-1);
    }

    return 0;
}

