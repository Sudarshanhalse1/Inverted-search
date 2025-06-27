#include "invertedIndex.h"
 
int update_DB(file_node_t **head, table* HT)
{
    /* Read the backupt fule name*/
    printf("Enter the file name to update database: ");
    char f_name[30];
    scanf("%s", f_name);
    if(validate_bck_file(f_name)==FAILURE)
        return FAILURE;
    /*Now validate it is the backup file*/
    /* 
       Now I am creating the temp ll which can store the only unique file names from the backup file 
       Which can be further used for the comparison with the main linked list and modifieng it, and after all free the each node of temp
       Linked list.
    */
    file_node_t* temp = NULL;
    FILE* fp = fopen(f_name, "r");
    /*main logic to update db*/
    char word[BUFF_SIZE], file_name[30];
    int index, file_count, word_count;
    while(fscanf(fp, "#%d;%[^;];%d;",&index, word, &file_count)==3)
    {
        update_to_main_node(word, file_count, HT, index);

        for(int i=0; i<file_count; i++) 
            if(fscanf(fp, "%[^;];%d;", file_name, &word_count)==2)
                update_the_sub_node(word, file_count, file_name, word_count, HT[index].mlink, &temp);

        fgetc(fp);/* To remove the #*/
        fgetc(fp); /* To reove the \n*/    
    }
    puts("INFO: Data base updated");
    // printf("Files in the backup file are\n");
    // file_node_t* tempHead = temp;
    // while (tempHead)
    // {
    //    printf("%s->", tempHead->f_name);
    //    tempHead = tempHead->link;
    // }
    // printf("NULL\n");
    /* Remove the files present in the backup file from the CLA files*/
    Remove_Duplicate_Files_from_list(temp, head);
    //printf("Removing Done\n");
    free_list(&temp);

    return SUCCESS;

}
void free_list(file_node_t** temp)
{
    file_node_t* temp1;
    while (*temp)
    {
        temp1 = *temp;
        (*temp) = (*temp)->link;
        free(temp1);
    }
}
int Remove_Duplicate_Files_from_list(file_node_t* tempHead, file_node_t** fileHead)
{
    file_node_t* temp = *fileHead, *tempPrev = NULL;
    file_node_t* tempTemp = NULL;
    int removed = 0;
    while (temp)
    {
        
        tempTemp = tempHead;
        while (tempTemp)
        {
            if (strcmp(temp->f_name, tempTemp->f_name)==0)
            {
                remove_node(fileHead, &tempPrev);
                removed = 1;
                break;
            }
            tempTemp = tempTemp->link;
        }
        if (removed)
        {
            tempPrev = NULL;
            temp = *fileHead;
            removed = 0;
            continue;
        }
        
        tempPrev = temp;
        temp = temp->link;
    }
    return SUCCESS;
}
int remove_node(file_node_t** fileHead, file_node_t** tempPrev)
{
    file_node_t* temp = NULL;
    if ((*tempPrev)==NULL)
    {
        temp = *fileHead;   
        (*fileHead) = (*fileHead)->link;
        free(temp);
        return SUCCESS;
    }
    if ((*fileHead)->link == NULL)
    {
        free(*fileHead);
        (*fileHead) = NULL;
        return SUCCESS;
    }
    
    (*tempPrev)->link = (*fileHead)->link;
    free(*fileHead);
    return SUCCESS;
}
int update_the_sub_node(char* word, int file_count, char* file_name, int word_count, main_node_t* temp, file_node_t** tempHead)
{
    while(strcmp(temp->word, word)!=0)
    {
        temp = temp->link;
    }
    sub_node_t* new = malloc(sizeof(sub_node_t));
    strcpy(new->f_name, file_name);
    new->link = NULL;
    new->w_count = word_count;
    store_filenames_to_list(file_name, tempHead);
    if (temp->sub_link == NULL)
    {
        temp->sub_link = new;
        return SUCCESS;
    }
    
    /* traversing the sub nodes*/
    sub_node_t* temp1 = temp->sub_link;
    while (temp1->link)
        temp1 = temp1->link;
    temp1->link = new;
    return SUCCESS;
}
int update_to_main_node(char* word, int file_count, table* HT, int index)
{
    main_node_t* new = malloc(sizeof(main_node_t));
    if(new == NULL)
        return FAILURE;
    new->f_count = file_count;
    strcpy(new->word, word);
    if (HT[index].mlink== NULL)
    {
        HT[index].mlink = new;
        return SUCCESS;
    }
    main_node_t* temp = HT[index].mlink;
    while (temp->link)
        temp = temp->link;
    
    temp->link = new;
    return SUCCESS;
}
int validate_bck_file(char* f_name)
{
    /*check is it .txt file*/
    if (strstr(f_name, ".txt")!= NULL && (strcmp(strstr(f_name, ".txt"), ".txt")==0))
    {
        /*checking it is exist or not*/
        FILE* fptr = fopen(f_name, "r");
        if(fptr != NULL)
        {
            fseek(fptr, 0, SEEK_END);
            /*checking is it empty*/
            if(ftell(fptr) != 0)
            {
                /*checking is it backup file*/
                /*If the last and first character is # then it is a backup file*/
                char start_ch, end_ch, ch;
                fseek(fptr, 0, SEEK_SET);
                start_ch = fgetc(fptr);
                while(((ch = fgetc(fptr)) != EOF)&& ch != '\n'); /*as there will be atleast one \n in the file so first condition not 
                                                                    requierd, but to be safer side keeping that condition     */
                fseek(fptr, -2, SEEK_CUR);
                end_ch = fgetc(fptr);
                if(start_ch == end_ch)
                {
                    printf("INFO: yes it is a backup file\n");
                    return SUCCESS;
                }
                else
                {
                    printf("ERROR: NO, it is not a backup file\n");
                    return FAILURE;
                }

            }
            else
            {
                printf("INFO: %s File empty\n", f_name);
                fclose(fptr);
                return FAILURE;
            }
            
        }
        else
        {
            printf("ERROR: %s does not exist\n", f_name);
            return FAILURE;
        }
    }
    else
    {
        printf("ERROR: File is not \".txt\" format\n");
        return FAILURE;
    }
    

}