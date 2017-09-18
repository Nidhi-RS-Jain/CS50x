#include<cs50.h>
#include<stdio.h>

int main(void){
    int height, flag, iterate;
    
    do{
        printf("Height: ");
        height = get_int();
    }while(!(height >= 0 && height <= 23));
    
    
    for(iterate = 0, flag = 1; iterate < height; iterate++, flag++){
        for(int iter = flag; iter < height; iter++){
            printf(" ");
        }
        for(int iter = 0; iter < flag; iter++){
            printf("#");
        }
        printf("  ");
        for(int iter = 0; iter < flag; iter++){
            printf("#");
        }
        /*for(int iter = flag - 1; iter < height; iter++){
            printf(" ");
        }*/
        printf("\n");
    }
    
    return 0;
}