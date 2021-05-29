#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
int main(int argc, char *argv[])

{
    
    if (argc > 2)
    {
    printf("Program only takes one command line argument");
    printf("\n");
    return 1;
    }
    if (argc != 2)
    {
     printf("usage ./Recover image");   
    }

    FILE *file = fopen(argv[1], "r"); 
    if (file == NULL)
    {
        printf("Couldn't open file, terminating");
        printf("n");
        return 1;
    }
    
      
    char file_name[8];
    BYTE buffer [512];
    FILE *image_out = NULL;
    int count = 0;
    while(fread(&buffer, 512, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            
            if (!(count == 0))
            {
            fclose(image_out);  
            }
           
        sprintf(file_name, "%03i.jpg", count);
        image_out = fopen(file_name, "w");
        count++;
        
            
        }    
        
        if (!(count ==0))
        {
            fwrite(&buffer, 512, 1, image_out);
        }    
    }   
    fclose(image_out);
    fclose(file);
    
     return 0;   
    }
