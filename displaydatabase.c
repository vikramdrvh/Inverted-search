#include"header.h"

int display_database(hash *arr) {
    printf("index\t word\t\t\t file_count\t filenames\t word_counts\n");
    
    for (int i = 0; i < 27; i++) {
        Mnode *main_node = arr[i].main_link;
        while (main_node != NULL) {
            printf("[%d]\t %-15s\t %7d", arr[i].index, main_node->word, main_node->file_count);
            Snode *sub_node = main_node->sub_link;
            
            while (sub_node != NULL) {
                printf("\t %-10s %9d \t", sub_node->file_name, sub_node->word_count);
                sub_node = sub_node->next;
            }
            printf("\n");
            main_node = main_node->next;
        }
    }
    return SUCCESS; 
}

