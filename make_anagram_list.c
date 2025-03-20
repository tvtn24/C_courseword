#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "make_anagram_list.h"


int compare(const void *a, const void *b) {
    return *(const char *)a - *(const char *)b;
}

char *sorting_key(char *word){
    size_t size = strlen(word);

    char *key = malloc(size + 1);
    if (key == NULL){
        printf("Malloc failed!");
    }

    strcpy(key, word); //make a copy to keep original word

    // sort the key
    qsort(key, size, sizeof(char), compare);
    return key;
}


key_node *make_anagram_list(char **words, int n){
    key_node *head = NULL;
    for (int i = 0; i < n; i++){
        char *key = sorting_key(words[i]);
        
        // Find insertion index
        key_node *current = head; 
        key_node *prev = NULL;

        // Search for existing key
        while(current != NULL && strcmp(current->sorted_key, key) < 0){
            prev = current;
            current = current->next;
        }

        // If key already in the list, add word to words list
        if(current != NULL && strcmp(current->sorted_key, key) == 0){
            word_node *new_word = malloc(sizeof(word_node));
            if (new_word == NULL) {
                perror("Malloc failed");
                exit(0);
            }
            new_word->word = strdup(words[i]);
            new_word->next = current->word_list;
            current->word_list = new_word;
            current->count++; //increment the count of variants

            free(key);
        } else{
             // if key not found create new key
            key_node *new_key = malloc(sizeof(key_node));
            if (new_key == NULL) {
                perror("Malloc failed");
                exit(0);
            }
            new_key->sorted_key = key;
            new_key->count = 1; // set the variant count to 1
            
            // Add first word to words list
            word_node *new_word = malloc(sizeof(word_node));
            if (new_word == NULL) {
                perror("Malloc failed");
                exit(0);
            }
            new_word->word = strdup(words[i]);
            new_word->next = NULL;
            new_key->word_list = new_word;
             // Insert into key list in sorted order
            if (prev == NULL) {
            new_key->next = head;
            head = new_key;
            } else {
                new_key->next = current;
                prev->next = new_key;
            }
        }
    }
    return head;
}

//Free the memory allocated for the anagram list
void free_anagram_list(key_node *list) {
    key_node *current = list;
    
    while (current != NULL) {
        key_node *temp_key = current;
        current = current->next;
        
        // Free words list 
        word_node *word = temp_key->word_list;
        while (word != NULL) {
            word_node *temp_word = word;
            word = word->next;
            free(temp_word->word);  // Free the string 
            free(temp_word);        // Free word node
        }
        
        free(temp_key->sorted_key);  // Free sorted key 
        free(temp_key);       // Free key node
    }
}
