#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // check usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\r");
        return 1;
    }

    // open raw data
    FILE *fPtr = fopen(argv[1], "r");
    if (fPtr == NULL)
    {
        fprintf(stderr, "Cannot Open file\r");
        return 2;
    }


    // create a data array
    char data[512] = {0};
    int imgIdx = 0;
    FILE *jpgFile = NULL;
    bool isJpg = false;
    while (read(data, 1, 512, fPtr) == 512)
    {


        // first three: 0xff 0xd8 0xff
        // the 4th: 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef

        // if jpg header signature is found
        if (data[0] == (char)0xff && data[1] == (char)0xd8 && data[2] == (char)0xff && (data[3] & 0xf0) == 0xe0)
        {

            // if last data read is jpg, then close it
            if (isJpg && jpgFile != NULL)
            {
                fclose(jpgFile);
            }

            // set is image to true
            isJpg = true;

            // get new image name and increase the image index
            char fileName[16] = {0};
            sprintf(fileName, "%03d.jpg", imgIdx++);
            jpgFile = fopen(fileName, "a");

        }

        // if new data read is not a jpg signature,
        if (jpgFile != NULL)
        {
            fwrite(&data, 512, 1, jpgFile);
        }

    }


    // once the last data segment read is not 512, then close file
    fclose(jpgFile);
    fclose(fPtr);




    return 0;

}
