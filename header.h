#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SUCCESS 1
#define FAILURE 0

typedef struct sub_node Snode; // Forward declaration of Snode
typedef struct main_node Mnode; // Forward declaration of Mnode

typedef struct sub_node {
    int word_count;
    char file_name[15];
    Snode *next;
} Snode;

typedef struct main_node {
    int file_count;
    char word[15];
    Snode *sub_link;
    Mnode *next;
} Mnode;

typedef struct lists {
    char file_name[15];
    struct lists *next;
} list;

typedef struct hash_table {
    int index;
    Mnode *main_link;
} hash;

int check_file_exist(char *filename);
int read_and_validate(int argc,char* argv[],list **head);
int add_file_to_list(char *filename,list ***head);
void print(list *head);
void create_hash_table(hash *arr);
int create_database(list *head ,hash *arr);
int open_and_store(char *filename,hash *arr);
int insert_to_hashtable(char* buffer,char* filename,hash *arr);
int display_database(hash *arr);
int search_database(hash *arr,char* data);
int save_database(hash *arr);
int update_database(hash *arr,char* filename);
int create_Sub_node(Snode **prevSnode, char *filename, int word_count);
int create_Main_node(Mnode **prevMnode, char *word, int file_count);