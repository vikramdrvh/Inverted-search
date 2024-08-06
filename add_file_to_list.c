#include"header.h"

int add_file_to_list(char *filename,list ***head){

    list *new_file = malloc(sizeof(list));

    if(new_file == NULL){
        printf("Memory allocation failed to add file to list\n");
        return FAILURE;
    }

    strcpy(new_file->file_name,filename);
    new_file->next = NULL;

    if(**head == NULL){
        **head = new_file;
        printf("Stored %s file in list completed\n",filename);
        return SUCCESS;
    }


    list *temp = **head;    

    while (temp != NULL) {
        if (strcmp(temp->file_name, filename) == 0){
            printf("%s file already stored in database (duplicate found)\n", filename);
            return FAILURE;
        }
        if (temp->next == NULL){
            break;
        }
        temp = temp->next;
    }
    
    temp->next = new_file;
    printf("Stored %s file in list completed\n",filename);        
    
     
}