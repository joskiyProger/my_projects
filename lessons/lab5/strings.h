#include <stdio.h>
#include <stdlib.h>

#define MAX_PATH 260

int slen(char *str);
char * stok(char *str, char *sep);
int sspn(char *str, char *find);
int scmp(char *str, char *match);
char *scpy(char *str);
int check_URL(char * str);