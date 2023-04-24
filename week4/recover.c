#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512

void get_filename(int counter, char curr_filename[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Image could not be opened\n");
        return 1;
    }

    BYTE buffer[512];
    char curr_filename[] = "000.jpg";
    FILE *currfile = NULL;

    int counter = 0;
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xF0) >> 4 == 0x0E)
        {
            get_filename(counter, curr_filename);
            //printf("%s, start of an image!! ", curr_filename);
            counter++;

            currfile = fopen(curr_filename, "w");
            fwrite(buffer, 1, BLOCK_SIZE, currfile);
            while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
            {
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xF0) >> 4 == 0x0E)
                {
                    fclose(currfile);
                    fseek(file, -BLOCK_SIZE, SEEK_CUR);
                    break;
                }
                fwrite(buffer, 1, BLOCK_SIZE, currfile);
            }
        }
    }
    fclose(currfile);
    fclose(file);
}

void get_filename(int counter, char arr[])
{
    char num[3];
    sprintf(num, "%d", counter);
    if (counter < 10)
    {
        arr[2] = num[0];
    }
    else
    {
        arr[1] = num[0];
        arr[2] = num[1];
    }
}
