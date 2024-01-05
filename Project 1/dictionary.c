#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

#define MAX_CMD_LEN 128

int binary_search(node_t *node, const char* query);
void inorder_traversal(node_t *node);
void traversal_free(node_t *node);
void node_free(node_t *node);
int string_compare(const char *node_word, const char *word);
void inorder_traversal_write(node_t *node, FILE *file_handle);

dictionary_t *create_dictionary() {
    dictionary_t *dict = malloc(sizeof(dictionary_t));
    if (dict == NULL) {
        return NULL;
    }
    dict->root = NULL;
    dict->size = 0;
    return dict;
}

/*Insert helper gets a node and a word, this function assumes the node passed in is not null
    Within the function, the word stored in the node will be compared against the word passed
    to the function. If the word passed to the function is smaller, a new node will be created
    on the left, otherwise on the right. This is a recursive function. returns 0
*/
int insert_helper(node_t *node, const char *word){
    if(strcmp(node->word, word) > 0){
        if(node->left == NULL){
            node->left = malloc(sizeof(node_t));
            strcpy(node->left->word, word);
            node->left->left = NULL;
            node->left->right = NULL;
            return 0;
        }
        else{
            insert_helper(node->left, word);
        }
    }
    else if(strcmp(node->word, word) < 0){
        if(node->right == NULL){
            node->right = malloc(sizeof(node_t));
            strcpy(node->right->word, word);
            node->right->left = NULL;
            node->right->right = NULL;
            return 0;
        }
        else{
            insert_helper(node->right, word);
        }
    }

    return 0;
}

int dict_insert(dictionary_t *dict, const char *word) {
    if(dict->root == NULL){
            dict->root = malloc(sizeof(node_t));
            strcpy(dict->root->word, word);
            dict->root->left = NULL;
            dict->root->right = NULL;
            return 0;
    }
    else{
        int result = insert_helper(dict->root, word);
        dict->size = dict->size + 1;
        return result;
    }
    
    return -1;
}

int dict_find(const dictionary_t *dict, const char *query) {
    int find = binary_search(dict->root, query);
    if(find == 0){
        return 0;
    }

    return 1;
}

void dict_print(const dictionary_t *dict) {
    if(dict == NULL){
        return;
    }
    inorder_traversal(dict->root);
    return;
}

void dict_free(dictionary_t *dict) {
    traversal_free(dict->root);
    free(dict);
}

dictionary_t *read_dict_from_text_file(const char *file_name) {
    FILE *file_handle = fopen(file_name, "r");

    if(file_handle == NULL) {
        return NULL;
    }

    dictionary_t *dict = create_dictionary();
    char word[MAX_CMD_LEN];

    while(!feof(file_handle)){
        fscanf(file_handle,"%s", word);
        dict_insert(dict, word);
    }

    fclose(file_handle);

    return dict;

}

int write_dict_to_text_file(const dictionary_t *dict, const char *file_name) {
    FILE *file_handle = fopen(file_name, "w");
    if(file_handle == NULL){
        return 1;
    }

    //print to the file_handle
    inorder_traversal_write(dict->root,file_handle);
    fclose(file_handle);
    
    return 0;
}

/* Binary search is a function used to find a node in the dictionary and say that it has been found.
    This function takes a node and a char array query. It then recurses through the tree, until it
    either finds a node that matches the found given and returns 1 or returns 0 otherwise
*/
int binary_search(node_t *node, const char *query){
    //algorithm obtained from 4041 textbook
    int result = 0;
    if(node == NULL){
        result = 0;
        return result;
    }
    else{
        if(strcmp(node->word, query) == 0){
            result = 1;
            return result;
        }
        else if(strcmp(node->word, query) > 0){
            return binary_search(node->left, query);
        }
        else if(strcmp(node->word, query) < 0){
            return binary_search(node->right, query);
        }
        else{
            result = 0;
        }
    }

    return result;
}

/* traversal free is a function used to free all the nodes. It is based off of the inorder traversal
used to go throughout a binary search tree. This will recurse all the way down to the leaves and free
as it works its way up. This function takes in a node as a parameter and returns nothing.
*/
void traversal_free(node_t *node){
    if(node == NULL){ 
       return;
    }
    else {
        traversal_free(node->left);
        traversal_free(node->right);
        free(node);
    }

    return;
}

/* Inorder traversal is a function used to print all the nodes of the tree in ABC order. It takes a node
as a parameter. It recurses through the tree, working its way down first through the left side and then
printing nodes, and then through the right side. 
*/
void inorder_traversal(node_t *node){
    //algorithom obtained from 4041 textbook
    if(node == NULL){
        return;
    }

    inorder_traversal(node->left); //recur on left side
    printf("%s\n", node->word); //print word of node
    inorder_traversal(node->right); //recur on right side
}

/* Inorder traversal write is a function based off of inorder traversing through a binary search tree. 
    This function takes in a node and a file handle. It will then recurse through the tree, starting at
    left most leaf and print to the file passed and will continue until it has gone through every node in
    the dictionary
*/
void inorder_traversal_write(node_t *node, FILE *file_handle){
    if(node == NULL){
        return;
    }

    inorder_traversal_write(node->left, file_handle);
    fprintf(file_handle, "%s\n", node->word);
    inorder_traversal_write(node->right, file_handle);
}