#ifndef UTILS_H
#define UTILS_H

void removeNewline(char *str);
void getStringInput(char *buffer, int size);
int getIntInput();
double getDoubleInput();
void logAction(const char *action);
void getCurrentTime(char *buffer);
void clearScreen();
void pauseScreen();

#endif