#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char USED_WORDS[1024][64] = { "salom" };
int length = 1;

int Lower(char sery[]) {
  for (int i = 0; i < strlen(sery); i++) {
    sery[i] = tolower(sery[i]);
  }
}

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
  srand(time(0));
  char found_words[1024][64];
  int found_words_index = 0;

  FILE *file = fopen("database/words.txt", "r");
  char word[64];
  while(fscanf(file, "%s", word) != EOF) {
    if (letter == word[0] && !is_used(word)) {
      strcpy(found_words[found_words_index++], word);
    }
  }

  fclose(file);
  if (found_words_index) {
    strcpy(pword, found_words[rand() % found_words_index]);
    return 1;
  }

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

void random_word_generate(char rand_word[]) {
  srand(time(0));
  FILE *file = fopen("database/words.txt", "r");
  char word[64];
  int count = 0;

  while (fscanf(file, "%s", word) != EOF) {
    count++;
  }

  // printf("\ncount = %d\n",count);

  rewind(file);
  int random = rand() % (count);

  // printf("\ncount = %d\n",count);

  for(int i = 1; fscanf(file, "%s", word) != EOF; i++) {
    if (i == random) {
      strcpy(rand_word, word);
      break;
    }
  }
}