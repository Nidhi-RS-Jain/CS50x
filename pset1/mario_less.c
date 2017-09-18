#include<cs50.h>
#include<stdio.h>

int main(void){
    int height, inc = 2;
    
    do{
        printf("Height: ");
        height = get_int();
    }while(!(height >= 0 && height <= 23));
    
    for(int iter = 0; iter < height; iter++, inc++){
         for(int iterIn = inc - 1; iterIn < height; iterIn++){
             printf(" ");
         }
         for(int iterate = 0; iterate < inc; iterate++){
             printf("#");
         }
         printf("\n");
    }
    return 0;
}