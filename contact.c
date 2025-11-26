#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

#define RESET "\033[0m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define GREEN "\033[0;32m"

void listContacts(AddressBook *addressBook, char sortCriteria) 
{
    // Sort contacts based on the chosen criteria

    switch(sortCriteria)
    {
        case '1':
        for(int i = 0;i < addressBook -> contactCount - 1;i++)
        {
            for(int j = 0;j < addressBook -> contactCount - 1 - i;j++)
            {
                if(strcasecmp(addressBook -> contacts[i].name,addressBook -> contacts[i + 1].name) > 0)
                {
                    Contact temp = addressBook -> contacts[j];
                    addressBook -> contacts[j] = addressBook -> contacts[j + 1];
                    addressBook -> contacts[j + 1] = temp;
                    
                }
            }
        }

        break;

        case '2':
        for(int i = 0;i < addressBook -> contactCount - 1;i++)
        {
            for(int j = 0;j < addressBook -> contactCount - 1 - i;j++)
            {
                if(strcasecmp(addressBook -> contacts[i].phone,addressBook -> contacts[i + 1].phone) > 0)
                {
                    Contact temp = addressBook -> contacts[j];
                    addressBook -> contacts[j] = addressBook -> contacts[j + 1];
                    addressBook -> contacts[j + 1] = temp;
                    
                }
            }
        }

        break;

        case '3':
        for(int i = 0;i < addressBook -> contactCount - 1;i++)
        {
            for(int j = 0;j < addressBook -> contactCount - 1 - i;j++)
            {
                if(strcasecmp(addressBook -> contacts[i].email,addressBook -> contacts[i + 1].email) > 0)
                {
                    Contact temp = addressBook -> contacts[j];
                    addressBook -> contacts[j] = addressBook -> contacts[j + 1];
                    addressBook -> contacts[j + 1] = temp;
                    
                }
            }
        }

        break;

        default:
        printf(RED"\nInvalid Choice. Please try again😑!\n"RESET);
        return;
    }

    printf("\n---------------------->CONTACT DETAILS<--------------------------\n");
    printf("-------------------------------------------------------------------\n");
    printf("| S.no\t| Name\t\t| Phone\t\t| Email                   |\n");
    for(int i = 0; i < addressBook -> contactCount;i++)
    {
        printf("-------------------------------------------------------------------\n");
        printf("| %d.\t| %s\t| %s\t| %s \t  |\n",i + 1,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
        
    }
    
     printf("-------------------------------------------------------------------\n");
    
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validate_name(char *name)
{
    int len = strlen(name);

    int i = 0;

    if(isalpha(name[i]))
    {
        i++;
    }
    else
    {
        return 1;
    }

    while(name[i] != '\0')
    {
        if(isalpha(name[i]) || name[i] == ' ' || name[i] == '.' )
        {
            i++;
        }
        else
        {
            return 1;
        }
    }

    return 0;

}

int validate_mob_num(char *phone,AddressBook *addressBook)
{
    int len = strlen(phone);

    if(len != 10)
        return 1;

    for(int i = 0;i < len;i++)
    {
        if(!isdigit(phone[i]))
        {
            return 1;
        }
        
    }

    return 0;

}

int validate_email(char *email,AddressBook *addressBook)
{
    if(!(isalpha(email[0])))
        return 1;

    for(int i = 0;email[i] != '\0';i++)
    {
        if(isupper(email[i]))
        {
            return 1;
        }
    }

    int count= 0;

    for(int i = 0;email[i] != '\0';i++)
    {
        if(email[i] == '@')
        {
           count++;
        }
    }

    if(count > 1)
    {
        return 1;
    }    

    char *at = strchr(email,'@');
    char *dot = strstr(email,".com");
    char *dotdot = strstr(email,"..");

    if(at == NULL || dot == NULL || dotdot != NULL)
    {
        return 1;
    }

    if(strcmp(dot,".com") != 0)
    {
        return 1;
    }

    if(dot < at)
    {
        return 1;
    }

    if(!(isalpha(*(at + 1))))
    {
        return 1;
    }

    return 0;
}

void createContact(AddressBook *addressBook)
{
    //step1: read the name and validate it

    char name[50];

    int res;

    do
    {
        printf("Enter the name : ");
        scanf(" %[^\n]",name);

        res = validate_name(name);

        //step2: if valid goto step3,if not valid print error and go to step1

        if(res == 1)
        {
            printf(RED"\nInvalid Name. Please try again!😑\n"RESET);
        }

    }while(res != 0);

    //step3: read the mobile number and validate it

    char phone[11];

    do
    {
        printf("Enter the mobile number : ");
        scanf(" %[^\n]",phone);

        res = validate_mob_num(phone,addressBook);

        //step4: if valid goto step5,if not valid print error and go to step3

        if(res == 1)
        {
            printf(RED"\nInvalid Phone Number. Please try again!😑\n"RESET);
        }

        
        for(int i = 0;i < addressBook -> contactCount;i++)
        {
            if(strcmp(addressBook -> contacts[i].phone,phone) == 0)
            {
                printf(YELLOW"\nPhone number already exists😑!\n"RESET);
                res = 1;
            }
        }

    }while(res != 0);


    //step5: read the email id and validate it

    char email[50];

    do
    {
        printf("Enter the email id : ");
        scanf(" %[^\n]",email);

        res = validate_email(email,addressBook);

        //step6: if valid goto step7,if not valid print error and go to step5
        
        if(res == 1)
        {
            printf(RED"\nInvalid Email ID. Please try again!😑\n"RESET);
        }

        for(int i = 0;i < addressBook -> contactCount;i++)
        {
            if(strcmp(addressBook -> contacts[i].email,email) == 0)
            {
                printf(YELLOW"\nEmail already exists😑!\n"RESET);
                res = 1;
            }
        }
    }while(res != 0);

    //step7: store the contact details in address book

    strcpy(addressBook -> contacts[addressBook -> contactCount].name,name);
    strcpy(addressBook -> contacts[addressBook -> contactCount].phone,phone);
    strcpy(addressBook -> contacts[addressBook -> contactCount].email,email);

    (addressBook -> contactCount)++;

    printf(GREEN"\n***CONTACT SAVED SUCCESSFULLY🎉🎉🎉***\n"RESET);
}

int search_by_phone(AddressBook *addressBook,char *phone)
{
    int index;
    int count = 0;
    for(int i = 0;i < addressBook -> contactCount;i++)
    {
        if(strcmp((addressBook -> contacts[i].phone),phone) == 0)
        {
            index = i;
            count++;
        }
    }
    
    if(count == 0)
    {
        printf(RED"\nNo Contact Found😑!\n"RESET);
        return -1;
    }
    else if(count == 1)
    {
        return index;
    }
}

int search_by_email(AddressBook *addressBook,char *email)
{
    int count = 0;
    for(int i = 0;i < addressBook -> contactCount;i++)
    {
        if(strcasecmp((addressBook -> contacts[i].email),email) == 0)
        {
            count = 1;
            return i;
        }
    }
    
    if(count == 0)
    {
        printf(RED"\nNo Contact Found😑!\n"RESET);
        return -1;
    }
   
}


int search_by_name(AddressBook *addressBook,char *name)
{
    int index;
    int match_index[addressBook -> contactCount];
    int count = 0;
    for(int i = 0;i < addressBook -> contactCount;i++)
    {
        if(strcasestr((addressBook -> contacts[i].name),name) != NULL)
        {
            match_index[count] = i;
            count++;
           
        }
    }
    
    if(count == 0)
    {
        printf(RED"\nNo Contact Found😑!\n"RESET);
        return -1;
    }
    else if(count == 1)
    {
        printf(GREEN"\n***CONTACT FOUND***\n"RESET);
        printf("\n---------->CONTACT DETAILS<----------\n");
        printf("%d. Name      : %s\n",count,addressBook -> contacts[match_index[0]].name);
        printf("   Mobile No. : %s\n",addressBook -> contacts[match_index[0]].phone);
        printf("   Email id.  : %s\n",addressBook -> contacts[match_index[0]].email);
        return match_index[0]; 
    }
    else if(count > 1)
    {
        char ch;
        int serial_num;
        char phone[11], email[50];
        printf(GREEN"\n***MULTIPLE CONTACTS FOUND***\n"RESET);
        printf("\n---------->CONTACT DETAILS<----------\n");

        for(int i = 0;i < count;i++)
        {
            printf("%d. Name      : %s\n",i + 1,addressBook -> contacts[match_index[i]].name);
            printf("   Mobile No. : %s\n",addressBook -> contacts[match_index[i]].phone);
            printf("   Email id.  : %s\n",addressBook -> contacts[match_index[i]].email);
        }

        do
        {
            printf(BLUE"\nPlease select the search criteria\n"RESET);
            printf(BLUE"1. Search by Phone number\n2. Search by Email\n3. Search by Serial number\n"RESET);
            printf("\nEnter the choice : ");
            scanf(" %c",&ch);

            switch(ch)
            {
                case '1':
                    printf("Enter the phone number : ");
                    scanf(" %s",phone);

                    index = search_by_phone(addressBook,phone);
    
                    if(index != -1)
                    {
                    printf(GREEN"\n***CONTACT FOUND***\n"RESET);
                    printf("\n---------->CONTACT DETAILS<----------\n");
                    printf("Name       : %s\n",addressBook -> contacts[index].name);
                    printf("Mobile No. : %s\n",addressBook -> contacts[index].phone);
                    printf("Email id.  : %s\n",addressBook -> contacts[index].email);
                    }

                    return index;

                    break;
                case '2':
                    printf("Enter the Mail id : ");
                    scanf(" %s",email);

                    index = search_by_email(addressBook,email);
    
                    if(index != -1)
                    {
                    printf(GREEN"\n***CONTACT FOUND***\n"RESET);
                    printf("\n---------->CONTACT DETAILS<----------\n");
                    printf("Name       : %s\n",addressBook -> contacts[index].name);
                    printf("Mobile No. : %s\n",addressBook -> contacts[index].phone);
                    printf("Email id   : %s\n",addressBook -> contacts[index].email);
                    }

                    return index;

                    break;
                case '3':
                    printf("Enter the Serial No. : ");
                    scanf("%d",&serial_num);
    
                    if(serial_num > 0 & serial_num <= count)
                    {
                        printf(GREEN"\n***CONTACT FOUND***\n"RESET);
                        printf("\n---------->CONTACT DETAILS<----------\n");
                        printf("Name       : %s\n",addressBook -> contacts[match_index[serial_num - 1]].name);
                        printf("Mobile No. : %s\n",addressBook -> contacts[match_index[serial_num - 1]].phone);
                        printf("Email id   : %s\n",addressBook -> contacts[match_index[serial_num - 1]].email);
                        return serial_num - 1;
                    }
                    else
                    {
                        printf(RED"\nInvalid Seial number😑\n"RESET);
                        return -1;
                    }
                    
                    break;
                default:
                    printf(RED"\nInvalid choice. Please try again😑!\n"RESET);
            }
            
        }while(ch != '1' && ch != '2' && ch != '3');
    }
    
}

int searchContact(AddressBook *addressBook) 
{
    char name[20];
    char phone[20];
    char email[50];

    char choice;
    int index;

    do
    {
        printf(BLUE"\nSelect Search criteria\n"RESET);
        printf(BLUE"1.Search by Name\n"RESET);
        printf(BLUE"2.Search by Phone\n"RESET);
        printf(BLUE"3.Search by Email\n"RESET);

        printf("\nEnter the choice : ");
        scanf(" %c",&choice);

        switch(choice)
        {
            int res;

            case '1':
                do
                {
                    printf("Enter the Name : ");
                    scanf(" %[^\n]",name);
                    
                    res = validate_name(name);

                    if(res == 1)
                    {
                        printf(RED"\nInvalid name. Please try again😑!\n"RESET);
                    }

                }while(res == 1);
                index = search_by_name(addressBook,name);
                break;

            case '2':
                do
                {
                    printf("Enter the Phone number : ");
                    scanf(" %[^\n]",phone);
                    
                    res = validate_mob_num(phone,addressBook);

                    if(res == 1)
                    {
                        printf(RED"\nInvalid Phone number. Please try again😑!\n"RESET);
                    }

                }while(res == 1);

                index = search_by_phone(addressBook,phone);

                if(index != -1)
                {
                    printf(GREEN"\n***CONTACT FOUND***\n"RESET);
                    printf("\n--------->CONTACT DETAILS<---------\n");
                    printf("Name       : %s\n",addressBook -> contacts[index].name);
                    printf("Mobile No. : %s\n",addressBook -> contacts[index].phone);
                    printf("Email id.  : %s\n",addressBook -> contacts[index].email);
                }
                break;
            
            case '3':
                do
                {
                    printf("Enter the Email id : ");
                    scanf(" %[^\n]",email);
                    
                    res = validate_email(email,addressBook);

                    if(res == 1)
                    {
                        printf(RED"\nInvalid Email id. Please try again😑!\n"RESET);
                    }

                }while(res == 1);

                index = search_by_email(addressBook,email);

                if(index != -1)
                {
                    printf(GREEN"\n***CONTACT FOUND***\n"RESET);
                    printf("\n--------->CONTACT DETAILS<---------\n");
                    printf("Name       : %s\n",addressBook -> contacts[index].name);
                    printf("Mobile No. : %s\n",addressBook -> contacts[index].phone);
                    printf("Email id.  : %s\n",addressBook -> contacts[index].email);
                }

                break;

            default:
                printf(RED"\nInvalid Input. Please try again😑!\n"RESET);
                
        }

    }while(choice != '1' && choice != '2' && choice != '3');

    return index;
}

void editContact(AddressBook *addressBook)
{
    printf("\nWhich contact do you want to edit?\n");
    int index = searchContact(addressBook);
    char choice;
    char name[50],phone[11],mail[50];

    do
    {
        printf(BLUE"\nWhat do you want to edit?\n"RESET);
        printf(BLUE"1. Name\n2. Phone number\n3. Email id\n"RESET);
        printf("\nEnter your choice : ");
        scanf(" %c",&choice);
        int res;

        switch(choice)
        {
            case '1':
                printf("Enter the new name :");
                scanf(" %[^\n]",name);
                res = validate_name(name);

                if(res == 1)
                {
                    printf(RED"\nInvalid name. Please try again😑!\n"RESET);
                    break;
                }

                strcpy(addressBook -> contacts[index].name,name);

                printf(GREEN"\n***NEW NAME IS SAVED SUCCESSFULLY🎉🎉🎉***\n"RESET);

                break;
            
            case '2':
                printf("Enter the new phone number :");
                scanf(" %s",phone);
                res = validate_mob_num(phone,addressBook);

                if(res == 1)
                {
                    printf(RED"\nInvalid input. Please try again😑!\n"RESET);
                    break;
                }

                strcpy(addressBook -> contacts[index].phone,phone);

                printf(GREEN"\n***NEW PHONE NUMBER IS SAVED SUCCESSFULLY🎉🎉🎉***\n"RESET);

                break;

            case '3':
                printf("Enter the new Email id :");
                scanf(" %s",mail);
                res = validate_email(mail,addressBook);

                if(res == 1)
                {
                    printf(RED"\nInvalid input. Please try again😑!\n"RESET);
                    break;
                }

                strcpy(addressBook -> contacts[index].email,mail);

                printf(GREEN"\n***NEW EMAIL ID IS SAVED SUCCESSFULLY🎉🎉🎉***\n"RESET);

                break;

            default:
                printf(RED"\nInvalid Choice. Please try again😑!\n"RESET);
                

        }
    }while(choice != '1' && choice != '2' && choice != '3');
     
}

void deleteContact(AddressBook *addressBook)
{
	printf("\nWhich contact do you want to delete?\n");
    int index = searchContact(addressBook);
    char res;
    if(index == -1)
    {
        return;
    }
    printf("\nAre you sure you want to delete? -> (Y/N)\n");
    scanf(" %c",&res);


    do
    {
        if(res == 'Y')
        {
            for(int i = index;i < addressBook -> contactCount;i++)
            {
                addressBook -> contacts[i] = addressBook -> contacts[i + 1];
            }

            printf(GREEN"\n***CONTACT DELETED SUCCESSFULLY***\n"RESET);

            addressBook -> contactCount--;
        }
        else if(res == 'N')
        {
            printf(YELLOW"***CONTACT IS NOT DELETED!***\n"RESET);
        }
        else
        {
            printf(RED"Invalid choice. Please try again😑!\n"RESET);
        }
    }while(res != 'Y' && res != 'N');

   
}
