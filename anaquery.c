#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "make_anagram_list.h"

void query_anagrams(key_node *list) {
    char word[100];
    
    while (1) {
        printf("Enter a word or 'quit' to exit: ");
        scanf("%s", word);
        
        if (strcmp(word, "quit") == 0) {
            break;
        }
        
        char *key = sorting_key(word);
        key_node *current = list;
        
        while (current != NULL && strcmp(current->sorted_key, key) != 0) {
            current = current->next;
        }
        
        if (current != NULL && current->count > 1) {
            printf("Anagrams of '%s':\n", word);
            word_node *curr_word = current->word_list;
            while (curr_word != NULL) {
                if (strcmp(curr_word->word, word) != 0) {
                    printf("%s\n", curr_word->word);
                }
                curr_word = curr_word->next;
            }
        } else {
            printf("No anagrams found for '%s'\n", word);
        }
        printf("\n");
        
        free(key);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    // Open file of user input
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }
    
    // Count the number of words
    int count = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }
    
    // Reset file pointer
    rewind(file);
    
    // Read words into array
    char **words = malloc(count * sizeof(char*));
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';
        words[i] = strdup(buffer);
        i++;
    }
    
    fclose(file);
    
    // Create anagram list
    key_node *anagram_list = make_anagram_list(words, count);
    
    // Start query loop
    query_anagrams(anagram_list);
    
    // Free all allocated memory
    free_anagram_list(anagram_list);

    for (int i = 0; i < count; i++) {
        free(words[i]);
    }

        free(words);
    
    return 0;
}