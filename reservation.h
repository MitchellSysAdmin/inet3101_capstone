#ifndef RESERVATION_H
#define RESERVATION_H

/*
 * Maximum number of characters allowed for a passenger name.
 */
#define MAX_NAME 50

/*
 * Total number of seats on the airplane.
 */
#define TOTAL_SEATS 48

/*
 * Reservation structure.
 * Each seat stores:
 * - seatNumber: the seat's number
 * - isBooked: 0 if available, 1 if booked
 * - passengerName: name of the passenger assigned to the seat
 * - reservationId: unique reservation ID for the booking
 */
typedef struct {
    int seatNumber;
    int isBooked;
    char passengerName[MAX_NAME];
    char reservationId[20];
} Reservation;

/*
 * Loads reservation data from the reservations.db GDBM file.
 */
void loadReservations(Reservation seats[]);

/*
 * Saves reservation data from the reservations.db GDBM file.
 */
void saveReservations(Reservation seats[]);

/*
 * Displays the current seat map.
 */
void displaySeats(Reservation seats[]);

/*
 * Creates a new reservation.
 */
void createReservation(Reservation seats[]);

/*
 * Views an existing reservation.
 */
void viewReservation(Reservation seats[]);

/*
 * Updates an existing reservation.
 */
void updateReservation(Reservation seats[]);

/*
 * Deletes an existing reservation.
 */
void deleteReservation(Reservation seats[]);

/*
 * Displays summary reports for booked and available seats.
 */
void viewReports(Reservation seats[]);

#endif