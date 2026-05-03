#include <stdio.h>
#include "reservation.h"

/*
 * Main function:
 * - Initializes seat data
 * - Displays menu
 * - Calls appropriate functions based on user input
 */
int main(void) {
    Reservation seats[TOTAL_SEATS]; // Array to store all seat reservations
    int choice;                     // Variable to store user menu choice

    // Load existing reservation data from file (or initialize if file doesn't exist)
    loadReservations(seats);

    // Main program loop
    do {
        // Display menu
        printf("\n====================================\n");
        printf("      Airplane Reservation System\n");
        printf("====================================\n");
        printf("1. View Seat Map\n");
        printf("2. Create Reservation\n");
        printf("3. View Reservation\n");
        printf("4. Update Reservation\n");
        printf("5. Delete Reservation\n");
        printf("6. View Reports\n");
        printf("0. Save and Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");

        // Read user input and validate it
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");

            // Clear invalid input from buffer
            while (getchar() != '\n');

            continue; // Restart loop
        }

        // Handle user choice
        switch (choice) {

            case 1:
                // Display all seats and their status
                displaySeats(seats);
                break;

            case 2:
                // Create a new reservation and save to file
                createReservation(seats);
                saveReservations(seats);
                break;

            case 3:
                // View a specific reservation
                viewReservation(seats);
                break;

            case 4:
                // Update an existing reservation and save
                updateReservation(seats);
                saveReservations(seats);
                break;

            case 5:
                // Delete a reservation and save
                deleteReservation(seats);
                saveReservations(seats);
                break;

            case 6:
                // Display summary report
                viewReports(seats);
                break;

            case 0:
                // Save data before exiting program
                saveReservations(seats);
                printf("Reservations saved. Exiting program.\n");
                break;

            default:
                // Handle invalid menu option
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }

    } while (choice != 0); // Continue until user selects Exit

    return 0;
}