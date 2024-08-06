#include"header.h"

int save_database(hash *arr){
    FILE *fp = fopen("database.txt","w");
    if(fp == NULL){
        printf("Error opening database.txt for writing\n");
        return FAILURE;
    }
    for(int i=0;i<27;i++){
        Mnode *tempMnode = arr[i].main_link;

        while(tempMnode != NULL){
            if(tempMnode->word != NULL){
                fprintf(fp, "#%d;%s;%d;",arr[i].index,tempMnode->word,
tempMnode->file_count);
                Snode *tempSnode = tempMnode->sub_link;

                while(tempSnode != NULL){
                    if(tempSnode->file_name != NULL){
                        fprintf(fp, "%s;%d;",tempSnode->file_name,
tempSnode->word_count);
                    }
                    tempSnode = tempSnode->next;
                }
                fprintf(fp, "#\n");
            }
            tempMnode = tempMnode->next;
        }
    }
    fclose(fp); // Close the file
    printf("Database saved successfully to database.txt.\n");
}