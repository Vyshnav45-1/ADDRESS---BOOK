#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Function to list all contacts with optional sorting
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    Contact temp;
    if(sortCriteria == 1)
    {
        printf("\nContacts sorted by name:\n");  
        printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
        for(int i=0;i<(addressBook->contactCount)-1;i++)
        {
            for(int j=0;j<(addressBook->contactCount)-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Sorted by Name\n");
        
    }
    else if(sortCriteria == 2)
    {
        printf("\nContacts sorted by phone:\n");
        printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
        for(int i=0;i<(addressBook->contactCount)-1;i++)
        {
            for(int j=0;j<(addressBook->contactCount)-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone) > 0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
            
        }
        printf("Sorted by Phone\n");
        
    }
    else if(sortCriteria == 3)
    {
        printf("\nContacts sorted by email:\n");
        printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
        for(size_t i=0;i<(addressBook->contactCount)-1;i++)
        {
            for(size_t j=0;j<(addressBook->contactCount)-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email) > 0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("Sorted by Email\n");
        
    }
    else if(sortCriteria == 4)
    {
        printf("\nDefault sorting:\n");
        printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
    }

    // Print each contact

    for(size_t i=0;i<addressBook->contactCount;i++)
    {
        printf("%-30s%-30s%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    
}

// Initialize address book (load from file)

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

// Save contacts and exit program

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// Create new contacts

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("\n📝CREATE CONTACT\n--------------------\n");
    printf("Enter the details: \n");
    char Name[50];
    char Phone[20];
    char Email[30];

    int next;
    do
    {
        // Input contact information
        printf("Enter the name : ");
        scanf(" %[^\n]",Name);
        printf("\nEnter the phone : ");
        scanf(" %[^\n]",Phone);
        printf("\nEnter the email : ");
        scanf(" %[^\n]",Email);
        // Validate contact data
        if (validate_name(Name) && validate_phone(Phone,addressBook) && validate_email(Email,addressBook))
        {
            // Store contact if valid
            strcpy(addressBook->contacts[addressBook->contactCount].name,Name);
            strcpy(addressBook->contacts[addressBook->contactCount].phone,Phone);
            strcpy(addressBook->contacts[addressBook->contactCount].email,Email);
            addressBook->contactCount++;
            // Prompt to continue
            printf("\nContact added successfully\n\n\nAdd another contact?\n---------------------------\n1. Yes\n2. No, back to main menu\n---------------------------\nEnter your choice: ");
            scanf("%d",&next);
        }
        else
        {
            printf("Entered data not valid\n");
            return ;
        }
    } while (next==1);
    

    
}
// Search contacts by name, phone or email
int searchContact(AddressBook *addressBook) 
{
    int search;
    printf("\n🔍 SEARCH CONTACTS\n-------------------\n");
    printf("1. Search by name : \n");
    printf("2. Search  by phone : \n");
    printf("3. Search by email : \n");
    scanf("%d",&search);
    int flag=0;
    getchar();// Clear input buffer


    if (search==1)
    {
        char ch[50];
        printf("Enter the name \n");
        scanf("%[^\n]",ch);
        for (int i=0;i<(addressBook->contactCount);i++)
        {
            // Match based on selected field
            if (strcasecmp((addressBook->contacts[i].name),ch)==0)
            {
                flag=1;
                printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
                printf("%-30s%-30s%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                printf("The index of the name is : %d\n",i);
            }
        }
        if (flag==0)
        {
            printf("Invalid name:\n");
            return 0;
        }
        else{
            return 1;
        }
    }
    else if (search==2)
    {
        char ch[50];
        printf("Enter the phone \n");
        scanf("%[^\n]",ch);
        for (int i=0;i<(addressBook->contactCount);i++)
        {
            if (strcasecmp((addressBook->contacts[i].phone),ch)==0)
            {
                flag=1;
                printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
                printf("%-30s%-30s%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                printf("The index of the phone is : %d\n",i);
            }
        }
         if (flag==0)
        {
            printf("Invalid phone:\n");
            return 0;
        }
        else{
            return 1;
        }
    }
    else if (search==3)
    {
        char ch[50];
        printf("Enter the email \n");
        scanf("%[^\n]",ch);
        for (int i=0;i<(addressBook->contactCount);i++)
        {
            if (strcasecmp((addressBook->contacts[i].email),ch)==0)
            {
                flag=1;
                int index1=i;
                printf("--------------------------------------------------------------------------------\nName                           Phone                          Email\n--------------------------------------------------------------------------------\n");
                printf("%-30s%-30s%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                printf("The index of the email is : %d\n",i);
            }
        }
         if (flag==0)
        {
            printf("Invalid name:\n");
            return 0;
        }
        else{
            return 1;
        }
    }
    else
    {
        printf("Invalid Search input:\n");
        
    }
}

// Edit a specific contact

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    printf("\n✏️  EDIT CONTACT\n----------------\nFind the contact you wish to update\n");
    int ret,ind,select;
    ret= searchContact(addressBook); // Find contact to edit
    
    if (ret==0)
    {
        return ;
    }
    else if (ret==1)
    {
        printf ("Enter the Index which want to edit: \n");
        scanf("%d",&ind);
        printf("What do you want to edit:\n 1. Name:\n 2. Phone:\n 3. email:\n");
        scanf("%d",&select);
        getchar();
        switch(select)
        {
            case 1:
            char ch1[30];
            int ret1; 
            printf("Enter the name to be edited:\n");
            scanf("%[^\n]",ch1);
            ret1=validate_name(ch1);
            if (ret1==1)
            {
                strcpy((addressBook->contacts[ind].name),ch1);
                printf("Updated succesfully\n");
                break;
            }
            else
            {
                printf("Invalid name\n");
                break;
            }

            case 2:
            char ch2[30]; 
            int ret2;
            printf("Enter the phone to be edited:\n");
            scanf("%[^\n]",ch2);
            ret2=validate_phone(ch2,addressBook);
            if (ret2==1)
            {
                strcpy((addressBook->contacts[ind].phone),ch2);
                printf("Updated succesfully\n");
                break;
            }
            else
            {
                printf("Invlid phone number\n");
                break;
            }
            case 3:
            char ch3[30];
            int ret3; 
            printf("Enter the email to be edited:\n");
            scanf("%[^\n]",ch3);
            ret3=validate_email(ch3,addressBook);
            if (ret3==1)
            {
                strcpy((addressBook->contacts[ind].email),ch3);
                printf("Updated succesfully\n"); 
                break;
            }
            else
            {
                printf("Invalid email is entered\n");
                break;
            }


        }

    }

    
}
// Delete a contact from the list
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    printf("\n🗑️  DELETE CONTACT\n------------------\nFind the contact you wish to delete\n");
    int ret,ind;
    ret= searchContact(addressBook);// Find contact to delete
    getchar();
    if (ret==0)
    {
        return ;
    }
    else 
    {
        printf ("Enter the Index which want to edit: \n");
        scanf("%d",&ind);
        // Shift contacts down to remove the selected index
        for (int i=ind;i<(addressBook->contactCount);i++) 
        {
            (addressBook->contacts[i])=(addressBook->contacts[i+1]);
            

        }
        printf("Contact deleted successfully\n");
        addressBook->contactCount--;

    }
    
   
}
// Validate name: Only letters and spaces allowed
int validate_name(char* Name)
{
    int i=0;
    while (Name[i])
    {
        if (Name[i] >= 'A'&& Name[i] <= 'Z' || Name[i] >= 'a' && Name[i] <= 'z' || Name[i] == ' ')
        {
            i++;
        }
        else
        {
            return 0;
        }
        
    }
    return 1;
}
// Validate phone number: Must be unique and 10 digits
int validate_phone(char* Phone,AddressBook *addressBook)
{
    
    
    if ((strlen(Phone)) == 10)
    {
        int i=0;
        while (Phone[i])
        {
            if (Phone[i] >= '0' && Phone[i] <= '9')
            {
               
            }
            else
            {
                return 0;
            }
            i++;
        }
        // Check for duplicate phone number
        int j=0;
            for (j=0;j<=addressBook->contactCount;j++)
            {
                if (strcmp(Phone,(addressBook->contacts[j].phone)) == 0)
                {
                    return 0;
                }
                else
                {
                    return 1           ;
                }
            }
    }
    else
    {
        return 0;
    }
}
// Validate email: Must be unique and properly formatted
int validate_email (char* Email,AddressBook *addressBook)
{   
    int i=0;
    for (i=0;i<=addressBook->contactCount;i++)
    {
        if (strcmp(Email,(addressBook->contacts[i].email)) == 0)
        {
            return 0;
        }
    }

    char * ret1,*ret2;
    if ((ret1 = (strchr(Email,'@'))) != NULL)
    {
        if ((ret2 = (strchr(Email,'.'))) != NULL)
        {
            if (ret2>ret1)
            {
                if ((isalnum(*(ret1+1))) && (isalnum(*(ret1-1))) && (isalnum(*(ret2+1))) && (isalnum(*(ret2-1))))
                {
                    int i=0;
                    while (Email[i])
                    {
                        if ((islower(Email[i])) || (isdigit(Email[i])) || Email[i]=='@' || Email[i]=='.')
                        {
                            i++;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                    return 1;

                }
            }
        }
    }
    return 0;
    
}