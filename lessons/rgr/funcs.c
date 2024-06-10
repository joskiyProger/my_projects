#include "funcs.h"

char * read_file(int argc, char* argv[])
{
    char* buf = malloc(sizeof(char) * BUFSIZ);
    FILE* file = fopen(argv[argc], "r");
    unsigned int i = 1, ch = 0;
    
    while ((ch = getc(file)) != EOF) 
    {
        buf = realloc(buf, sizeof(char) * i);
        buf[i - 1] = ch;
        i++;
    }
    return buf;
}

int translate(char * word_to_translate, char * dictionary, FILE * file_name) {
    
    char * word = (char*) malloc(sizeof(char));
    
    word = dictionary;
    word = strtok(word, "\n \t");
    
    int i = 0;
    for (int word_counter = 0; word != NULL ; word_counter++) {
        
        if (!strcmp(word_to_translate, word)) {
            // printf(" %d\n", i);
            while (dictionary[i] != '-') {
                // printf("!!!!%c\n", dictionary[i]);
                i++;
            }
            for (i++; dictionary[i]!='\n' && i<strlen(dictionary); i++) {
                
                fputc(dictionary[i], file_name);
            }
            return 0;
        }
        while (dictionary[i] != '\n' && i<strlen(dictionary))
            i++;
        word = strtok(NULL, "\n \t");
        
    }
    return 1;
}