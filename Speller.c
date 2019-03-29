// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 65535  // range of unsigned int


/*
    Comments? Is it really a hashtable? By the struct defination, it looks more like a linkedlist
 */
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    // old hash function
    //return tolower(word[0]) - 'a';

    // new hash function, try to use memory address but failed
    int val = 0;
    for(int i = 0; i < strlen(word); ++i){
        val += tolower(word[i]);
    }

    return val % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO
        // word to struct
        int l = (int)strlen(word);   //get str length

        // allcoate emory for the node
        node* item = malloc(sizeof(node));
        item->next = NULL;

        // put info to node, I don't care if there are two same word in dictionary
        memset(item->word, 0, sizeof(item->word)); //for proper null terminating
        strcpy(item->word, word);

        // Get hash value for table index
        int val = hash(word);

        // save node into the hashtable and its list
        if (hashtable[val] == NULL)
        {
            hashtable[val] = item;
        }
        else
        {

            // put this node as the head of the list
            item->next = hashtable[val];
            hashtable[val] = item;

        } // end else

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int n = 0;
    for(int i = 0; i < N; ++i){
        if(hashtable[i] != NULL){
            ++n;    // increase the word count
            node* word = hashtable[i];
            while(word->next != NULL){
                word = word->next;
                ++n;    // increase the word count
            }
        }
    }

    return n;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    // hash the word
    int val = hash(word);

    node* item = hashtable[val];

    while (item != NULL){
        bool find = true;
        if(strlen(word) == strlen(item->word)){
            for(int i = 0; i < strlen(word); ++i){
                if(tolower(word[i]) != tolower((item->word)[i])){
                    find = false;
                }
            }


            if(find == true){
                return true;
            }
        }

        item = item -> next;

    }


    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; ++i)
    {
        node* temp;
        node* head = hashtable[i];

        while (head!=NULL){
            temp = head;
            head = head->next;
            free(temp);
        }

    }

    return true;
}
