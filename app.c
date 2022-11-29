#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.c"

char USED_WORDS[1024][64] = { "salom" };
int length = 1;

int is_used(char word[]) { 
  Lower(word);
  for (int i = 0; i < length; i++) {
    if (!strcmp(USED_WORDS[i], word)) {
      return 1;
    }
  }
  return 0;
}

int get_new_word(char letter, char pword[]) {
  FILE *file = fopen("database/words.txt", "r");
  char word[64];
  while(fscanf(file, "%s", word) != EOF) {
    if (letter == word[0] && !is_used(word)) {
      strcpy(pword, word);
      fclose(file);
      return 1;
    }
  }
  fclose(file);
  return 0;
}

int check_and_add_word_from_database(char new_word[]) {
  FILE *file = fopen("database/words.txt", "r");
  FILE *file_append = fopen("database/words.txt", "a");
  char word[64];

  Lower(new_word);
  while (fscanf(file, "%s", word) != EOF) {
    if (!strcmp(word, new_word)) {
      fclose(file);
      fclose(file_append);
      return 0;
    }
  }

  fprintf(file_append, "%s\n", new_word);
  fclose(file);
  fclose(file_append);
  return 1;
}

int add_used_word(char word[]) {
  strcpy(USED_WORDS[length++], word);
  return 1;
}

int main() {
  system("cls");
  char random_word[64] = { "hello" };
  char gamer_word[64];

  
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