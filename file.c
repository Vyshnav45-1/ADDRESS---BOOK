#include <stdio.h>
#include "file.h"
// Function to save all contacts from memory to a CSV file
void saveContactsToFile(AddressBook *addressBook) {
   // Open file in write mode
    FILE* fptr1=fopen("contacts.csv","w");
    // First line stores the number of contacts
    fprintf(fptr1,"%d\n",addressBook->contactCount);
    // Write each contact in CSV format: name,phone,email
    for (int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr1,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
  // Close the file
  fclose(fptr1);
}
// Function to load contacts from a CSV file into memory
void loadContactsFromFile(AddressBook *addressBook) {
    // Open the file in read mode
     FILE* fptr=fopen("contacts.csv","r");
     // Read the number of contacts from the first line
     fscanf(fptr,"%d",&addressBook->contactCount);
     int i;
     // Read each contact line-by-line
     for (i=0;i<=addressBook->contactCount;i++)
     {
        fseek(fptr,1,SEEK_CUR);
        fscanf(fptr," %[^,]",addressBook->contacts[i].name);
        fseek(fptr,1,SEEK_CUR);
        fscanf(fptr," %[^,]",addressBook->contacts[i].phone);
        fseek(fptr,1,SEEK_CUR);
        fscanf(fptr," %[^\n]",addressBook->contacts[i].email);


     }
     // Close the file
     fclose(fptr);
    
}
