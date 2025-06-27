#include "invertedIndex.h"

int display_DB(table* HT)
{
    main_node_t* temp;
    sub_node_t* tempSub;
    puts("----------------------------------------------");
    puts("Index\tword\t\t\tfile count");
    puts("----------------------------------------------\n");
    for(int i=0; i<27; i++) /*Traversing the hash table*/
    {
        temp = HT[i].mlink;
        while(temp != NULL)/*Checking index not empty*/
        {
            
            tempSub = temp->sub_link;
            printf("[%d]\t[ %-10s ]\t%12d\t", i, temp->word, temp->f_count);

            while(tempSub!=NULL)/*Traversing the sub nodes based on the file count in the main node*/
            {
                printf("%s\t%d\t", tempSub->f_name, tempSub->w_count);
                tempSub = tempSub->link;
            }
            putchar('\n');
            temp = temp->link;
        }
    }
    puts("\n----------------------------------------------\n");
}