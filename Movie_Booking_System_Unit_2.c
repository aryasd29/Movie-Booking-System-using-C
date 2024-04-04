#include <stdio.h>
#include <string.h>

#define NUM_USERS 10
#define NUM_MOVIES 3
#define NUM_SHOW_TIMES 3
#define NUM_ROWS 5
#define NUM_SEATS_PER_ROW 10
#define TICKET_PRICE 10

char usernames[NUM_USERS][20];
char passwords[NUM_USERS][20];
int tickets_bought[NUM_USERS] = {0};
char movies[NUM_MOVIES][50] = {
    "Avengers: Endgame",
    "Joker",
    "Inception"
};

char show_times[NUM_MOVIES][NUM_SHOW_TIMES][10] = {
    { "10:00 AM", "2:00 PM", "6:00 PM" },
    { "11:00 AM", "3:00 PM", "7:00 PM" },
    { "12:00 PM", "4:00 PM", "8:00 PM" }
};

int current_user = -1;

// Function to register a new user
void register_user(char usernames[][20], char passwords[][20], int *current_user) {
    if (*current_user == NUM_USERS - 1) {
        printf("Maximum number of users reached.\n");
        return;
    }

    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);

    // Check for existing username
    for (int i = 0; i <= *current_user; i++) {
        if (strcmp(usernames[i], username) == 0) {
            printf("Username already exists. Please choose a different one.\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", password);

    (*current_user)++;
    strcpy(usernames[*current_user], username);
    strcpy(passwords[*current_user], password);
    printf("User registered successfully.\n");
}

// Function to login a user
void login_user(char usernames[][20], char passwords[][20], int *current_user) {
    if (*current_user != -1) {
        printf("Logout current user to login as a different user.\n");
        return;
    }

    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i <= *current_user; i++) {
        if (strcmp(usernames[i], username) == 0 && strcmp(passwords[i], password) == 0) {
            *current_user = i;
            printf("Login successful.\n");
            return;
        }
    }

    printf("Invalid username or password.\n");
}

// Function to book a ticket for the logged-in user
void book_ticket(int *current_user, char movies[][50], char show_times[][NUM_SHOW_TIMES][10]) {
    int movie_choice, show_time_choice, row_choice, seat_choice;

    if (*current_user == -1) {
        printf("Please login to book a ticket.\n");
        return;
    }

    printf("Select a movie:\n");
    for (int i = 0; i < NUM_MOVIES; i++) {
        printf("%d. %s\n", i + 1, movies[i]);
    }
    printf("Enter your choice: ");
    scanf("%d", &movie_choice);
    movie_choice--;

    printf("Select a show time:\n");
    for (int i = 0; i < NUM_SHOW_TIMES; i++) {
        printf("%d. %s\n", i + 1, show_times[movie_choice][i]);
    }
    printf("Enter your choice: ");
    scanf("%d", &show_time_choice);
    show_time_choice--;

    printf("Select a seat (row and seat number):\n");
    printf("Rows: 1 to 5\n");
    printf("Seats: 1 to 10\n");
    printf("Enter row number: ");
    scanf("%d", &row_choice);
    printf("Enter seat number: ");
    scanf("%d", &seat_choice);

    if (row_choice < 1 || row_choice > NUM_ROWS || seat_choice < 1 || seat_choice > NUM_SEATS_PER_ROW) {
        printf("Invalid seat selection.\n");
        return;
    }

    char confirmation;
    printf("Confirm booking (y/n): ");
    scanf(" %c", &confirmation);
    int payment_choice;

    if (confirmation == 'y' || confirmation == 'Y') {
        printf("Booking confirmed.\n");
        printf("Select a payment mode:\n");
        printf("1. Credit Card\n2. Debit Card\n3. UPI\n4. Cash\n");
        printf("Enter your choice: ");
        scanf("%d", &payment_choice);

        switch (payment_choice) {
            case 1:
                printf("Payment successful using Credit Card.\n");
                break;
            case 2:
                printf("Payment successful using Debit Card.\n");
                break;
            case 3:
                printf("Payment successful using UPI.\n");
                break;
            case 4:
                printf("Payment successful using Cash.\n");
                break;
            default:
                printf("Invalid payment mode.\n");
                break;
        }

        printf("Payment of $%d made!.\n", TICKET_PRICE);
        tickets_bought[*current_user]++;

        printf("Ticket Number: %d%d%d%d\n", movie_choice + 1, show_time_choice + 1, row_choice, seat_choice);
        printf("Here's your ticket:\n");
        printf("=======================Ticket confirmed!!=====================\n");
        printf("Name : %s\n", usernames[*current_user]);
        printf("Movie name: %s\n", movies[movie_choice]);
        printf("Show time selected: %s\n", show_times[movie_choice][show_time_choice]);
        printf("row and seat number selected: %d %d\n", row_choice, seat_choice);
        printf("ENJOY YOUR MOVIE!\n");
        printf("===============================================================");
    } else {
        printf("Booking canceled.\n");
    }
}

// Function to view the logged-in user's ticket history
void view_user_history(int current_user, char usernames[][20], int tickets_bought[]) {
    if (current_user == -1) {
        printf("Please login to view user history.\n");
        return;
    }

    printf("User History:\n");
    printf("Username: %s\n", usernames[current_user]);
    printf("Tickets Bought: %d\n", tickets_bought[current_user]);
}

int main() {
    int choice, payment_choice;

    while (1) {
        printf("\n1. User Registration\n2. Login\n3. Book Ticket\n4. View User History\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user(usernames, passwords, &current_user);
                break;
            case 2:
                login_user(usernames, passwords, &current_user);
                break;
            case 3:
                if (current_user == -1) {
                    printf("Please login to book a ticket.\n");
                } else {
                    book_ticket(&current_user, movies, show_times);
                }
                break;
            case 4:
                if (current_user == -1) {
                    printf("Please login to view user history.\n");
                } else {
                    view_user_history(current_user, usernames, tickets_bought);
                }
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
