#ifndef INV_H
#define INV_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include "colors.h"

#define SUCCESS 0
#define FAILURE -1
#define NOELEMENT -2
#define EMPTYLIST -3
#define REPEATED -4
#define FILE_EMPTY -5
#define NOT_PRESENT -6

#define SIZE 27
#define BUFF_SIZE 255
#define NAMELENGTH 255

//inverted table

/* subnode structue */
typedef struct sub_node
{
	char f_name[NAMELENGTH];
	int w_count;
	struct sub_node *link;
}sub_node_t;

/*structure for main node*/
typedef struct node
{
	char word[NAMELENGTH];
	struct node *link;
	sub_node_t *sub_link;
	int f_count;
}main_node_t;

/*structure for table*/
typedef struct table
{
	int index;
	main_node_t *mlink;
}table;

/* file node structure (Lineked list used to store the filenames */
typedef struct file_node
{
    char f_name[NAMELENGTH];
    struct file_node *link;
}file_node_t;


/* validating files */
int validate_n_store_filenames(file_node_t **, char *filenames[]);
int IsFileValid(char *);
int store_filenames_to_list(char *f_name, file_node_t **head);

/*Init hash table*/
void init_HT(table* HT);

/* Create Database */
int create_DB(file_node_t *file_head, main_node_t **head, table* HT);

/*Functions related to the Create DB*/
int read_datafile(file_node_t *, main_node_t **, char *f_name, table* HT);
int insert_at_last_main(main_node_t **head, char *word, char* f_name);
int update_sub_node(main_node_t **main_node, char* f_name);
int update_word_count(sub_node_t* sub_node, char *fname);
int toLower(char *str);

/* Display database */
int display_DB(table* HT);

/* Update database */
int update_DB(file_node_t **head, table* HT);
int validate_bck_file(char* f_name);
int update_to_main_node(char* word, int file_count, table* HT, int index);
int update_the_sub_node(char* word, int file_count, char* file_name, int word_count, main_node_t* temp,file_node_t** tempHead);
int Remove_Duplicate_Files_from_list(file_node_t* tempHead, file_node_t** fileHead);
void free_list(file_node_t** temp);
int remove_node(file_node_t** fileHead, file_node_t** tempPrev);
/* Search Database */
int search_DB(table *HT, char *word);

/* Save Database */
int save_DB(table* HT);

/*validate the back up file*/
int validate_backup(char*);

#endif
