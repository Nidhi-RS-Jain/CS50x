#include<stdio.h>
#include<cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>

char *crypt(const char *key, const char *salt);

int main(int argc, string argv[]){
    
    string pass = crypt(key, "50");
    char key[5];
    
    printf("%s\n", key);
    return 0;
}