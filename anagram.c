#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"make_anagram_list.h"
#include"histogram.h"

void find_max_variants(key_node *list){
    key_node *curr = list;
    key_node *max_node = NULL;
    int max_count = 0;

    // iterate through the list to get the key with highest count
    while(curr !=NULL){
        if(curr->count > max_count){
            max_count = curr->count;
            max_node = curr;
        }
        curr = curr->next;
    }

    if(max_node !=NULL){
        printf("Most variants anagram is %s with %d variants \n", max_node->sorted_key, max_count);
    }
}

void longest_pair(key_node *list){
    key_node *curr = list;
    word_node *longest1 = NULL;
    word_node *longest2 = NULL;
    int max_length = 0;

    // iterate through the list to get the longest key 
    while(curr != NULL){
        if(curr->count >= 2){
            int len = strlen(curr->sorted_key);
            if(len >= max_length){
                // if found set value of longest pair to the first 2 words in word list
                max_length = len;
                longest1 = curr->word_list;
                longest2 = longest1->next;

            }
        }
        curr = curr->next;
    } 

    if (longest1 != NULL && longest2 != NULL) {
        printf("Longest anagram pair (length %d):\n", max_length);
        printf("%s and %s\n\n", longest1->word, longest2->word);
    }
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    // Initialise array for strings
    char **strings = NULL;
    int count = 0;
    int capacity = 10;
    char buffer[100];

    // Allocate initial capacity for strings
    strings = (char **)malloc(capacity * sizeof(char *));
    if (strings == NULL) {
        printf("Malloc failed\n");
        fclose(file);
        return 1;
    }

    // Read the file line by line
    while (fscanf(file, "%s", buffer) != EOF) {

        // Resize the array
        if (count >= capacity) {
            capacity *= 2;
            char **new_strings = (char **)realloc(strings, capacity * sizeof(char *));

            if (new_strings == NULL) {
                printf("Realloc failed\n");
                fclose(file);
                
                // Free already allocated memory
                for (int i = 0; i < count; i++) {
                    free(strings[i]);
                }
                free(strings);

                return 1;
            }
            strings = new_strings;
        } 

        strings[count] = strdup(buffer);  // Duplicate the line into the array
        count++;
    }

    fclose(file);

    key_node *root = make_anagram_list(strings, count);

    find_max_variants(root);

    longest_pair(root);

    //Prepare list for histogram
    int hist_arr[11] = {0};
    key_node *curr = root;
    while(curr != NULL){
        int count = curr->count;
        if(count >= 2 && count <=12){
            hist_arr[count]++;
        }
        curr = curr->next;
    }

    int x[11];
    double y[11];

    for (int i = 2; i <= 12; i++){
        x[i - 2] = i;
        y[i - 2] = hist_arr[i] > 0 ? log10(hist_arr[i]) : 0;
    }

    printf("\nHistogram:\n");
    histogram(x, y, 11, 50);  // 50 is the width of the histogram
    
    // Free all allocated memory
    free_anagram_list(root);
    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}



