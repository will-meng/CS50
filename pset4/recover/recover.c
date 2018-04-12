#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCKSIZE 512
#define MAX_FILENAME_LENGTH 7

FILE* create_output_file(char filename[], int outfileNum);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover filename\n");
        return 1;
    }
    
    // open card file
    FILE * inptr = fopen(argv[1],"r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Unable to open %s\n",argv[1]);
        return 2;
    }
    
    // create buffer
    uint8_t buffer[BLOCKSIZE];
    
    // initialize naming of output jpg files
    int outfileNum = 0;
    char filename[MAX_FILENAME_LENGTH + 1];
    FILE *outptr;
    
    // create flag for open jpg file
    int openJPG = 0;
    
    // iterate over each 512 byte block
    while (fread(buffer, BLOCKSIZE, 1, inptr) > 0)
    {  
         // check for start of jpg file
         if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
         {
            // found new jpg, so close existing output jpg and increment outfileNum
            if (openJPG == 1)
            {
                fclose(outptr);
                outfileNum++;
            }
            
            // open new output jpg file
            outptr = create_output_file(filename, outfileNum);
            openJPG = 1;
         }   
                
        // check if open output jpg file exists
        if (openJPG == 1)
        {
            // append to currently open output jpg file
            fwrite(buffer, BLOCKSIZE, 1, outptr);
        }
    }           

    // close card file
    fclose(inptr);
    
    // close jpg file 
    fclose(outptr);
            
}

FILE* create_output_file(char filename[], int outfileNum)
{
    // 
    sprintf(filename, "%03i.jpg", outfileNum);
    FILE *outptr = fopen(filename,"w");
    if (outptr == NULL)
    {
        fprintf(stderr,"Unable to open %s\n",filename);
        exit(3); 
    }
    
    return outptr;
}