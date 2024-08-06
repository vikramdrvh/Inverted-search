#include"header.h"

void create_hash_table(hash *arr){
    for(int i=0; i<28;i++){
        arr[i].index = i;
        arr[i].main_link = NULL;
    }
}

int create_database(list *head,hash *arr){
    list *temp = head;
    while(temp != NULL){
        open_and_store(temp->file_name,arr);
        temp = temp->next;
    }
    return SUCCESS;
}

int open_and_store(char *filename,hash *arr){
    FILE *fp;
    fp = fopen(filename,"r");
    char buffer[15]; 
    while(fscanf(fp," %s",buffer) == 1){
        if(insert_to_hashtable(buffer,filename,arr) == SUCCESS){
            continue;
        }
        else{
            printf("Error is storing word %s from %s!\n",buffer,filename);
        }
    }
    printf("\nSuccesfully stored %s in database\n\n",filename);
    fclose(fp);
    return SUCCESS;
}

int insert_to_hashtable(char* buffer,char* filename,hash *arr){
    int ind;
    char firstchar = tolower(buffer[0]);
    if(isalpha(buffer[0])){
        ind = firstchar - 'a';
    }
    else if(isdigit(buffer[0])){
        ind = 26;
    }
    else{
        ind  = 27; //special characters or symbols
    }
    Mnode *new = malloc(sizeof(Mnode));
    Snode *new_sub = malloc(sizeof(Snode));

    new_sub->word_count = 1;
    strcpy(new_sub->file_name,filename);
    new_sub->next = NULL;

    new->file_count = 1;
    strcpy(new->word,buffer);
    new->sub_link = new_sub;
    new->next = NULL;

    if(arr[ind].main_link == NULL){

        arr[ind].main_link = new;
        return SUCCESS;
    }

    Mnode *temp = arr[ind].main_link;

    while(temp->next != NULL){
        if(strcmp(temp->word,buffer)==0){
            if(strcmp(temp->sub_link->file_name,filename)==0){
                temp->sub_link->word_count++;
                return SUCCESS;
            }
            else{
                Snode *new_sub = malloc(sizeof(Snode));
                new_sub->word_count = 1;
                strcpy(new_sub->file_name,filename);
                new_sub->next = NULL;

                Snode *temp2 = temp->sub_link;

                while(temp2->next != NULL){
                    temp2 = temp2->next;
                }

                temp2->next = new_sub;
                temp->file_count++;
                return SUCCESS;
            }
        }
        temp = temp->next;
    }
    temp->next = new;
    return SUCCESS;     
}
