#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100//Macros

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void sortbyname(AddressBook* addressBook);
void sortbyphone(AddressBook* addressBook);
void sortbyemail(AddressBook* addressBook);
int searchContactAndSelect(AddressBook *addressBook);
int check_name(char* name_str);
int check_phone(char* phone, AddressBook* addressBook);
int check_email(char* email, AddressBook* addressBook);
void searchbyname(AddressBook *addressBook);
void searchbyphone(AddressBook *addressBook);
void searchbyemail(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
