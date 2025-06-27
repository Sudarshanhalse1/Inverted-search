#include "invertedIndex.h"

int main(int argc, char* argv[])
{
    if(argc<2)
    {
        printf("INFO: No file found\n");
        return FAILURE;
    }
    file_node_t* fileHead = NULL;
    main_node_t* mainHead = NULL;
    /*calling the validation*/
    if(validate_n_store_filenames(&fileHead, argv)== SUCCESS)
    {
        printf("INFO: Validation is successfull\n");
    }
    else
    {
        printf("ERROR: Validation not successfull\n");
    }
    /*Creating the Hash table*/
    table HT[SIZE];
    init_HT(HT);
    int option;
    puts("---------------------------------------");
    puts("\t\tmain\t\t");
    puts("---------------------------------------");
    puts("\t1. Create DATABASE.");
    puts("\t2. Display DATABASE.");
    puts("\t3. Search.");
    puts("\t4. Update DATABASE.");
    puts("\t5. Save DATABASE.");
    puts("\t6. Exit");
    puts("Enter your choice: ");
    int cdb_flag =0, udb_flag = 0;
    while(1)
    {
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                if (cdb_flag == 0)
                {
                    if(create_DB(fileHead, &mainHead, HT)==SUCCESS)
                        puts("SUCCESSFUL: Data Base Created");
                    cdb_flag = 1;
                }
                else
                {
                    puts("INFO: Data base is up to date");
                }
            break;
            case 2:
                display_DB(HT);
            break;
            case 3:
            {
                printf("Enter the word you want to search: ");
                char buffer[BUFF_SIZE];
                scanf("%s", buffer);
                if(search_DB(HT, buffer)==NOT_PRESENT)
                {
                    printf("%s word is not found!\n", buffer);
                    return FAILURE;
                }
                    
            }
            break;
            case 4:
                if (udb_flag == 0 && cdb_flag == 0) /* For the error handling */
                {
                    if(update_DB(&fileHead, HT)==FAILURE)
                    {
                        break;
                    }
                    udb_flag = 1;  
                }
                else
                {
                    puts("INFO: Data Base is Up to Date");
                }
                
            break;
            case 5:
                if(save_DB(HT)== FAILURE)
                {
                    printf("ERROR: failure in saving file\n");
                    return FAILURE;
                }
                    
                
            break;
            case 6:
                return SUCCESS;
            break;
            default:
            puts("Invalid choice");
        }
    }
    /*printing the list*/
    file_node_t* temp = fileHead;
    printf("head-> ");
    while(temp)
    {
        printf("%s -> ", temp->f_name);
        temp = temp->link;
    }
    printf("NULL\n");

}
void init_HT(table* HT)
{
    for(int i=0; i<27; i++)
    {
        HT->index = i;
        HT->mlink = NULL;
    }
}