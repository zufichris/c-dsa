#ifndef COMMON_H
#define COMMON_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1000
#define SUCCESS 1
#define FAILURE -1

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

void handleError(char *message);
void printSeparator(char *title);
double getTimeDiff(time_t start, time_t end);

#endif // !COMMON_H
