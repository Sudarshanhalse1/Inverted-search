#include "invertedIndex.h"
#include <unistd.h>
int save_DB(table* HT)
{
    printf("Enter the file name to save database: ");
    char f_name[30];
    scanf("%s", f_name);
    /*vslidation for the back up file*/
    if(validate_backup(f_name) == FAILURE)
        return FAILURE;
    /*opening file*/
    FILE* fp = fopen(f_name, "w");
    puts("Saving...");
    main_node_t* temp;
    sub_node_t* tempSub;
    /*Main logic for the save file*/
    for(int i=0; i<27; i++)
    {
        temp = HT[i].mlink;
        while(temp != NULL)
        {
            fprintf(fp, "#%d;%s;%d;", i, temp->word, temp->f_count);
            tempSub = temp->sub_link;
            while (tempSub->link)
            {
                fprintf(fp, "%s;%d;", tempSub->f_name, tempSub->w_count);
                tempSub = tempSub->link;
            }
            /*To print the last node data without semicolan*/
            fprintf(fp, "%s;%d", tempSub->f_name, tempSub->w_count);
            fputc('#', fp);
            fputc('\n', fp);
            temp = temp->link;
        } 
    }
    sleep(1);
    puts("Saved");
    fclose(fp);
}
int validate_backup(char* f_name)
{
    if (strstr(f_name, ".txt")!= NULL && (strcmp(strstr(f_name, ".txt"), ".txt")==0))
    {
        FILE* fp = fopen(f_name, "r");
        if (fp != NULL)
        {
           fseek(fp, 0, SEEK_END);
           if (ftell(fp)!=0)
           {
                char option;
                printf("Do you want to overwrite %s file\n", f_name);
                printf("y/Y for Yes and n/N for NO\n");
                scanf(" %c", &option);
                if(option=='y' || option=='Y')
                {
                    fclose(fp);
                    return SUCCESS;
                }
                else if (option=='n' || option=='N')
                {
                    fclose(fp);
                    return FAILURE;
                }
                else
                {
                    printf("Invalid Choice\n");
                    fclose(fp);
                    return FAILURE;
                }
           }
           else
           {
                return SUCCESS;
           }
           
        }
        else
        {
            return SUCCESS;
        }
    }
    else
    {
        printf("File is not \".txt\" format\n");
        return FAILURE;
    }
    
}