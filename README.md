# Airplane Reservation System (C Programming Capstone)

## Problem Statement
This project implements a simple airplane reservation system using the C programming language. The goal is to manage seat bookings for a single airplane with a fixed number of seats. The system allows users to perform core reservation operations such as booking seats, viewing reservations, updating passenger information, and canceling reservations.

The program is designed to demonstrate fundamental C programming concepts including structures, arrays, file handling, modular programming, and user interaction through a command-line interface.

---

## Describe the Solution

The solution is implemented as a modular C application consisting of multiple source files:

- `main.c` → Handles user interaction and menu navigation  
- `reservation.h` → Defines data structures and function prototypes  
- `reservation_functions.c` → Implements all reservation logic and file operations  
- `reservations.txt` → Stores reservation data persistently  

### Key Features

- **Seat Management**
  - The airplane has 48 seats stored in an array of structures.
  - Each seat contains:
    - Seat number
    - Booking status
    - Passenger name
    - Reservation ID

- **CRUD Operations**
  - Create reservation (book a seat)
  - Read reservation (view details)
  - Update reservation (modify passenger name)
  - Delete reservation (cancel booking)

- **File Persistence**
  - uses a GDBM database file (reservations.db) for persistent storage
  - Data is loaded when the program starts
  - Data is saved after any modification and on exit

- **Seat Map Display**
  - Displays all seats with status:
    - `A` = Available
    - `B` = Booked

- **Reports**
  - Total seats
  - Number of booked and available seats
  - List of all booked passengers

---

## Pros and Cons of the Solution

### Pros
- Simple and easy to use command-line interface
- Demonstrates core C programming concepts effectively
- Modular design improves readability and maintainability
- Persistent storage ensures data is not lost between runs
- Easy to compile and run without external libraries

### Cons
- Supports only a single airplane (no multiple flights)
- No concurrency handling (single user only)
- Limited validation for user input
- No graphical user interface (CLI only)

---

## How to Compile and Run

### Requirements

This program requires the GNU dbm (gdbm) library.

On Ubuntu/Debian:
```bash
sudo apt install libgdbm-dev

### Compile
```bash
gcc main.c reservation_functions.c -o reservation -lgdbm

### Run
```bash
./reservation

## Example Data Format (reservations.txt)
Each line in the file follows this format:
- SeatNumber|IsBooked|PassengerName|ReservationID

### Example:
1|0||
2|1|John Doe|R0002
3|0||

## Swmonstration
The program demonstrates:
- Loading reservation data from file
- Booking a seat
- Viewing and updating reservation details
- Deleting a reservation
- Saving data and maintaining persistence between runs

## Conclusion
This project successfully implements a functional reservation system in C while demonstrating key programming concepts such as file handling, structures, and modular design. It provides a solid foundation for extending into more advanced systems such as multi-user or network-based reservation platforms.