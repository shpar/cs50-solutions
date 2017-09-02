/**
 * Implements a dictionary's functionality using a trie.
 */

#include <stdbool.h>
#include "dictionary.h"

node* build(int* c, node* tran, node* root);
void delete(node* tran);
node *root = NULL;
unsigned int *sizeDict;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // check down every linked list of a trie if the word is present
    node* tran = root;
    for (int i = 0;  i < LENGTH; i++)
    {
        if (tran == NULL)
            return false;
        else if (word[i] == '\0')
        {
            if (tran->is_word == true)
                return true;
            else
                return false;
        }
        else if (isalpha(word[i]))
        {
            unsigned int temp = tolower(word[i]);
            if (tran->child[temp - 'a'] == NULL && tran->is_word != true)
                return false;
            tran = tran->child[temp - 'a'];
        }
        else if (word[i] == '\'')
        {
            if (tran->child[MAX_WORD-1] == NULL && tran->is_word != true)
                return false;
            tran = tran->child[MAX_WORD-1];
        }
    }
    return true;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        unload();
        return 1;
    }
    
    // keep track of dictionary size and create trie structure using the build function
    sizeDict = calloc(1, sizeof(int));
    *sizeDict = 0;
    root = calloc(1, sizeof(node));
    node *tran = root;
    
    int c = fgetc(fp);
    while (c != EOF)
    {
        tran = build(&c, tran, root);
        c = fgetc(fp);
    }
    tran->is_word = true;
    tran = root;
    root->is_word = false;

    fclose(fp);
    if (c == EOF)
        return true;
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return *sizeDict;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // unload dictionary by calling the delete function
    node *tran = root;
    delete(tran);

    free(sizeDict);
    return true;
}

node* build(int* c, node* tran, node *root)
{
    // insert the character into the dictionary's trie structure
    if (isalpha(*c))
    {
        *c = tolower(*c);
        if (tran->child[*c - 'a'] == NULL)
        {
            node *new = calloc(1, sizeof(node));
            tran->child[*c - 'a'] = new;
            return new;
        }
        else if (tran->child[*c - 'a'] != NULL)
        {
            tran = tran->child[*c - 'a'];
            return tran;
        }
    }
    
    else if (*c == '\'')
    {
        if (tran->child[MAX_WORD-1] == NULL)
        {
            node *new = calloc(1, sizeof(node));
            tran->child[MAX_WORD-1] = new;
            return new;
        }
        else if (tran->child[MAX_WORD-1] != NULL)
        {
            tran=tran->child[MAX_WORD-1];
            return tran;
        }
    }
    
    else if (*c == '\n')
    {
        tran->is_word = true;
        tran = root;
        *sizeDict = *sizeDict + 1;
        return root;
    }
    return root;
}

void delete(node* tran)
{
    // recursively delete trie
    for (int i = 0; i < MAX_WORD; i++)
    {
        if (tran->child[i] == NULL && tran->is_word == true)
        {
            free(tran->child[i]);
        }
        else if (tran->child[i] != NULL)
        {
            delete(tran->child[i]);
        }
    }
    free(tran);
}