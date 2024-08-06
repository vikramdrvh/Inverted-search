#include "header.h"

FILE *fptr = NULL; 

int create_Sub_node(Snode **prevSnode, char *filename, int word_count) {
    // printf("inside create_sub_node\n\n");
    Snode *Snew = malloc(sizeof(Snode));
    if (Snew == NULL) {
        printf("ERROR: Memory allocation failed for Snew\n");
        return FAILURE;
    }

    // Copy the filename into the array
    strncpy(Snew->file_name, filename, sizeof(Snew->file_name) - 1);
    Snew->file_name[sizeof(Snew->file_name) - 1] = '\0'; // Ensure null-termination

    Snew->word_count = word_count;
    Snew->next = NULL;

    if (*prevSnode == NULL) {
        *prevSnode = Snew;
    } else {
        Snode *current = *prevSnode;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = Snew;
    }
    // printf("done create_sub_node\n\n");

    return SUCCESS;
}

int create_Main_node(Mnode **prevMnode, char *word, int file_count) {
    // printf("inside create_main_node\n\n");
    Mnode *Mnew = malloc(sizeof(Mnode));
    if (Mnew == NULL) {
        printf("ERROR: Memory allocation failed for Mnew\n");
        return FAILURE; // Check if malloc for Mnew failed
    }

    // Copy the word into the array
    strncpy(Mnew->word, word, sizeof(Mnew->word) - 1);
    Mnew->word[sizeof(Mnew->word) - 1] = '\0'; // Ensure null-termination

    Mnew->file_count = file_count;
    Mnew->next = NULL;
    Mnew->sub_link = NULL;

    if (*prevMnode == NULL) {
        *prevMnode = Mnew;
    } else {
        Mnode *current = *prevMnode;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = Mnew;
    }
    // printf("done create_main_node\n\n");

    return SUCCESS;
}

int update_database(hash *arr, char* filename) {
    if (strstr(filename, ".txt") == NULL) {
        printf("Error: Pass only .txt files to update database\n");
        return FAILURE;
    }

    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("ERROR: File %s does not exist\n", filename);
        return FAILURE;
    }

    // printf("cccccccccc before seek\n");

    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr);

    if (size < 1) {
        printf("ERROR: File \"%s\" is empty\n", filename);
        fclose(fptr);
        return FAILURE;
    }

    rewind(fptr);
    // printf("cccccccccc after seeek\n");

    char ch, flag = 0;

    // Check if the file starts with a '#'
    if ((ch = fgetc(fptr)) == '#') {
        while ((ch = fgetc(fptr)) != '\n') {
            if (ch == '#') {
                flag = 1;
                break;
            }
        }
    }

    if (flag == 0) {
        printf("Provided file %s is not a backup file\n", filename);
        fclose(fptr);
        return FAILURE;
    }

    for (int i = 0; i < 27; i++) {
        arr[i].index = i;
        arr[i].main_link = NULL;
    }

    char line[1000];
    char *token;

    // printf("before fgetsssssssssssss\n");

    rewind(fptr);
    while (fscanf(fptr, "%1023[^\n]\n", line) != EOF) {
        // printf("Processing line: %s\n", line); // Debugging statement

        // Tokenize the line
         token = strtok(line, "#;");
        int idx = atoi(token);

        token = strtok(NULL, "#;");
        char *word = strdup(token);

        token = strtok(NULL, "#;");
        int file_count = atoi(token);


        Mnode *tempMnode = arr[idx].main_link;

        if (tempMnode == NULL) {
            create_Main_node(&arr[idx].main_link, word, file_count);
            tempMnode = arr[idx].main_link;
        } else {
            // Traverse to the end of the main node list
            while (tempMnode->next != NULL) {
                tempMnode = tempMnode->next;
            }
            create_Main_node(&tempMnode->next, word, file_count);
            tempMnode = tempMnode->next; // Move to the newly created main node
        }

        Snode *tempSnode = tempMnode->sub_link;

        // Create sub nodes based on file count
        for (int i = 0; i < file_count; i++) {
            token = strtok(NULL, "#;");
            char *file = strdup(token);

            token = strtok(NULL, "#;");
            int word_count = atoi(token);

            if (tempSnode == NULL) {
                create_Sub_node(&tempMnode->sub_link, file, word_count);
                tempSnode = tempMnode->sub_link;
            } else {
                // Traverse to the end of the sub node list
                while (tempSnode->next != NULL) {
                    tempSnode = tempSnode->next;
                }
                create_Sub_node(&tempSnode->next, file, word_count);
            }
        }
        free(word); // Free the duplicated word after use
    }

    fclose(fptr); // Close the file pointer

    // Display the database/hashtable
    display_database(arr);

    printf("\n\nDatabase updated succesfully!\n\n");

    return SUCCESS;
}

