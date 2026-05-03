# Airplane Reservation System (C Programming Capstone)

## Problem Statement
This project implements a simple airplane reservation system using the C programming language. The system manages seat bookings for a single airplane with a fixed number of seats. Users can create, view, update, and delete reservations through a command-line interface.

The goal of this project is to demonstrate fundamental C programming concepts including structures, arrays, modular design, and persistent data storage.

---

## Describe the Solution

The solution is implemented as a modular C application with multiple source files:

- `main.c` → Handles user interaction and menu navigation  
- `reservation.h` → Defines data structures and function prototypes  
- `reservation_functions.c` → Implements reservation logic and database operations  
- `Makefile` → Handles compilation  
- `reservations.db` → GDBM database file (auto-generated)

### Key Features

- **Seat Management**
  - 48 seats managed using an array of structures
  - Each seat stores:
    - Seat number
    - Booking status
    - Passenger name
    - Reservation ID

- **CRUD Operations**
  - Create reservation (book a seat)
  - Read reservation (view details)
  - Update reservation (modify passenger name)
  - Delete reservation (cancel booking)

- **Database Storage (GDBM)**
  - Uses GNU dbm (gdbm) for persistent storage
  - Each seat is stored as a key-value pair
  - Data persists between program executions

- **Seat Map Display**
  - `A` = Available
  - `B` = Booked

- **Reports**
  - Total seats
  - Booked vs available seats
  - Passenger list

---

## Pros and Cons of the Solution

### Pros
- Simple and intuitive command-line interface
- Demonstrates core C programming concepts effectively
- Modular design improves maintainability
- Uses GDBM database for efficient persistent storage
- No manual setup required before running

### Cons
- Supports only a single airplane
- No concurrency handling (single-user system)
- Limited input validation
- No graphical user interface

---

## How to Compile and Run

### Requirements
This program requires:
- GCC (GNU Compiler Collection)
- GNU dbm (gdbm) library
- make (build tool)

On Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential libgdbm-dev make
```

On Fedora/RHEL:
```bash
sudo dnf install gcc gdbm-devel make
```

### Compile
```bash
make
```

### Run
```bash
./reservation
```

### Clean Build Files
```bash
make clean
```

## Notes
The program uses a GDBM database file (reservations.db) for storage.
The database file is automatically created on first run.
No manual file setup is required.

## Swmonstration
The program demonstrates:
- Loading data from the database
- Creating reservations
- Viewing, updating, and deleting reservations
- Generating reports
- Maintaining data persistence across executions

## Conclusion
This project successfully implements a functional airplane reservation system in C using GDBM for persistent storage. 
It demonstrates key programming concepts such as modular design, file/database handling, and structured data management, providing a strong foundation for more advanced systems.