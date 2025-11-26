#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100  //macro declaration

typedef struct {      //struct data type name is Contact
    char name[50];
    char phone[11];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, char sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void loadContactsFromFile(AddressBook *AddressBook);

#endif
