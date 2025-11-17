#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_SIZE 50
#define PHONE_SIZE 20
#define EMAIL_SIZE 50

struct Contact {
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    char email[EMAIL_SIZE];
};


void clearBuffer();
void inputString(char *str, int size);
void addContact(struct Contact contacts[], int *count);
void displayContacts(struct Contact contacts[], int count);
void deleteContact(struct Contact contacts[], int *count);
void editContact(struct Contact contacts[], int count);
void saveContactsToFile(struct Contact contacts[], int count);
void searchContact(struct Contact contacts[], int count);

int main() {
    struct Contact contacts[MAX_CONTACTS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n===== CONTACT BOOK MENU =====\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Delete Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Search Contact\n");
        printf("6. Save to File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: addContact(contacts, &count); break;
            case 2: displayContacts(contacts, count); break;
            case 3: deleteContact(contacts, &count); break;
            case 4: editContact(contacts, count); break;
            case 5: searchContact(contacts, count); break;
            case 6: saveContactsToFile(contacts, count); break;
            case 7: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice. Try again!\n");
        }
    }
}
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
void inputString(char *str, int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0'; // remove newline
}
void addContact(struct Contact contacts[], int *count) {
    if (*count >= MAX_CONTACTS) {
        printf("Contact list is full!\n");
        return;
    }

    printf("Enter Name: ");
    inputString(contacts[*count].name, NAME_SIZE);

    printf("Enter Phone: ");
    inputString(contacts[*count].phone, PHONE_SIZE);

    printf("Enter Email: ");
    inputString(contacts[*count].email, EMAIL_SIZE);

    (*count)++;
    printf("Contact added successfully!\n");
}
void displayContacts(struct Contact contacts[], int count) {
    if (count == 0) {
        printf("No contacts available.\n");
        return;
    }

    printf("\n===== CONTACT LIST =====\n");
    for (int i = 0; i < count; i++) {
        printf("\nContact %d\n", i + 1);
        printf("Name : %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].phone);
        printf("Email: %s\n", contacts[i].email);
    }
}
void deleteContact(struct Contact contacts[], int *count) {
    if (*count == 0) {
        printf("No contacts to delete.\n");
        return;
    }

    int index;
    printf("Enter contact number to delete: ");

    if (scanf("%d", &index) != 1) {
        printf("Invalid input.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    if (index < 1 || index > *count) {
        printf("Invalid contact number!\n");
        return;
    }

    for (int i = index - 1; i < *count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    (*count)--;
    printf("Contact deleted successfully!\n");
}

void editContact(struct Contact contacts[], int count) {
    if (count == 0) {
        printf("No contacts to edit.\n");
        return;
    }

    int index;
    printf("Enter contact number to edit: ");

    if (scanf("%d", &index) != 1) {
        printf("Invalid input.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    if (index < 1 || index > count) {
        printf("Invalid contact number!\n");
        return;
    }

    int pos = index - 1;

    printf("Enter new Name: ");
    inputString(contacts[pos].name, NAME_SIZE);

    printf("Enter new Phone: ");
    inputString(contacts[pos].phone, PHONE_SIZE);

    printf("Enter new Email: ");
    inputString(contacts[pos].email, EMAIL_SIZE);

    printf("Contact updated successfully!\n");
}

void searchContact(struct Contact contacts[], int count) {
    if (count == 0) {
        printf("No contacts to search.\n");
        return;
    }

    char query[NAME_SIZE];
    printf("Enter name to search: ");
    inputString(query, NAME_SIZE);

    int found = 0;

    for (int i = 0; i < count; i++) {
        if (strstr(contacts[i].name, query) != NULL) {
            printf("\nMatch Found:\n");
            printf("Name : %s\n", contacts[i].name);
            printf("Phone: %s\n", contacts[i].phone);
            printf("Email: %s\n", contacts[i].email);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching contacts found.\n");
    }
}

void saveContactsToFile(struct Contact contacts[], int count) {
    FILE *fp = fopen("contacts.txt", "w");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s\n",
                contacts[i].name,
                contacts[i].phone,
                contacts[i].email);
    }

    fclose(fp);
    printf("Contacts saved to file successfully!\n");
}
