#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

enum {
    MaxCodeLength = 4
};

typedef struct {
    uint8_t code[MaxCodeLength];
    size_t length;
} CodeUnits;

uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90)
    {
        return r % 128;
    }
    if (p < 95)
    {
        return r % 16384;
    }
    if (p < 99)
    {
        return r % 2097152;
    }
    return r % 268435455;
}

int encode(uint32_t code_point, CodeUnits *code_units) {
    if (code_point <= 0x7F) { // 0xxxxxxx
        code_units->code[0] = (uint8_t)code_point;
        code_units->length = 1;
    }
    else if(code_point <= 0x7FF) { // 110xxxxx 10xxxxxx
        code_units->code[0] = (uint8_t)(0b11000000 | (code_point >> 6));
        code_units->code[1] = (uint8_t)(0b10000000 | (code_point & 0b00111111));
        code_units->length = 2;
    }
    else if(code_point <= 0xFFFF) { // 1110xxxx 10xxxxxx 10xxxxxx
        code_units->code[0] = (uint8_t)(0b11100000 | (code_point >> 12));
        code_units->code[1] = (uint8_t)(0b10000000 | ((code_point >> 6) & 0b00111111 ));
        code_units->code[2] = (uint8_t)(0b10000000 | (code_point & 0b00111111));
        code_units->length = 3;
    } 
    else if (code_point <= 0x1FFFFF) { // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        code_units->code[0] = (uint8_t)(0b11110000 | (code_point >> 18));
        code_units->code[1] = (uint8_t)(0b10000000 | ((code_point >> 12) & 0b00111111 ));
        code_units->code[2] = (uint8_t)(0b10000000 | ((code_point >> 6) & 0b00111111 ));
        code_units->code[3] = (uint8_t)(0b10000000 | (code_point & 0b00111111));
        code_units->length = 4;
    } 
    else {
        return -1;
    }
    return 0;
}

int write_code_unit(FILE *out, const CodeUnits *code_unit) 
{
    if (fwrite(code_unit->code, sizeof(uint8_t), code_unit->length, out) != code_unit->length) 
    {
        return -1;
    }
    return 0;
}

int encode_file(const char *in_file_name, const char *out_file_name) {
    FILE* file_in = fopen(in_file_name, "r");
    FILE* file_out = fopen(out_file_name, "wb");
    if (!file_in || !file_out) 
    {
        fprintf(stderr, "Error opening file\n");
        return -1;
    }
    uint32_t code_point;
    CodeUnits code_units;
    while(fscanf(file_in, "%" SCNx32, &code_point) == 1) {
        encode(code_point, &code_units);
        write_code_unit(file_out, &code_units);
    }
    return 0;
}

uint32_t decode(const CodeUnits *code_units) {
    uint32_t code_point = 0;
    if (code_units->code[0] <= 0x7F) { // 0xxxxxxx
        code_point = (uint8_t)code_units->code[0];
    }
    else if(code_units->code[0] <= 0xDF) { // 110xxxxx 10xxxxxx
        code_point = (uint8_t)((0b00011111 & code_units->code[0]));
        code_point <<= 6;
        code_point |= (uint8_t)(0b00111111 & code_units->code[1]);
    }
    else if(code_units->code[0] <= 0xEF) { // 1110xxxx 10xxxxxx 10xxxxxx
        code_point = (uint8_t)(0b00001111 & code_units->code[0]);
        code_point <<= 6;
        code_point |= (uint8_t)(0b00111111 & code_units->code[1]);
        code_point <<= 6;
        code_point |= (uint8_t)(0b00111111 & code_units->code[2]);
    } 
    else if (code_units->code[0] <= 0xF7) { // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        code_point = (uint8_t)(0b00000111 & code_units->code[0]);
        code_point <<= 6;
        code_point |= (uint8_t)(0b00111111 & code_units->code[1]);
        code_point <<= 6;
        code_point |= (uint8_t)(0b00111111 & code_units->code[2]);
        code_point <<= 6;
        code_point |= (uint8_t)(0b00111111 & code_units->code[3]);
    } 
    else {
        return -1;
    }
    return code_point;
}

int read_next_code_unit(FILE *in, CodeUnits *code_units) {
    uint8_t byte;
    if(fread(&byte, sizeof(uint8_t), 1, in) == 1)
    {
        code_units->code[0] = byte;
        if(byte <= 127)
        {
            code_units->length = 1;
        }
        else if(byte >= 191 && byte <= 223)
        {
            code_units->length = 2;
        }
        else if(byte >= 224 && byte <= 239)
        {
            code_units->length = 3;
        }
        else
        {
            code_units->length = 4;
        }
    }
    for(size_t len = 1; len < code_units->length; len++)
    {
        fread(&byte, sizeof(uint8_t), 1, in);
        code_units->code[len] = byte;
    }
    if (feof(in)) 
    {
        return EOF;
    }
    return 0; 
}

int decode_file(const char *in_file_name, const char *out_file_name) {
    FILE *file_in = fopen(in_file_name, "rb");
    FILE *file_out = fopen(out_file_name, "w");

    if (!file_in || !file_out) 
    {
        fprintf(stderr, "Error opening file\n");
        return -1;
    }

    CodeUnits code_units;
    uint32_t code_point;

    while (read_next_code_unit(file_in, &code_units) != EOF) 
    {
        code_point = decode(&code_units);
        fprintf(file_out, "%" PRIx32 "\n", code_point);
    }

    fclose(file_in);
    fclose(file_out);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4 && strcmp(argv[1], "encode") == 0) {
        encode_file(argv[2], argv[3]);
    }
    else if (argc == 4 && strcmp(argv[1], "decode") == 0) {
        decode_file(argv[2], argv[3]);
    }
    return 0;
}