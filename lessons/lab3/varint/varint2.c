#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

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

size_t encode_varint(uint32_t value, uint8_t *buf)
{
    assert(buf != NULL);
    uint8_t *cur = buf;
    while (value >= 0x80)
    {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}

uint32_t decode_varint(uint8_t **bufp)
{
    uint8_t *cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80)
    {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

int main()
{
    FILE *uncompressed_file = fopen("uncompressed.dat", "wb");
    FILE *compressed_file = fopen("compressed.dat", "wb");

    if (uncompressed_file == NULL || compressed_file == NULL) 
    {
        perror("Unable to open file");
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    uint8_t *buffer = malloc(5);
    for (int i = 0; i < 1000000; ++i) 
    {
        uint32_t number = generate_number();
        fwrite(&number, sizeof(uint32_t), 1, uncompressed_file);
        encode_varint(number, buffer);
        
        if(buffer[0] == 0)
        {
            fwrite(&buffer[0], sizeof(uint8_t), 1, compressed_file);
        }
        for (int numb_byte = 0; numb_byte < 5; numb_byte++)
        {
            if (buffer[numb_byte] != 0)
            {
                fwrite(&buffer[numb_byte], sizeof(uint8_t), 1, compressed_file);
            }
            buffer[numb_byte] = 0;
        }
    }

    fclose(uncompressed_file);
    fclose(compressed_file);

    uncompressed_file = fopen("uncompressed.dat", "rb");
    compressed_file = fopen("compressed.dat", "rb");

    if (uncompressed_file == NULL || compressed_file == NULL) 
    {
        perror("Unable to open file");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 1000000; ++i) 
    {
        uint32_t uncompressed_number, compressed_number;
        uint8_t *decode_buffer = malloc(5);
        fread(&uncompressed_number, sizeof(uint32_t), 1, uncompressed_file);
        for(int i = 0; i < 5; i++)
        {
            decode_buffer[i] = 0;
        }
        fread(&decode_buffer[0], sizeof(uint8_t), 1, compressed_file);
        for(int numb_var = 0; decode_buffer[numb_var] > 127 && numb_var < 5;)
        {
            fread(&decode_buffer[numb_var + 1], sizeof(uint8_t), 1, compressed_file);
            numb_var++;
        }
        compressed_number = decode_varint(&decode_buffer);
        if (uncompressed_number != compressed_number) 
        {
            printf("Error: The sequence of numbers does not match!\n");
            return EXIT_FAILURE;
        }
    }

    fclose(uncompressed_file);
    fclose(compressed_file);

    return EXIT_SUCCESS;
}
