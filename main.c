#include "header.h"

int main(int argc, char *argv[]) {
    list *head = NULL;

    // Read and validate the input arguments and create a linked list
    read_and_validate(argc, argv, &head);
    print(head);

    hash arr[27];

    int choice;
    while (1) {
        // Display menu options to the user
        printf("1. Create database\n2. Display database\n3. Search database\n4. Save database\n5. Update database\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Create hash table and database
                create_hash_table(arr);
                if (create_database(head, arr))
                    printf("Database created successfully\n");
                else
                    printf("Error creating database\n");
                break;
        
            case 2:
                // Display the database
                display_database(arr);
                break; 

            case 3: {
                // Search for a word in the database
                char data[15];
                printf("Enter a word to search: ");
                scanf(" %s", data);
                search_database(arr, data);
                break;
            }

            case 4:
                // Save the database to a file
                save_database(arr);
                break;

            case 5: {
                // Update the database from a file
                char filename[15];
                printf("Enter the filename to update the database: ");
                scanf("%s", filename);
                update_database(arr, filename);
                break;
            }
            
            case 6:
                // Exit the program
                exit(1);

            default:
                // Handle invalid choices
                printf("Enter a valid choice\n");
        }
    }

    return 0;
}
