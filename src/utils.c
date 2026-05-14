#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/utils.h"

void removeNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void getStringInput(char *buffer, int size) {
    fgets(buffer, size, stdin);
    removeNewline(buffer);
}

int getIntInput() {
    char buffer[50];
    getStringInput(buffer, sizeof(buffer));
    return atoi(buffer);
}

double getDoubleInput() {
    char buffer[50];
    getStringInput(buffer, sizeof(buffer));
    return atof(buffer);
}

void getCurrentTime(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", 
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void logAction(const char *action) {
    FILE *fp = fopen("data/logs.txt", "a");
    if (fp) {
        char timeBuf[50];
        getCurrentTime(timeBuf);
        fprintf(fp, "[%s] %s\n", timeBuf, action);
        fclose(fp);
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    printf("\nPress Enter to continue...");
    char temp[10];
    fgets(temp, sizeof(temp), stdin);
}