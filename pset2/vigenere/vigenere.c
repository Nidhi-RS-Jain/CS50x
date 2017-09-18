#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<ctype.h>

int main(int argc, string argv[]){
    if(argc != 2){
        printf("Give a command line argument\n");
        return 1;
    }
    
    int size = strlen(argv[1]);
    
    if(argc == 2){
        for(int i = 0; i < size; i++){
            argv[1][i] = toupper(argv[1][i]);
            if(!(argv[1][i] >= 'A' && argv[1][i] <= 'Z')){
                printf("Only alphabets should be present in argument\n");
                return 1;
            }
        }
    }
    
    int key[size];
    
    for(int i = 0; i < size; i++){
        key[i] = argv[1][i] - 65 ;
    }
    
    printf("plaintext: ");
    string plainText = get_string();
    char cipherText[strlen(plainText) + 1];
    
    for(int i = 0, iter = 0, n = strlen(plainText); i < n; i++, iter++){
        if(plainText[i] < 'A' || (plainText[i] >'Z' && plainText[i] < 'a') || plainText[i] > 'z'){
            cipherText[i] = plainText[i];
            iter --;
            continue;
        }
        
        cipherText[i] = (plainText[i] + key[iter % size]) % 128; 
    
        if(cipherText[i] > 'z'){
                    cipherText[i] = cipherText[i] - (int)'z' + (int)'a' - 1;
                }
            
        else if(cipherText[i] < 'a' && plainText[i] >= 'a'){
                cipherText[i] += 'a' + 5;
            }
            
        else if(cipherText[i] > 'Z' && plainText[i] <= 'Z'){
                cipherText[i] = cipherText[i] - (int)'Z' + (int)'A' - 1; 
            }
    }
    cipherText[strlen(plainText)] ='\0';
    
    printf("ciphertext: %s\n", cipherText);
    
    return 0;
}