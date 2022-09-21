// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //create a buffer that will read 8bits(1byte) each time and can carry 44bytes(header_size)
    uint8_t header[HEADER_SIZE];
    //start read at header, size in bytes of how much to read, read 1 at a time, from input
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    //create a buffer that will read 16bits(2bytes) each time (can carry any amount of bits needed kinda thing)

    int16_t buffer;
    //while loop is reading from buffer with a size of 2bytes each time from input it updates buffer after each go and that updated buffer is put in the output
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
