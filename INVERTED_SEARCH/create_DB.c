#include "invertedIndex.h"

int create_DB(file_node_t *file_head, main_node_t **head_main, table* HT)
{
    /*traversing through the filenames*/
    while(file_head)
    {
        read_datafile(file_head, head_main, file_head->f_name, HT);
        file_head = file_head->link;
    }
    return SUCCESS;
}
int read_datafile(file_node_t *file_head, main_node_t ** head_main, char *f_name, table* HT)
{
    char buffer[BUFF_SIZE];
    int index;
    
    FILE* fptr = fopen(file_head->f_name, "r");
    while (fscanf(fptr, "%s", buffer)!=EOF)
    {
        /*Making the string as case insensitive*/
        //toLower(buffer);
        
        index = tolower(buffer[0])%97;
        if (index>25 || index<0)
            index = 26;
            
        //printf("Word is %s index = %d\n", buffer, index);
        /*If the index is empty */
        if (HT[index].mlink==NULL)
        {
            main_node_t* new = malloc(sizeof(main_node_t));
            if(new == NULL)
                return FAILURE;
            new->f_count = 1;
            new->link = NULL;
            new->sub_link = NULL;
            strcpy(new->word, buffer);
            HT[index].mlink = new;
            update_sub_node(&(HT[index].mlink), f_name);
            
        }
        else    /*If index is not empty*/
        {
            main_node_t* temp = HT[index].mlink;
            while ((strcmp(temp->word, buffer)!=0) && temp->link != NULL)
                temp = temp->link;
                    
            /* Reached to the last */
            if(temp->link == NULL)
            {
                /*If the last word matched*/
                if(strcmp(temp->word, buffer)==0)
                    update_sub_node(&temp, f_name);
                else /* If last word is also not matched*/
                {
                    insert_at_last_main(&temp, buffer, f_name); 
                }
            }
            else /*If found in between*/
            {
                update_sub_node(&temp, f_name);
            }
        }
        fgetc(fptr);
    }
    fclose(fptr);
        
}
int insert_at_last_main(main_node_t **head, char *word, char* f_name)
{
    main_node_t* new = malloc(sizeof(main_node_t));
    if(new == NULL)
        return FAILURE;
    new->f_count = 1;
    new->link = NULL;
    new->sub_link = NULL;
    strcpy(new->word, word);
    (*head)->link = new;
    /*new address get passed*/
    update_sub_node(&new, f_name);
    
}
int update_sub_node(main_node_t **main_node, char* f_name)
{
    sub_node_t* subNew = malloc(sizeof(sub_node_t));
    if (subNew == NULL)
        return FAILURE;

    strcpy(subNew->f_name, f_name);
    subNew->link = NULL;

    /*If there is no sub node initially*/
    if ((*main_node)->sub_link == NULL)
    {
        subNew->w_count = 1;
        (*main_node)->sub_link = subNew;
        return SUCCESS;
    }

    /*If there is multiple sub nodes present*/
    sub_node_t* temp = (*main_node)->sub_link;
    while (temp->link!=NULL && (strcmp(temp->f_name, f_name)!=0))
        temp = temp->link;

    /*If its last node*/
    if(temp->link == NULL)
    {
        /*Last node is also not matching with file name*/

        if(strcmp(temp->f_name, f_name)!=0)
        {
            (*main_node)->f_count++; 
            subNew->w_count = 1;
            temp->link = subNew;
            return SUCCESS;
        }
        else // last node matching then updating the word count in the file node
        {
            update_word_count(temp, f_name);
            free(subNew);
        }
    }
    else/* If file name matched */
    {
        update_word_count(temp, f_name);
        free(subNew);
    }
}

int update_word_count(sub_node_t* sub_node, char *fname)
{
    sub_node->w_count++;
}

int toLower(char *str)
{
    for(int i=0; str[i]; i++)
        str[i] = tolower(str[i]);
}