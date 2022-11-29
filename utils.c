#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int Lower(char sery[]) {
  for (int i = 0; i < strlen(sery); i++) {
    sery[i] = tolower(sery[i]);
  }
}