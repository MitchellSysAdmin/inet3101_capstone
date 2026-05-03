#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gdbm.h>
#include "reservation.h"

/*
 * GDBM database file.
 * This replaces the plain text reservations.txt file.
 */
#define DB_FILE "reservations.db"

/*
 * Clears leftover input from stdin.
 * Useful when mixing scanf() and fgets().
 */
static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * Creates a key for the GDBM database using the seat number.
 * Example: seat 1 becomes key "1".
 */
static void makeSeatKey(int seatNumber, char keyBuffer[]) {
    snprintf(keyBuffer, 10, "%d", seatNumber);
}

/*
 * Loads reservations from the GDBM database.
 * If the database does not exist yet, it initializes all seats as available.
 */
void loadReservations(Reservation seats[]) {
    GDBM_FILE dbf;
    datum key, data;
    char keyString[10];

    // Initialize all seats first
    for (int i = 0; i < TOTAL_SEATS; i++) {
        seats[i].seatNumber = i + 1;
        seats[i].isBooked = 0;
        strcpy(seats[i].passengerName, "");
        strcpy(seats[i].reservationId, "");
    }

    // Open or create the database
    dbf = gdbm_open(DB_FILE, 512, GDBM_WRCREAT, 0644, NULL);

    if (dbf == NULL) {
        printf("Error: Could not open GDBM database.\n");
        return;
    }

    // Try loading each seat record from the database
    for (int i = 0; i < TOTAL_SEATS; i++) {
        makeSeatKey(i + 1, keyString);

        key.dptr = keyString;
        key.dsize = strlen(keyString) + 1;

        data = gdbm_fetch(dbf, key);

        // If record exists, copy it into the seats array
        if (data.dptr != NULL) {
            if (data.dsize == sizeof(Reservation)) {
                memcpy(&seats[i], data.dptr, sizeof(Reservation));
            }

            // gdbm_fetch allocates memory, so it must be freed
            free(data.dptr);
        }
    }

    gdbm_close(dbf);
}

/*
 * Saves all reservation records to the GDBM database.
 * Each seat is stored as one key-value record.
 */
void saveReservations(Reservation seats[]) {
    GDBM_FILE dbf;
    datum key, data;
    char keyString[10];

    dbf = gdbm_open(DB_FILE, 512, GDBM_WRCREAT, 0644, NULL);

    if (dbf == NULL) {
        printf("Error: Could not save reservation data.\n");
        return;
    }

    // Store each seat record in the database
    for (int i = 0; i < TOTAL_SEATS; i++) {
        makeSeatKey(seats[i].seatNumber, keyString);

        key.dptr = keyString;
        key.dsize = strlen(keyString) + 1;

        data.dptr = (char *)&seats[i];
        data.dsize = sizeof(Reservation);

        if (gdbm_store(dbf, key, data, GDBM_REPLACE) != 0) {
            printf("Error: Could not store seat %d.\n", seats[i].seatNumber);
        }
    }

    gdbm_close(dbf);
}

/*
 * Displays the airplane seat map.
 * A = Available
 * B = Booked
 */
void displaySeats(Reservation seats[]) {
    printf("\nSeat Map\n");
    printf("B = Booked, A = Available\n\n");

    for (int i = 0; i < TOTAL_SEATS; i++) {
        printf("[%02d:%c] ",
               seats[i].seatNumber,
               seats[i].isBooked ? 'B' : 'A');

        // Print 6 seats per row
        if ((i + 1) % 6 == 0) {
            printf("\n");
        }
    }
}

/*
 * Creates a new reservation for a selected seat.
 */
void createReservation(Reservation seats[]) {
    int seatNumber;

    printf("\nEnter seat number to reserve (1-%d): ", TOTAL_SEATS);

    if (scanf("%d", &seatNumber) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (seatNumber < 1 || seatNumber > TOTAL_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[seatNumber - 1].isBooked) {
        printf("Seat %d is already booked.\n", seatNumber);
        return;
    }

    clearInputBuffer();

    printf("Enter passenger name: ");
    fgets(seats[seatNumber - 1].passengerName, MAX_NAME, stdin);

    // Remove trailing newline
    seats[seatNumber - 1].passengerName[
        strcspn(seats[seatNumber - 1].passengerName, "\n")
    ] = '\0';

    seats[seatNumber - 1].isBooked = 1;

    // Generate reservation ID based on seat number
    snprintf(seats[seatNumber - 1].reservationId,
             sizeof(seats[seatNumber - 1].reservationId),
             "R%04d",
             seatNumber);

    printf("Reservation created successfully.\n");
    printf("Reservation ID: %s\n", seats[seatNumber - 1].reservationId);
}

/*
 * Views reservation details for a selected seat.
 */
void viewReservation(Reservation seats[]) {
    int seatNumber;

    printf("\nEnter seat number to view reservation: ");

    if (scanf("%d", &seatNumber) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (seatNumber < 1 || seatNumber > TOTAL_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    if (!seats[seatNumber - 1].isBooked) {
        printf("Seat %d is not currently booked.\n", seatNumber);
        return;
    }

    printf("\nReservation Details\n");
    printf("-------------------\n");
    printf("Seat Number: %d\n", seats[seatNumber - 1].seatNumber);
    printf("Passenger Name: %s\n", seats[seatNumber - 1].passengerName);
    printf("Reservation ID: %s\n", seats[seatNumber - 1].reservationId);
}

/*
 * Updates the passenger name for an existing reservation.
 */
void updateReservation(Reservation seats[]) {
    int seatNumber;

    printf("\nEnter seat number to update reservation: ");

    if (scanf("%d", &seatNumber) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (seatNumber < 1 || seatNumber > TOTAL_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    if (!seats[seatNumber - 1].isBooked) {
        printf("Seat %d is not currently booked.\n", seatNumber);
        return;
    }

    clearInputBuffer();

    printf("Enter updated passenger name: ");
    fgets(seats[seatNumber - 1].passengerName, MAX_NAME, stdin);

    seats[seatNumber - 1].passengerName[
        strcspn(seats[seatNumber - 1].passengerName, "\n")
    ] = '\0';

    printf("Reservation updated successfully.\n");
}

/*
 * Deletes a reservation and makes the seat available again.
 */
void deleteReservation(Reservation seats[]) {
    int seatNumber;

    printf("\nEnter seat number to delete reservation: ");

    if (scanf("%d", &seatNumber) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    if (seatNumber < 1 || seatNumber > TOTAL_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    if (!seats[seatNumber - 1].isBooked) {
        printf("Seat %d is not currently booked.\n", seatNumber);
        return;
    }

    seats[seatNumber - 1].isBooked = 0;
    strcpy(seats[seatNumber - 1].passengerName, "");
    strcpy(seats[seatNumber - 1].reservationId, "");

    printf("Reservation deleted successfully.\n");
}

/*
 * Displays reservation summary reports.
 */
void viewReports(Reservation seats[]) {
    int booked = 0;
    int available = 0;

    printf("\nReservation Report\n");
    printf("------------------\n");

    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[i].isBooked) {
            booked++;
        } else {
            available++;
        }
    }

    printf("Total Seats: %d\n", TOTAL_SEATS);
    printf("Booked Seats: %d\n", booked);
    printf("Available Seats: %d\n", available);

    printf("\nBooked Passenger List\n");
    printf("---------------------\n");

    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[i].isBooked) {
            printf("Seat %02d | %s | %s\n",
                   seats[i].seatNumber,
                   seats[i].passengerName,
                   seats[i].reservationId);
        }
    }

    if (booked == 0) {
        printf("No reservations found.\n");
    }
}