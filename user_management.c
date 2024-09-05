#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 10

typedef struct {
    int id;
    char name[50];
    int age;
    char address[100];
} User;

User users[MAX_USERS];
int userCount = 0;

// Function to create a user's information
void createUser() {
    //check that the number of user is full
    if (userCount >= MAX_USERS) {
        printf("User storage is full.\n");
        return;
    }

    printf("Create User Page\n********************\n");
    users[userCount].id = userCount + 1;

    do {
        printf("Enter name: ");
        scanf(" %[^\n]", users[userCount].name);

        // Ensure name is non-empty
        if (strlen(users[userCount].name) == 0) {
            printf("Name cannot be empty. Please try again.\n");
        }
    } while (strlen(users[userCount].name) == 0);

    // Ensure age is a valid number
    bool ageValid;
    while (ageValid == false) {
        printf("Enter age: ");
        scanf("%d", &users[userCount].age);

        if (users[userCount].age <= 0) {
            printf("Invalid age. Please enter a positive number.\n");
            while(getchar() != '\n'); // clear invalid input
        } else {
            ageValid = true;
        }
    }

    do {
        printf("Enter address: ");
        scanf(" %[^\n]", users[userCount].address);

        // Ensure address is non-empty
        if (strlen(users[userCount].address) == 0) {
            printf("Address cannot be empty. Please try again.\n");
        }
    } while (strlen(users[userCount].address) == 0);

    userCount++;
    printf("User created successfully!\n");
}

// Function to read user's information
void readAllUsers() {
    printf("Reading All Users\n********************\n");
    // check for no user
    if (userCount == 0) {
        printf("No User found!\n");
        return;
    }

    // Get user from array
    for (int i = 0; i < userCount; i++) {
        printf("%d %s %d %s\n", users[i].id, users[i].name, users[i].age, users[i].address);
    }
}

// Function to update a user's information with optional fields
void updateUser() {
    bool found = false;
    printf("Update User Page\n********************\n");

    do {
        int id;
        printf("Enter id to update: ");
        scanf("%d", &id);
        getchar();  // consume the newline character ('\n') left by scanf

        for (int i = 0; i < userCount; i++) {
            if (users[i].id == id) {
                found = true;
                printf("User found! Going to update ...\n");

                char temp[100]; //for name and address

                // Name update
                printf("Enter name to update (leave empty/ enter to keep current): ");
                //Reads input from the user including the newline character if the input is shorter than the buffer size.
                fgets(temp, sizeof(temp), stdin);
                if (temp[0] != '\n') {
                    temp[strcspn(temp, "\n")] = 0;  // Remove newline character if present and replaces it with a null terminator
                    strcpy(users[i].name, temp); // Copy the cleaned input from temp to users[userCount].name
                }

                // Age update
                int tempAge;
                while (true) { // if valid input
                    printf("Enter age to update (0 to keep current): ");

                    if (scanf("%d", &tempAge) != 1) {
                        // If scanf fails to read an integer, clear the invalid input
                        printf("Invalid input. Please enter a numeric value for the age.\n");
                        while (getchar() != '\n');  // Clear the input buffer
                    } else {
                        // If a valid integer is entered
                        if (tempAge > 0) {
                            users[i].age = tempAge;
                        }
                        getchar();
                        break;
                    }
                }

                // Address update
                printf("Enter address to update (leave empty to keep current): ");
                fgets(temp, sizeof(temp), stdin);
                if (temp[0] != '\n') {
                    temp[strcspn(temp, "\n")] = 0;
                    strcpy(users[i].address, temp);
                }

                printf("User id: %d Updated ...\n", id);
                break;
            }
        }

        if (found == false) {
            printf("Your provided id was not found! Try again!\n");
        }
    } while (found == false);
}

// Function to delete a user
void deleteUser() {
    bool found = false;
    printf("Delete User Page\n********************\n");

    do {
        int id;
        printf("Enter id to delete: ");

        if (scanf("%d", &id) != 1) { // The user enters a non-numeric character, it will return 0
            printf("Invalid input! Please enter a numeric value.\n");
            while (getchar() != '\n');  // clear invalid input
            continue;
        }

        for (int i = 0; i < userCount; i++) {
            if (users[i].id == id) {
                found = true;
                for (int j = i; j < userCount - 1; j++) {
                    users[j] = users[j + 1];
                }
                userCount--;
                printf("User id: %d Deleted\n", id);
                break;
            }
        }

        if (found == false) {
            printf("Your provided id was not found! Try again!\n");
        }
    } while (found == false);
}


int main() {
    int option;
    do {
        printf("\n1 Create User\n2 Read All Users\n3 Update User\n4 Delete User\n0 Exit\nEnter your Option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: createUser(); break;
            case 2: readAllUsers(); break;
            case 3: updateUser(); break;
            case 4: deleteUser(); break;
            case 0: printf("Exiting program.\n"); break;
            default: printf("Invalid option!\n"); break;
        }
    } while (option != 0);

    return 0;
}


//
// Created by marco on 9/2/24.
//

