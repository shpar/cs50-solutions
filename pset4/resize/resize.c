/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP by (0, 100].
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

#define MAX_RESIZE 100

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize amount infile outfile\n");
        return 1;
    }

    // remember filenames and resize amount
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // check resize amount
    if (n <= 0 || n > MAX_RESIZE)
    {
        fprintf(stderr, "Resize amount must be between 0 and %i\n", MAX_RESIZE);
        return -1;
    }
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfResized;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, biResized;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // change header for new file
    bfResized = bf;
    biResized = bi;
    biResized.biWidth = bi.biWidth * n;
    biResized.biHeight = bi.biHeight * n;
    int biHeight = abs(biResized.biHeight);

    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingResized =  (4 - (biResized.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // sizes of file and bitmap in header
    bfResized.bfSize = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + 3 * biHeight * biResized.biWidth + biHeight * paddingResized;
    biResized.biSizeImage = 3 * biHeight * biResized.biWidth + biHeight * paddingResized;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfResized, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biResized, sizeof(BITMAPINFOHEADER), 1, outptr);

    

    // iterate over infile's scanlines
    for (int i = 0; i < biHeight; i++)
    {   
        
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // scale horizontally
            for (int k = 0; k < n; k++) 
            {
                // write pixel
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);                
            }
            
        }

        // skip over padding of input file
        fseek(inptr, padding, SEEK_CUR);

        // add padding to output file
        for (int k = 0; k < paddingResized; k++)
        {
            fputc(0x00, outptr);
        }
        
        // backtrack in input file for vertical copy
        if ((i + 1) % n != 0)
        {
            fseek(inptr, - sizeof(RGBTRIPLE) * bi.biWidth - padding, SEEK_CUR);    
        }
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}
