#include "header.h"

// Function to print the linked list of file names
void print(list *head) {
    if (head == NULL) {
        printf("INFO: List is empty\n");
    } else {
        // Traverse through the list and print each file name
        while (head) {
            printf("%s -> ", head->file_name);
            head = head->next;
        }
        printf("NULL\n");
    }
}
