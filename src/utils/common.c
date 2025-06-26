#include "common.h"

void handleError(char *message) {
  fprintf(stderr, COLOR_RED "Error: %s\n" COLOR_RESET, message);
}

void printSeparator(char *title) {
  printf(COLOR_BLUE "\n%s\n" COLOR_RESET, title);
}

double getTimeDiff(time_t start, time_t end) {
  return (double)(end - start) / CLOCKS_PER_SEC;
}
