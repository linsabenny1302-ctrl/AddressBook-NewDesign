#include <stdio.h>
#include "contact.h"
#define RESET "\033[0m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define GREEN "\033[0;32m"

int main() 
{
    char choice;
    AddressBook addressBook;
    addressBook.contactCount = 0;
    loadContactsFromFile(&addressBook);
    //initialize(&addressBook); // Initialize the address book

    do 
    {
        printf(CYAN"\nAddress Book Menu:\n"RESET);
        printf(CYAN"1. Create contact\n"RESET);
        printf(CYAN"2. Search contact\n"RESET);
        printf(CYAN"3. Edit contact\n"RESET);
        printf(CYAN"4. Delete contact\n"RESET);
        printf(CYAN"5. List all contacts\n"RESET);
        printf(CYAN"6. Exit\n"RESET);
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);
        
        switch (choice) 
        {
            case '1':
                createContact(&addressBook);
                break;
            case '2':
                searchContact(&addressBook);
                break;
            case '3':
                editContact(&addressBook);
                break;
            case '4':
                deleteContact(&addressBook);
                break;
            case '5':
                char sortChoice;
                do
                {
                    printf(BLUE"Select sort criteria:\n"RESET);
                    printf(BLUE"1. Sort by name\n"RESET);
                    printf(BLUE"2. Sort by phone\n"RESET);
                    printf(BLUE"3. Sort by email\n"RESET);
                    printf("\nEnter your choice: ");
                    scanf(" %c", &sortChoice);
                    listContacts(&addressBook, sortChoice);
                }while(sortChoice != '1' && sortChoice != '2' && sortChoice != '3');
                break;
            case '6':
                printf(GREEN"\nSaving and Exiting...\n"RESET);
                saveContactsToFile(&addressBook);
                break;
            default:
                printf(RED"\nInvalid choice. Please try again😑\n"RESET);
        }
    } while (choice != '6');
    
       return 0;
}
