#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if(file == NULL){
        fprintf(stderr, "Cannot open the file\n");
        return 2;
    }
    
    typedef unsigned char byte;
    char* filename = malloc(7 * sizeof(char));
    int found = 0;
    byte* buffer = malloc(512 * sizeof(byte));
    int i = 0;
    FILE *img = NULL;

    while(fread(buffer, 1, 512, file) == 512){
        if(buffer[0] ==0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
            found = 1;
            sprintf(filename, "%03d.jpg", i);
            img = fopen(filename, "w");
            fwrite(buffer, 1, 512, img);
            i++;
        }
        else if(found){
            fwrite(buffer, 512, 1, img);
        }
    }
    
    free(filename);
    free(img);
    free(buffer);
    fclose(file);
    return 0;
}