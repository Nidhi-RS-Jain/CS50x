/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

#include "dictionary.h"
node *root;
int count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int index = 0;
    node *temp = root;
    //printf("%s\n", word);
    int length = strlen(word);
    for(int i = 0; i < length; i++){
        switch(word[i]){
            case '\'': index = 26;
                    break;
            default: index = tolower(word[i]) - 97;
        }
        //printf("%d\n", index);
        if(temp->next[index] == NULL){
            return false;
        }
        temp = temp->next[index];
    }
    //printf("%d\n", index);
    return temp->is_word;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *inFile = fopen(dictionary, "r");
    //FILE *outfile = fopen("my.txt", "w");
    
    if(inFile == NULL){
        fprintf(stderr, "Cannot open the dictionary file %s\n", dictionary);
        return false;
    }
    root = NULL;
    node *tmp, *ptr;
    char str[LENGTH];
    root = malloc(sizeof(node));
    if(root != NULL){
        root->is_word = false;
        for(int i = 0; i < 27; i++)
            root->next[i] = NULL;
         while(fscanf(inFile, "%s", str) != EOF){
            int index = 0, i = 0;
                do{
                    switch(str[i]){
                        case '\'' : index = 26;
                                    break;
                        default: index = str[i] - 97;
                    }
                    
                    if(i){
                        if(ptr->next[index] == NULL){
                            tmp = (node *)malloc(sizeof(node));
                            
                            if(tmp == NULL){
                                fprintf(stderr, "Not enough memory to load dictionary\n");
                                return false;
                            }
                            ptr->next[index] = tmp;
                            ptr = tmp;
                        }
                        else{
                            ptr = ptr->next[index];
                        }
                    }
                    else{
                        if(root->next[index] == NULL){
                            tmp = (node *)malloc(sizeof(node));
                            if(tmp == NULL){
                                fprintf(stderr, "Not enough memory to load dictionary\n");
                                return false;
                            }
                            root->next[index] = ptr = tmp;
                        }
                        else{
                            ptr = root->next[index];
                        }
                    }
                    
                    i++;
                }while(i < strlen(str));
                     ptr->is_word = true;
                     count++;
                     //fprintf(outfile, "%s\n", WOR);
        }
    }
    else{
            fprintf(stderr, "Not enough memory to load dictionary\n");
            return false;
    }
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/*void dereference(node *tmp){
    int total = 0;
    for(int i = 0; i < 27; i++){
        if(tmp->next[i] == NULL){
            total++;
        }
        else{
            dereference(tmp->next[i]);
        }
    }
    if(total == 27){
        free(tmp);
    }
} */

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    //if(root != NULL){
        //dereference(root);
   // }
   free(root);
    return true;
}
