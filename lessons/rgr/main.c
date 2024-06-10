#include "funcs.h"

int main(int argc, char * argv[]) {
    if (argc != 4) {
        return 1;
    }
    char * text = read_file(3, argv);
    char * dictionary = read_file(2, argv);
    FILE* translated = fopen(argv[1], "w, ccs=UTF-8");
    char * word = (char*) malloc(sizeof(char));
    int letter_in_word = 0, last_word_index = 0;
    for (int i = 0; i<strlen(text) ; i++) {
        if (!isblank(text[i]) || text[i] == '\n') {
            word = (char*) realloc(word, sizeof(char) * letter_in_word+1);
            word[letter_in_word] = text[i];
            letter_in_word++;
            word[letter_in_word] = '\0';
        }
        else {
            // printf("!%s\n", dictionary);
            if (translate(word, dictionary, translated)) {
                int j = last_word_index;
                for (; (!isblank(text[j]) || text[j]!='\n') &&  j<strlen(text); j++) {
                    fputc(text[j], translated);
                }
                i = j;
            }
            word[0] = '\0';
            letter_in_word = 0;
            last_word_index = i;
        }
    }
    fprintf(translated, "%s", word);
    free(word);
    fclose(translated);
}