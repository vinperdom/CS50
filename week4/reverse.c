#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("File could not be opened\n");
        return 1;
    }

    WAVHEADER header;
    fread(&header, 1, 44, file);

    bool is_wav = check_format(header);
    if (!is_wav)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    char *output = argv[2];
    FILE *outfile = fopen(output, "wb");

    if (outfile == NULL)
    {
        printf("File could not be generated\n");
        return 1;
    }

    fwrite(&header, 1, 44, outfile);

    int block_size = get_block_size(header);

    // Write reversed audio to file
    BYTE *buffer = malloc(sizeof(BYTE) * block_size);

    // get file size
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);

    int blocks_left = (file_size - 44) / block_size;
    fseek(file, -block_size, SEEK_CUR);


    for (int i = 0; i < blocks_left; i++)
    {
        fread(buffer, block_size, 1, file);
        fwrite(buffer, block_size, 1, outfile);
        fseek(file, -(block_size * 2), SEEK_CUR);
    }

    free(file);
    free(outfile);
    free(buffer);
}

int check_format(WAVHEADER header)
{
    char *format = malloc(4 * sizeof(char));
    for (int i = 0; i < 4; i++)
    {
        format[i] = header.format[i];
    }

    char *correct_format = "WAVE";
    bool is_wave = !strcmp(format, correct_format);
    free(format);
    return is_wave;
}

int get_block_size(WAVHEADER header)
{
    return (header.numChannels * header.bitsPerSample) / 8;
}
