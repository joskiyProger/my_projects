#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <locale.h>

char * read_file(int argc, char* argv[]);
int translate(char * word_to_translate, char * dictionary, FILE * file_name);