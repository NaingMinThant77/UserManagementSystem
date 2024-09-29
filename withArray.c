#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 10

// Arrays to store user data
int ids[MAX_USERS];
char names[MAX_USERS][50];
int ages[MAX_USERS];
char addresses[MAX_USERS][100];
int userCount = 0;

// Function to create a user's information
void createUser()
{
    if (userCount >= MAX_USERS)
    {
        printf("User storage is full.\n");
        return;
    }

    printf("Create User Page\n********************\n");
    ids[userCount] = userCount + 1;

    do
    {
        printf("Enter name: ");
        scanf(" %[^\n]", names[userCount]);

        if (strlen(names[userCount]) == 0)
        {
            printf("Name cannot be empty. Please try again.\n");
        }
    } while (strlen(names[userCount]) == 0);

    // Ensure age is a valid number
    bool ageValid = false;
    while (!ageValid)
    {
        printf("Enter age: ");
        scanf("%d", &ages[userCount]);

        if (ages[userCount] <= 0)
        {
            printf("Invalid age. Please enter a positive number.\n");
            while (getchar() != '\n')
                ; // clear invalid input
        }
        else
        {
            ageValid = true;
        }
    }

    do
    {
        printf("Enter address: ");
        scanf(" %[^\n]", addresses[userCount]);

        if (strlen(addresses[userCount]) == 0)
        {
            printf("Address cannot be empty. Please try again.\n");
        }
    } while (strlen(addresses[userCount]) == 0);

    userCount++;
    printf("User created successfully!\n");
}

// Function to read all users' information
void readAllUsers()
{
    printf("Reading All Users\n********************\n");
    if (userCount == 0)
    {
        printf("No User found!\n");
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        printf("%d %s %d %s\n", ids[i], names[i], ages[i], addresses[i]);
    }
}

// Function to update a user's information with optional fields
void updateUser()
{
    bool found = false;
    printf("Update User Page\n********************\n");

    do
    {
        int id;
        printf("Enter id to update: ");
        scanf("%d", &id);
        getchar(); // consume the newline character ('\n') left by scanf

        for (int i = 0; i < userCount; i++)
        {
            if (ids[i] == id)
            {
                found = true;
                printf("User found! Going to update ...\n");

                char temp[100]; // for name and address

                // Name update
                printf("Enter name to update (leave empty to keep current): ");
                fgets(temp, sizeof(temp), stdin);
                if (temp[0] != '\n')
                {
                    temp[strcspn(temp, "\n")] = 0; // Remove newline character if present
                    strcpy(names[i], temp);        // Copy the cleaned input from temp to names[i]
                }

                // Age update
                int tempAge;
                while (true)
                {
                    printf("Enter age to update (0 to keep current): ");
                    if (scanf("%d", &tempAge) != 1)
                    {
                        printf("Invalid input. Please enter a numeric value for the age.\n");
                        while (getchar() != '\n')
                            ; // Clear the input buffer
                    }
                    else
                    {
                        if (tempAge > 0)
                        {
                            ages[i] = tempAge;
                        }
                        getchar();
                        break;
                    }
                }

                // Address update
                printf("Enter address to update (leave empty to keep current): ");
                fgets(temp, sizeof(temp), stdin);
                if (temp[0] != '\n')
                {
                    temp[strcspn(temp, "\n")] = 0;
                    strcpy(addresses[i], temp);
                }

                printf("User id: %d Updated ...\n", id);
                break;
            }
        }

        if (!found)
        {
            printf("Your provided id was not found! Try again!\n");
        }
    } while (!found);
}

// Function to delete a user
void deleteUser()
{
    bool found = false;
    printf("Delete User Page\n********************\n");

    do
    {
        int id;
        printf("Enter id to delete: ");

        if (scanf("%d", &id) != 1)
        {
            printf("Invalid input! Please enter a numeric value.\n");
            while (getchar() != '\n')
                ; // clear invalid input
            continue;
        }

        for (int i = 0; i < userCount; i++)
        {
            if (ids[i] == id)
            {
                found = true;
                for (int j = i; j < userCount - 1; j++)
                {
                    ids[j] = ids[j + 1];
                    strcpy(names[j], names[j + 1]);
                    ages[j] = ages[j + 1];
                    strcpy(addresses[j], addresses[j + 1]);
                }
                userCount--;
                printf("User id: %d Deleted\n", id);
                break;
            }
        }

        if (!found)
        {
            printf("Your provided id was not found! Try again!\n");
        }
    } while (!found);
}

int main()
{
    int option;
    do
    {
        printf("\n1 Create User\n2 Read All Users\n3 Update User\n4 Delete User\n0 Exit\nEnter your Option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            createUser();
            break;
        case 2:
            readAllUsers();
            break;
        case 3:
            updateUser();
            break;
        case 4:
            deleteUser();
            break;
        case 0:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid option!\n");
            break;
        }
    } while (option != 0);

    return 0;
}
