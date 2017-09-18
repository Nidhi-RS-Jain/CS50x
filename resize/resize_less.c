/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
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
    BITMAPFILEHEADER bf, nbf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, nbi;
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
    
    nbi.biWidth = bi.biWidth * n;
    nbi.biHeight = bi.biHeight * n;
    nbi.biSizeImage = ((sizeof(RGBTRIPLE) * nbi.biWidth) + (4 - (nbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4) * abs(nbi.biHeight);
    nbi.biSize = bi.biSize;
    nbi.biPlanes = bi.biPlanes;
    nbi.biBitCount = bi.biBitCount;
    nbi.biCompression = bi.biCompression;
    nbi.biXPelsPerMeter = bi.biXPelsPerMeter;
    nbi.biYPelsPerMeter = bi.biYPelsPerMeter;
    nbi.biClrImportant = bi.biClrImportant;
    nbi.biClrUsed = bi.biClrUsed;
    
    nbf.bfSize = nbi.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
    nbf.bfType = bf.bfType;
    nbf.bfReserved1 = bf.bfReserved1;
    nbf.bfReserved2 = bf.bfReserved2;
    nbf.bfOffBits = bf.bfOffBits;
    // write outfile's BITMAPFILEHEADER
    fwrite(&nbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&nbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int npadding = (4 - (nbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //FILE *temp;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //temp = inptr;
        
        for(int iterate = 0; iterate < n - 1; iterate++){
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for(int iter = 0; iter < n; iter ++){
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
        
            // then add it back (to demonstrate how)
            for (int k = 0; k < npadding; k++)
            {
                fputc(0x00, outptr);
            }
            
           //inptr = temp;
           fseek(inptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + i * (bi.biWidth * sizeof(RGBTRIPLE) + padding), SEEK_SET);
        }
        
        
        // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for(int iter = 0; iter < n; iter ++){
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
        
            // then add it back (to demonstrate how)
            for (int k = 0; k < npadding; k++)
            {
                fputc(0x00, outptr);
            }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
