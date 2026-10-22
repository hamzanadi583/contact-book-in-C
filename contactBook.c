#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CONTACTS 100
#define FILENAME "contacts.txt"

int listContacts() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("could not open file\n");
        return 1;
    }

    char line[MAX_CONTACTS];
    while(fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
    return 0;
}

int addContacts(char name[40], char phone[20]) {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("could not open file\n");
        return 1;
    }

    fprintf(file , "%s - %s\n", name, phone);
    fclose(file);
    return 0;
}

int searchContact(char name[40]) {
    FILE *file = fopen(FILENAME, "r");
    if(file == NULL){
        printf("could not open file\n");
        return 1;
    }

    char line[MAX_CONTACTS];
    bool found = false;
    while(fgets(line , sizeof(line), file)) {
        if(strstr(line, name) != NULL){
            printf("%s", line);
            found = true;
        }
    }
    if (!found) {
        printf("Contact not found\n");
    }

    fclose(file);
    return 0;
}

int deleteContact(char name[40]){
    FILE *file = fopen(FILENAME, "r");
    if(file == NULL){
        printf("could not open file\n");
        return 1;
    }

    char line[MAX_CONTACTS];
    FILE *tempFile = fopen("temp.txt", "w");
    if(tempFile == NULL){
        printf("could not open file\n");
        return 1;
    }

    while(fgets(line , sizeof(line), file)) {
        if(strstr(line, name) == NULL){
            fputs(line, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);
    return 0;
}

int main() {

    bool exit = false;

    while (!exit) {
        printf("=== Contact book Menu ===\n");
        printf("1 . Add contact\n");
        printf("2 . Search contact\n");
        printf("3 . List all contacts\n");
        printf("4 . Delete contact\n");
        printf("5 . Exit\n");

        printf("Choose an option : ");
        int op;
        scanf("%d", &op);

        while (getchar() != '\n' && getchar() != EOF);

        switch (op) {
            case 1 : {
                char name[40];
                char phone[20];

                printf("Enter contact name : ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline character
                
                printf("\nEnter contact phone : ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = 0; // Remove newline character

                addContacts(name, phone);
                break;
            }
            case 2 : {
                char name[40];
                printf("Enter contact name to search : ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline character
                searchContact(name);
                break;
            }
            case 3 : {
                listContacts();
                printf("\n");
                break;
            }
            case 4 : {
                char name[40];
                printf("Enter contact name to delete : ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline character
                deleteContact(name);
                break;
            }
            case 5 : {
                exit = true;
                break;
            }
        }

    }

}