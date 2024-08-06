#include"header.h"

 int search_database(hash *arr,char* data){

    int ind;
    char firstchar = tolower(data[0]);

    if(isalpha(data[0])){
        ind = firstchar - 'a';
    }
    else if(isdigit(data[0])){
        ind = 26;
    }
    else{
        ind  = 27; //special characters or symbols
    }

    Mnode *tempMnode = arr[ind].main_link;

    while(tempMnode != NULL){
        if(tempMnode->word != NULL && strcmp(tempMnode->word,data) == 0){
            printf("Word %s is found in the database\n",data);
            printf("[%d]\t %-15s\t %7d", arr[ind].index, tempMnode->word, tempMnode->file_count);

            Snode *sub_node = tempMnode->sub_link;
            
            while (sub_node != NULL) {
                if(sub_node->file_name != NULL){
                    printf("\t %-10s %9d \t", sub_node->file_name, sub_node->word_count);
                }
                sub_node = sub_node->next;
            }
            printf("\n");
        }
        tempMnode = tempMnode->next;
    }
    printf("Word %s is not found in the database.\n", data);
}


