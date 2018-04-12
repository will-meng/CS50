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
        fprintf(stderr, "Usage: ./resize scale_factor infile outfile\n");
        return 1;
    }
    
    // scale factor
    double f = atof(argv[1]);
    if (f <= 0 || f > 100)
    {
        fprintf(stderr, "Invalid scale factor of %f (must be in (0.0, 100])\n", f);
        return 5;
    }

    // remember filenames
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
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
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
    
    // create outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf2 = bf;
    
    // create outfile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi2 = bi;
    
    // determine new dimensions of output image (pixels only)
    bi2.biWidth = bi.biWidth * f;
    bi2.biHeight = bi.biHeight * f;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding2 = (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        
    // change outfile's total size info (includes padding and headers)
    bi2.biSizeImage = (sizeof(RGBTRIPLE) * bi2.biWidth + padding2) * abs(bi2.biHeight);
    bf2.bfSize = bi2.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    double vthresh, hthresh;
    for (int i = 1, i2 = 1, dupe, biHeight = abs(bi.biHeight); i <= biHeight; i++)
    {
        // only scan line if less than threshold, otherwise skip line with fseek
        vthresh = i*f;
        if (i2 > vthresh)
            fseek(inptr, (int) (bi.biWidth * sizeof(RGBTRIPLE) + padding), SEEK_CUR);
            
        dupe = 0;
        while (i2 <= vthresh)
        {
            // seek back to beginning of line if duplicating line when f > 1.0
            if (dupe > 0)
                fseek(inptr, -(int) (bi.biWidth * sizeof(RGBTRIPLE) + padding), SEEK_CUR);
                
            // iterate over pixels in scanline
            for (int j = 1, j2 = 1; j <= bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile while less than threshold
                hthresh = j*f;
                while (j2 <= hthresh)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    j2++;
                }
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
    
            // add padding to outfile (if necessary)
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }
            
            i2++;
            dupe++;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
