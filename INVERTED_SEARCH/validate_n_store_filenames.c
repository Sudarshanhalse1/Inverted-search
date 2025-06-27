#include "invertedIndex.h"

int validate_n_store_filenames(file_node_t ** head, char *filenames[])
{
    
    int i=1;
    while(filenames[i])
    {
        if(IsFileValid(filenames[i])==SUCCESS)
        {
            store_filenames_to_list(filenames[i], head);
        }
        i++;
    }
    return SUCCESS;
    
}
int IsFileValid(char * filenames)
{
    
    /*case handling the file is .txt*/
    if(strstr(filenames, ".txt") != NULL && (strcmp(strstr(filenames, ".txt"), ".txt")==0))
    {
        /*check file is exist*/
        FILE* fptr = fopen(filenames, "r");
        if(fptr != NULL)
        {
            fseek(fptr, 0, SEEK_END);
            /*checking is it empty*/
            if(ftell(fptr) != 0)
            {
                fclose(fptr);
                return SUCCESS;
                /*logic for the duplicate file is written in the store file names to list*/
            }
            else
            {
                printf("INFO: %s File empty\n", filenames);
                fclose(fptr);
                return FAILURE;
            }
            
        }
        else
        {
            printf("ERROR: %s does not exist\n", filenames);
            return FAILURE;
        }
    }
    else
    {
        printf("warning: %s file is not \".txt\" file\n", filenames);
        return FAILURE;
    }

}
int store_filenames_to_list(char *f_name, file_node_t **head)
{
    
    file_node_t *new = malloc(sizeof(file_node_t));
    if (new == NULL)
        return FAILURE;
    strcpy(new->f_name, f_name);
    new->link = NULL;
    if (*head == NULL)
    {
        *head = new;
        printf("Successful: inserting file name : %s into file linked list\n",f_name); 
        return SUCCESS;  
    }
    file_node_t* temp = *head, *tempPrev = NULL;
    /*checking the duplicate is present or not*/
    while (temp && (strcmp(temp->f_name, f_name) != 0))
    {
        tempPrev = temp;
        temp = temp->link;
    }
    if(temp != NULL)
        return FAILURE;
    tempPrev->link = new;
    printf("Successful: inserting file name : %s into file linked list\n",f_name);
    return SUCCESS;
}