#include "invertedIndex.h"

int search_DB(table *HT, char *word)
{
    int index = tolower(word[0])%97;
    if (index<0 || index>25)
        index = 26;
    main_node_t* temp;
    sub_node_t* tempSub;
    temp = HT[index].mlink;
    if(temp == NULL)
    {
        return NOT_PRESENT;
    }
    while(temp != NULL && (strcmp(temp->word, word)!=0))/*Checking index not empty*/
        temp = temp->link;

    /*word not found*/
    if(temp == NULL)
        return NOT_PRESENT;
    /*If word found*/
    printf("Word %s is present in %d files\n", word, temp->f_count);
    tempSub = temp->sub_link;
    while(tempSub)
    {
        printf("In file: %s %d time/s\n", tempSub->f_name, tempSub->w_count);
        tempSub = tempSub->link;
    }
    return SUCCESS;
}
/*INFO: Word is not found in database
  INFO: word %s is present in the %d times files*/