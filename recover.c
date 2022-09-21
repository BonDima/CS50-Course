#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//define a new type which is BYTE, it will store an 8-bit unsigned integer
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //--------------DEFINES------------------------
    //define the buffer that will have a size of 512 bytes, or 4096 bits
    BYTE buffer[512];
    //counter for the number of jpegs created
    int counter = 0;
    //names in order
    char order_names[8];

    //check if its a 1 command line argument, if its not then print Usage, close the file and return 1
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //we open the file for reading (argv[1] is card.raw)
    FILE *file = fopen(argv[1], "r");
    //if check if for if the ime cant be opened fo reading
    if (!file)
    {
        return 1;
    }

    FILE *img = NULL;

    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        //check if the 3 first values represent the start of the JPG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if its the first time and checks the header
            if (counter == 0)
            {
                //create the jpg
                sprintf(order_names, "%03i.jpg", counter);
                //change first to 0, which means that we have found the first jpg
                img = fopen(order_names, "w");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                //increment counter because a new jpg is gonna be created
                counter += 1;
            }
            //if not the first and checks the header
            else if (counter > 0)
            {
                fclose(img);
                //create the jpg
                sprintf(order_names, "%03i.jpg", counter);
                img = fopen(order_names, "w");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                counter += 1;
            }
        }
        //if doesnt check the header but its not the first time
        else
        {
            if (counter > 0)
            {
                fwrite(&buffer, sizeof(BYTE), 512, img);
            }
        }
    }
    fclose(file);
    fclose(img);
}