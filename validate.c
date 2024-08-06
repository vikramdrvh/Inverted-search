#include"header.h"

int read_and_validate(int argc,char* argv[],list **head){

    if(argc > 1){
        for(int i=1; i<argc; i++){

            char *compare = strstr(argv[i], ".txt");

            if(compare != NULL && strcmp(compare, ".txt") == 0){
    
                if(check_file_exist(argv[i]) == SUCCESS){
                    add_file_to_list(argv[i],&head);
                }
            }
            else{
                printf("the %s is not a valid file(.txt missing)\n",argv[i]);
            }
        }
    }
    else{
        printf("Please pass input file via CLA\n");
        exit(1);
    } 
    return SUCCESS;
}

int check_file_exist(char *filename){
FILE *fp;
    char ch;

    fp = fopen(filename,"r");
     
    if(fp == NULL){
        printf("Unable open file, %s \n",filename);
        return FAILURE;
    }

    ch = fgetc(fp);

    if(ch == EOF){ //check for contents in the file
        printf("The file, %s has no contents\n",filename);
        return FAILURE;
    }

    fclose(fp);
    return SUCCESS;
}


