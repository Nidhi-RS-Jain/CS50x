#include<stdio.h>
#include<cs50.h>
#include<string.h>

int main(int argc, string argv[]){
    if(argc != 2){
        printf("OOPS! You were supposed to input a command line argument!\n");
        return 1;
    }
    
    printf("plaintext: ");
    string plainText = get_string();
    char cipherText[strlen(plainText) + 1];
    
    int k = atoi(argv[1]);
    
    /* for(int iter = 0, len = strlen(argv[1]); iter < len; iter++){
        k = 10 * k + ( argv[1][iter] - '0');
    } */
    
    
    k %= 26;
    
    for(int i = 0, n = strlen(plainText); i < n; i++){
        if(plainText[i] >= 'A' && plainText[i] <= 'Z'){
                cipherText[i] = plainText[i] + k;
                
                if(cipherText[i] > 'Z'){
                    cipherText[i] = cipherText[i] - (int)'Z' + (int)'A' - 1;
                }
        }
        
        else if(plainText[i] >='a' && plainText[i] <= 'z'){
            cipherText[i] = (plainText[i] + k) % 128;
            
            if(cipherText[i] > 'z'){
                cipherText[i] = cipherText[i] - (int)'z' + (int)'a' - 1; 
            }
            
            else if(cipherText[i] < 'a'){
                cipherText[i] += 'a' + 5;
            }
        }
        
        else cipherText[i] = plainText[i];
    }
    
    cipherText[strlen(plainText)] = '\0';
    
    printf("ciphertext: %s\n", cipherText);
    return 0;
}