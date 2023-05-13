#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 100
#define MAX_LINE_LEN 1000

int count_chars(char *filename);
int count_words(char *filename);

int main(int argc, char *argv[]) {
    char filename[MAX_FILENAME_LEN];
    char *parameter;
    int count;

    // 获取参数和文件名
    if (argc == 2) {
        parameter = "-c";
        strcpy(filename, argv[1]);
    } else if (argc == 3) {
        parameter = argv[1];
        strcpy(filename, argv[2]);
    } else {
        printf("Usage: %s [-c | -w] [filename]\n", argv[0]);
        return 1;
    }

    // 根据参数调用不同的函数
    if (strcmp(parameter, "-c") == 0) {
        count = count_chars(filename);
        printf("字符数：%d\n", count);
    } else if (strcmp(parameter, "-w") == 0) {
        count = count_words(filename);
        printf("单词数：%d\n", count);
    } else {
        printf("Invalid parameter: %s\n", parameter);
        return 1;
    }

    return 0;
}

int count_chars(char *filename) {
    FILE *fp;
    char line[MAX_LINE_LEN];
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Cannot open file: %s\n", filename);
        exit(1);
    }

    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        count += strlen(line);
    }

    fclose(fp);

    return count;
}

int count_words(char *filename) {
    FILE *fp;
    char line[MAX_LINE_LEN];
    char *word;
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Cannot open file: %s\n", filename);
        exit(1);
    }

    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        word = strtok(line, " ,\n\t");
        while (word != NULL) {
            count++;
            word = strtok(NULL, " ,\n\t");
        }
    }

    fclose(fp);

    return count;
}

