#include <stdio.h>
#include "file.h"
#include <string.h>

void saveContactsToFile(AddressBook *addressBook) {
    FILE* fptr = fopen("contacts.csv", "w");
    if (fptr == NULL) {   
        printf("The file not opened 😓😓\n");
        return;
    }

    fprintf(fptr, "Name,Phone,Email\n"); // header for csv file
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fptr, "%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.csv", "r");
    if (fptr == NULL) {
        printf("The file not opened 😓😓\n");
        return;
    }

    char line[256];
    addressBook->contactCount = 0;

    // Skip header
    fgets(line, sizeof(line), fptr);

    while (fgets(line, sizeof(line), fptr)) {
        line[strcspn(line, "\n")] = '\0';

        char name[50], phone[20], email[50];
        if (sscanf(line, "%49[^,],%19[^,],%49s\n", name, phone, email) == 3) {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);
            strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
            strcpy(addressBook->contacts[addressBook->contactCount].email, email);
            addressBook->contactCount++;
        }
    }

    fclose(fptr);
}

