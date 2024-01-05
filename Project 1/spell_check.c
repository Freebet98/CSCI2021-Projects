#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define MAX_CMD_LEN 128

// A helper function to spell check a specific file
// 'file_name': Name of the file to spell check
// 'dict': A dictionary containing correct words
int spell_check_file(const char *file_name, const dictionary_t *dict){
    FILE *file_handle = fopen(file_name, "r");
    if(file_handle == NULL){
        return -1;
    }
    char word[MAX_WORD_LEN];

    while(!feof(file_handle)){
        if(fscanf(file_handle,"%s", word) > 0){
            int find = dict_find(dict, word);
            if(find == 1){
                printf("%s ", word);
            }
            else if (find == 0){
                printf("%s[X] ", word);
            }
        }
        int space = fgetc(file_handle);
        if(isspace(space) > 0){
            if(space == 10){
                printf("\n");
            }
        }
    }

    fclose(file_handle);
    return 0;
}

/*
 * This is in general *very* similar to the list_main file seen in lab
 */
int main(int argc, char **argv) {
    dictionary_t *dict = create_dictionary();
    char cmd[MAX_CMD_LEN];

    if(argc > 1){
        for(int i = 1; i < argc; i++){
            if(i == 1){
                dictionary_t *dict_r = read_dict_from_text_file(argv[i]);
                if(dict_r == NULL){
                    printf("Failed to read dictionary from text file\n");
                    break;
                }
                else{
                    printf("Dictionary successfully read from text file\n");
                    dict_free(dict);
                    dict = dict_r;
                }
                continue;
            }
            else if(i == 2){
                int check = spell_check_file(argv[i], dict);
                if(check == -1){
                    printf("Spell check failed\n");
                }
                continue;
            }
        }
    }
    else{
         printf("CSCI 2021 Spell Check System\n");
        printf("Commands:\n");
        printf("  add <word>:              adds a new word to dictionary\n");
        printf("  lookup <word>:           searches for a word\n");
        printf("  print:                   shows all words currently in the dictionary\n");
        printf("  load <file_name>:        reads in dictionary from a file\n");
        printf("  save <file_name>:        writes dictionary to a file\n");
        printf("  check <file_name>: spell checks the specified file\n");
        printf("  exit:                    exits the program\n");

        while (1) {
            printf("spell_check> ");
            if (scanf("%s", cmd) == EOF) {
                printf("\n");
                break;
            }

            if(strcmp("add", cmd) == 0){
                scanf("%s", cmd);
                int insert = dict_insert(dict, cmd);
                if(insert == -1){
                    printf("Failed to insert into dictionary\n");
                }
                continue;
            }

            if(strcmp("lookup", cmd) == 0){
                scanf("%s", cmd);
                int find = dict_find(dict, cmd);
                if(find == 0){
                    printf("\'%s\' not found\n", cmd);
                }
                else{ 
                    printf("\'%s\' present in dictionary\n", cmd);
                }
                continue;
            }

            if(strcmp("print", cmd) == 0){
                dict_print(dict);
                continue;
            }

            if(strcmp("load", cmd) == 0){
                scanf("%s", cmd);
                dictionary_t *dict_r = read_dict_from_text_file(cmd);
                if(dict_r == NULL){
                    printf("Failed to read dictionary from text file\n");
                }
                else{
                    printf("Dictionary successfully read from text file\n");
                    dict_free(dict);
                    dict = dict_r;
                }
                continue;
            }

            if(strcmp("save", cmd) == 0){
                scanf("%s", cmd);
                int save = write_dict_to_text_file(dict, cmd);
                if(save == 1){
                    printf("Failed to write dictionary from text file\n");
                }
                else{
                    printf("Dictionary successfully written to text file\n");
                }

                continue;
            }

            if(strcmp("check", cmd) == 0){
                scanf("%s", cmd);
                int check = spell_check_file(cmd, dict);
                if(check == -1){
                    printf("Spell check failed\n");
                }

                continue;
            } 

            if (strcmp("exit", cmd) == 0) {
                break;
            }

            else {
                printf("Unknown command %s\n", cmd);
                continue;
            }

            dict_free(dict);
            return 0;
        }
    }
    dict_free(dict);
}
