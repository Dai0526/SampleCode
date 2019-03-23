// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int multi = atoi(argv[1]);

    if (multi < 1 || multi > 100)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf_in, bf_out;
    fread(&bf_in, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_out = bf_in;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi_in, bi_out;
    fread(&bi_in, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_out = bi_in;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf_in.bfType != 0x4d42 || bf_in.bfOffBits != 54 || bi_in.biSize != 40 ||
        bi_in.biBitCount != 24 || bi_in.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine old padding for scanlines
    int padding = (4 - (bi_in.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Resize BITMAPINFOHEADER
    bi_out.biWidth = bi_in.biWidth * multi;
    bi_out.biHeight = bi_in.biHeight * multi;

    // determine new padding for scanlines after update bi
    int newPadding = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_out.biSizeImage = ((sizeof(RGBTRIPLE) * bi_out.biWidth) + newPadding) * abs(bi_out.biHeight);

    // Resize BITMAPFILEHEADER
    bf_out.bfSize = bi_out.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    /* ========================================
    The lgorithm is:
    1. loop vertically(biHeight) to find each line
    2. for each line, loop over each pixel(biWidth),  using an array to store each pixel for new bmp-lines
    3. for each pixel, do n times horizontally.
    4. after one line is done, write the array to file, add new padding.
    5. repeat step 4 for n times to finish resize vertically
    6. set input file ptr to next line
    =============================================*/

    printf("IN-> width: %d, height: %d, padding: %d\n", bi_in.biWidth, bi_in.biHeight, padding);
    printf("OUT-> width: %d, height: %d, padding: %d\n", bi_out.biWidth, bi_out.biHeight, newPadding);

    // iterate over infile's scanlines
    int biHeight = abs(bi_in.biHeight);
    for (int i = 0; i < biHeight; ++i)
    {
        // instantiate an empty array for one row of new image
        RGBTRIPLE pixPtr[bi_out.biWidth];

        // iterate over pixels in scanline
        for (int j = 0; j < bi_in.biWidth; ++j)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read a single pixel (RGB triple) from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write pixel to array n times
            for (int n = 0; n < multi; ++n)
            {
                // write RGB triple to outfile
                pixPtr[j * multi + n] = triple;
                //printf("r:%d, g:%d, b:%d\n", pixPtr[j*multi+n].rgbtRed, pixPtr[j*multi+n].rgbtGreen, pixPtr[j*multi+n].rgbtBlue);
            } // each pixel

        }// each scanline

        // write new scanline array to outfile for n times, then add padding
        for (int vert = 0; vert < multi; ++vert)
        {
            fwrite(&pixPtr, bi_out.biWidth * sizeof(RGBTRIPLE), 1, outptr);
            // then add it back (to demonstrate how)
            // skip over padding, if any

            for (int k = 0; k < newPadding; ++k)
            {
                fputc(0x00, outptr);
            }

        }
        // set padding for input file cursor
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
