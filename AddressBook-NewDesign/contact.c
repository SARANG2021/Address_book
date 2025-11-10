#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>

//--------------------------------------------------------------------------------------------------------------------------------->
void sortbyname(AddressBook* addressBook) {
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
            if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) > 0) {
                // Swap entire struct
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }

    // Print sorted list
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("||---------------------------------------||\n");
        printf("%s\n", addressBook->contacts[i].name);
        printf("%s\n", addressBook->contacts[i].phone);
        printf("%s\n", addressBook->contacts[i].email);
        printf("||---------------------------------------||\n");
    }
}

void sortbyphone(AddressBook* addressBook){
    for(int i = 0; i < addressBook->contactCount; i++){
        for(int j = 0; j < addressBook->contactCount-i-1; j++){
            if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone) > 0){
                // Swap entire struct
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
    for(int i = 0; i < addressBook->contactCount; i++){
        printf("||---------------------------------------||\n");
        printf("%s\n", addressBook->contacts[i].name);
        printf("%s\n", addressBook->contacts[i].phone);
        printf("%s\n", addressBook->contacts[i].email);
        printf("||---------------------------------------||\n");
    }
}

void sortbyemail(AddressBook* addressBook){
    for(int i = 0; i < addressBook->contactCount; i++){
        for(int j = 0; j < addressBook->contactCount-i-1; j++){
            if(strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email) > 0){
                // Swap entire struct
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
    for(int i = 0; i < addressBook->contactCount; i++){
        printf("||---------------------------------------||\n");
        printf("%s\n", addressBook->contacts[i].name);
        printf("%s\n", addressBook->contacts[i].phone);
        printf("%s\n", addressBook->contacts[i].email);
        printf("||---------------------------------------||\n");
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    int criteria;
    do{
    printf("Enter the criteria for listing:\n1.Name\n2.Phone\n3.Email\n");
    scanf("%d", &criteria);
    }while(!(criteria >=1 && criteria <= 3));
    
    switch(criteria){
        case 1:
            sortbyname(addressBook);
            break;
        case 2:
            sortbyphone(addressBook);
            break;
        case 3:
            sortbyemail(addressBook);
            break;
        default:
            printf("Wrong input.\n");

    }

}

//-------------------------------------------------------------------------------------------------------------------------------->
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
//-------------------------------------------------------------------------------------------------------------------------------->
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int check_name(char* name_str){
int n = 0, alphacount = 0;
while(name_str[n]){
if(!(isalpha(name_str[n]) || name_str[n] == ' ' || name_str[n] == '.')){
    printf("❗INVAILD INPUT❗\n");
    return 1;
}
if(isalpha(name_str[n]))
    ++alphacount;
n++;
}
if(!alphacount){
    printf("❗INVAILD INPUT❗\n");
    return 1;
}
return 0;  
}

int check_phone(char* phone, AddressBook* addressBook){
int n = 0;

for(int i = 0; i < addressBook->contactCount; i++){
    if(!strcmp(phone, addressBook->contacts[i].phone)){
        printf("❌❌ DUPLICATE PHONE NUMBER FOUND!! ❌❌\n");
        return 1;
    }
}
if(phone[0] == '0'){
    printf("❗INVAILD INPUT❗\n");
    return 1;
}
while(phone[n]){
    if(!(isdigit(phone[n]))){
        printf("❗INVAILD INPUT❗\n");
        return 1;
    }
n++;
}
if(n != 10){
    printf("❗INVAILD INPUT❗\n");
    return 1;
}
return 0;
}

int check_email(char* email, AddressBook* addressBook){
    int n = 0, atcount = 0, dotcount;

    for(int i = 0; i < addressBook->contactCount; i++){
    if(!strcmp(email, addressBook->contacts[i].email)){
        printf("❌❌ DUPLICATE EMAIL-ID FOUND!! ❌❌\n");
        return 1;
    }
}
    while(email[n]){
        if(!(islower(email[n]) || isdigit(email[n]) || email[n] == '@' || email[n] == '.' || email[n] == '_')){
            printf("❗INVAILD INPUT❗\n");
            return 1;
        }
        if(email[n] == '@'){
            atcount++;
            if(email[0] == '@' && email[strlen(email)-1] == '@'){
                printf("❗INVAILD INPUT❗\n");
                return 1;
            }
        }
        if(email[n] == '.'){
            dotcount++;
            if(email[0] == '.' || email[strlen(email)-1] == '.'){
                printf("❗INVAILD INPUT❗\n");
                return 1;
            }
        }
    n++;
    }

    if(atcount != 1)
        return 1;

    char* ptr = strchr(email, '@');
    if(strchr(ptr, '.') == NULL){
        printf("❗INVAILD INPUT❗\n");
        return 1;
    }

return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createContact(AddressBook *addressBook)
{
/* Define the logic to create a Contacts */
// char name_str[20], phone[11], email[30]
char name_str[20];
char phone[11];
char email[30];
do{
printf("Enter the name:");
scanf(" %[^\n]", name_str);
}while(check_name(name_str));
strcpy(addressBook->contacts[addressBook->contactCount].name , name_str);
//get phone num and validate
do{
printf("Enter the phone number:");
scanf("%s", phone);
}while(check_phone(phone, addressBook));
strcpy(addressBook->contacts[addressBook->contactCount].phone , phone);
//get the mail and validate
do{
printf("Enter the email-id:");
scanf("%s", email);
}while(check_email(email, addressBook));
strcpy(addressBook->contacts[addressBook->contactCount].email , email);
printf("Contact created sucessfully 😊😊\n");
addressBook->contactCount++;
}

//------------------------------------------------------------------------------------------------------------------------------->
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int searchContactAndSelect(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) {
        printf("❌ No contacts available!\n");
        return -1;
    }

    int option;
    do {
        printf("Search by:\n1. Name\n2. Phone\n3. Email\n");
        scanf("%d", &option);
    } while (!(option >= 1 && option <= 3));

    char query[30];
    printf("Enter search text 🔍: ");
    scanf(" %[^\n]", query);

    int matches[100]; // store actual indices of matched contacts
    int matchCount = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        int found = 0;
        if (option == 1 && strstr(addressBook->contacts[i].name, query)) found = 1;
        if (option == 2 && strstr(addressBook->contacts[i].phone, query)) found = 1;
        if (option == 3 && strstr(addressBook->contacts[i].email, query)) found = 1;

        if (found) {
            matchCount++;
            matches[matchCount] = i; // store real index
            printf("%d.\n", matchCount);
            printf("%s\n", addressBook->contacts[i].name);
            printf("%s\n", addressBook->contacts[i].phone);
            printf("%s\n", addressBook->contacts[i].email);
            printf("------------------------------------->\n");
        }
    }

    if (matchCount == 0) {
        printf("😓 No matches found!\n");
        return -1;
    }

    int choice;
    printf("Enter the number of the contact to select (1-%d): ", matchCount);
    scanf("%d", &choice);

    if (choice < 1 || choice > matchCount) {
        printf("❌ Invalid selection!\n");
        return -1;
    }

    return matches[choice]; // return actual index
}

//-------------------------------------------------------------------------------------------------------------------------------->
void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) {
        printf("❌ No contacts to edit!\n");
        return;
    }

    int idx = searchContactAndSelect(addressBook);
    if (idx == -1) return; // no valid selection

    int choice;
    do {
        printf("Enter the field you want to edit:\n1. Name\n2. Phone\n3. Email\n");
        scanf("%d", &choice);

        char name_str[20], phone[11], email[30];

        if (choice == 1) {
            do {
                printf("Enter the new name: ");
                scanf(" %[^\n]", name_str);
            } while (check_name(name_str));
           char a;
           printf("Are you sure Y/N: ");
           scanf(" %c", &a);
           if(a == 'Y'){   
            strcpy(addressBook->contacts[idx].name, name_str);
            printf("✅ Name edited successfully!\n");
           }
           else 
                return;
        } 
        else if (choice == 2) {
            do {
                printf("Enter the new phone number: ");
                scanf("%s", phone);
            } while (check_phone(phone, addressBook));
           char a;
           printf("Are you sure Y/N: ");
           scanf(" %c", &a);
           if(a == 'Y'){   
            strcpy(addressBook->contacts[idx].phone, phone);
            printf("✅ Phone number edited successfully!\n");
           }
           else 
                return;
            
        } 
        else if (choice == 3) {
            do {
                printf("Enter the new email-id: ");
                scanf("%s", email);
            } while (check_email(email, addressBook));
           char a;
           printf("Are you sure Y/N: ");
           scanf(" %c", &a);
           if(a == 'Y'){   
            strcpy(addressBook->contacts[idx].email, email);
            printf("✅ Email-id edited successfully!\n");
           }
           else 
                return;
        } 
        else {
            printf("❌ Invalid choice!\n");
        }
    } while (!(choice >= 1 && choice <= 3));
}


//-------------------------------------------------------------------------------------------------------------------------------->    

void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) {
        printf("❌ No contacts to delete!\n");
        return;
    }

    int idx = searchContactAndSelect(addressBook);
    if (idx == -1) return; // no valid selection
    char a;
    printf("Are you sure Y/N: ");
    scanf(" %c", &a);
    if(a == 'Y'){
    for (int i = idx; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }

    addressBook->contactCount--;
}
    else
        return;

    printf("✅ Contact deleted successfully!\n");
}
