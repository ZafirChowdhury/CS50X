#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage : reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    char *infile = argv[1];


    //Open input file in "reading"-mode
    FILE *input = fopen(infile, "r");
    if (input == NULL)
    {
        printf("Incorrect input.\n");
        fclose(input);
        return 1;
    }

    // Read header
    //Read file-header from input
    WAVHEADER fheader;
    fread(&fheader, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(fheader) != 0)
    {
        fclose(input);
        return 1;
    }

    // Open output file for writing

    char *outfile = argv[2];

    FILE *output = fopen(outfile, "w");
    //Ensure a valid output file
    if (output == NULL)
    {
        printf("Output file unsuccesful");
        fclose(output);
        fclose(input);
        return 1;
    }

    // Write header to output-file

    fwrite(&fheader, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block

    int size = get_block_size(fheader);

    // Write reversed audio to file
    BYTE buffer[size];
    for (fseek(input, 0 - size, SEEK_END); ftell(input) > sizeof(fheader)-size; fseek(input, 0 - (size * 2), SEEK_CUR))
    {
        fread(&buffer, size, 1, input);
        fwrite(&buffer, size, 1, output);
    }


    fclose(input);
    fclose(output);
    return 0;
}

int check_format(WAVHEADER header)
{
    // TODO #4
    //Array of characters
    int wav[] = {0x57, 0x41, 0x56, 0x45};
    int i;
    for (i = 0; i < 4; i++)
    {
        //check if chars match those in file-format-descriptor
        if (header.format[i] != wav[i])
        {
            printf("Not a valid WAV file!\n");
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{

    int size;
    size = header.numChannels * (header.bitsPerSample / 8);

    return size;
}
