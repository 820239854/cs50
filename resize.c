/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
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
    BITMAPFILEHEADER bf;
    BITMAPFILEHEADER out_bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    out_bf = bf;
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    BITMAPINFOHEADER out_bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    out_bi = bi;
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    out_bi.biWidth = bi.biWidth * factor;
    out_bi.biHeight = bi.biHeight * factor;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding =  (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    out_bi.biSizeImage =  (out_bi.biWidth * sizeof(RGBTRIPLE)  + out_padding)* abs(out_bi.biHeight);
    out_bf.bfSize = out_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    // write outfile's BITMAPFILEHEADER
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        RGBTRIPLE* buffer = (RGBTRIPLE*)malloc(bi.biWidth*sizeof(RGBTRIPLE));
        RGBTRIPLE* pixels = buffer;
        RGBTRIPLE* to_free = buffer;
        for (int j = 0; j < bi.biWidth; j++)
        {
            fread(buffer, sizeof(RGBTRIPLE), 1, inptr);
            buffer = buffer + sizeof(RGBTRIPLE);
        }
        for(int k=0; k<factor; k++)
        {
            pixels = to_free;
            for (int j = 0; j < bi.biWidth; j++)
            {
                for(int n = 0; n<factor; n++)
                    fwrite(pixels, sizeof(RGBTRIPLE), 1, outptr);
                pixels = pixels + sizeof(RGBTRIPLE);
            }
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)

        free(to_free);
    }

    // close infile
    fclose(inptr);
    // close outfile
    fclose(outptr);
    // success
    return 0;
}
