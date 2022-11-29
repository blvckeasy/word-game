#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.c"

int main() {
  system("cls");
  char random_word[64];
  char gamer_word[64];
  random_word_generate(random_word);
  
  while(1) {
      
    printf("random so'z = %s\n", random_word);

    printf("so'z kiriting: ");
    scanf("%s", gamer_word);

    if (is_used(gamer_word) || gamer_word[0] != random_word[strlen(random_word) - 1]) {
      check_and_add_word_from_database(gamer_word);
      printf("Yutqazingiz.");
      break;
    }
    add_used_word(gamer_word);

    if (get_new_word(gamer_word[strlen(gamer_word) - 1], random_word)) {
      add_used_word(random_word);
      check_and_add_word_from_database(gamer_word);
    } else {
      check_and_add_word_from_database(gamer_word);
      printf("Yuttingiz.");
      break;
    }
  }

  return 0;
}