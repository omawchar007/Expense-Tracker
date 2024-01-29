#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *itemName(int choice) {
    switch (choice) {
        case 1: return "House Rent";
        case 2: return "Food";
        case 3: return "Mobile";
        case 4: return "Clothes";
        case 5: return "Transport";
        case 6: return "EMI";
        default: return "Invalid Item";
    }
}

typedef struct Account {
    char name[100];
    char username[100];
    char pass[64]; 
    char email[150];
    int age;
    float salary;
    float total;
    float budget;
    float totalPerItem[7];
} Ac;

int logIn(char username[], char pass[], Ac id[], int totalUsers) {
    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(username, id[i].username) == 0 && strcmp(pass, id[i].pass) == 0) {
            return i;
        }
    }
    return -1;
}

void signUp(int *index, char name[], char username[], char pass[], char email[], int age, float salary, Ac id[], int totalUsers) {
    if (*index < totalUsers) {
        for (int i = 0; i < *index; i++) {
            if (strcmp(username, id[i].username) == 0) {
                printf("This Username is Already Taken\n");
                return;
            }
        }

        strcpy(id[*index].username, username);
        strcpy(id[*index].name, name);
        strcpy(id[*index].pass, pass);
        strcpy(id[*index].email, email);
        id[*index].age = age;
        id[*index].total = 0.0;
        id[*index].salary = salary;
        id[*index].budget = 0.0;

        for (int i = 0; i < 7; i++) {
            id[*index].totalPerItem[i] = 0.0;
        }

        printf("User Created Successfully\n");
        (*index)++;
    } else {
        printf("Server is Full\n");
    }
}

void addExpense(Ac *user) {
    printf("\n==================================== Add Expense ====================================\n");

    int itemChoice;
    float expenseAmount;
    char date[10];

    printf("\nAvailable Expense Items:\n");
    printf("1. House Rent\n2. Food\n3. Mobile\n4. Clothes\n5. Transport\n6. EMI\n");

    printf("\nEnter the number corresponding to the expense item: ");
    scanf("%d", &itemChoice);

    if (itemChoice < 1 || itemChoice > 6) {
        printf("Invalid item choice.\n");
        return;
    }

    printf("Enter the amount spent: ");
    scanf("%f", &expenseAmount);

    printf("Enter Date (DD/MM/YY): ");
    scanf("%s", date);

    user->total += expenseAmount;
    user->totalPerItem[itemChoice - 1] += expenseAmount;

    printf("\nExpense added successfully:\n");
    printf("Item: %s\nAmount: %.2f\nDate: %s\n", itemName(itemChoice), expenseAmount, date);
}

void totalSpend(Ac *user) {
    printf("\n==================================== Total Spend ====================================\n");

    float totalSpend = user->total;

    printf("\nTotal spend for all time: %.2f\n", totalSpend);

    
    printf("\nTotal spend for each item:\n");
    for (int i = 1; i <= 6; i++) {
        printf("%s: %.2f\n", itemName(i), user->totalPerItem[i - 1]);
    }
}

void viewProfile(Ac *user) {
    printf("\n==================================== View Profile ====================================\n");
    printf("Name: %s\nUsername: %s\nEmail: %s\nAge: %d\nSalary: %.2f\nMonthly Budget: %.2f\n",
           user->name, user->username, user->email, user->age, user->salary, user->budget);
}

void editProfile(Ac *user) {
    printf("\n==================================== Edit Profile ====================================\n");
    printf("Enter new monthly budget: ");
    scanf("%f", &(user->budget));
    if (user->budget < 0) {
        printf("Invalid budget value. Please enter a non-negative value.\n");
        user->budget = 0.0;
    }
    printf("Monthly budget updated successfully!\n");
}

int main() {
    const int MAX_USERS = 500;
    Ac id[MAX_USERS];
    int choice;
    int index = 0;
    char username[100];
    char name[100];
    char email[100];
    int age;
    char pass[64];
    float salary;

    int loggedInUserIndex = -1;

    do {
        printf("\n==================================== Expense Tracker ====================================\n");
        printf("1 -> Log In\n2 -> Sign Up\n3 -> Add Expense\n4 -> Total Spend\n5 -> View Profile\n6 -> Edit Profile\n7 -> Log Out\n");
        printf("-------------------------------------------------------------------------------------------\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n======================================= Log In ========================================\n");
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf("%s", pass);
                loggedInUserIndex = logIn(username, pass, id, index);
                if (loggedInUserIndex != -1) {
                    printf("\nLog In Successful\n");
                } else {
                    printf("Invalid Username or Password\n");
                }
                break;

            case 2:
                printf("\n====================================== Sign Up =======================================\n");
                printf("Name: ");
                scanf("%s", name);
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf("%s", pass);
                printf("Email: ");
                scanf("%s", email);
                printf("Age: ");
                scanf("%d", &age);
                printf("Monthly salary: ");
                scanf("%f", &salary);

                signUp(&index, name, username, pass, email, age, salary, id, MAX_USERS);
                break;

            case 3:
                if (loggedInUserIndex != -1) {
                    addExpense(&id[loggedInUserIndex]);
                } else {
                    printf("Please log in to add an expense.\n");
                }
               

                break;

            case 4:
                if (loggedInUserIndex != -1) {
                    totalSpend(&id[loggedInUserIndex]);
                } else {
                    printf("Please log in to check total spending.\n");
                }
                break;

            case 5:
                if (loggedInUserIndex != -1) {
                    viewProfile(&id[loggedInUserIndex]);
                } else {
                    printf("Please log in to view the profile.\n");
                }
                break;

            case 6:
                if (loggedInUserIndex != -1) {
                    editProfile(&id[loggedInUserIndex]);
                } else {
                    printf("Please log in to edit the profile.\n");
                }
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid Input, Please Enter Correct Option\n");
                break;
        }
    }
         while (choice != 7);
    
    return 0;
}
