# ATM Machine Simulator

A console-based ATM system built in C++ that simulates real-world banking operations — secure login, account management, and persistent data storage.

> [!IMPORTANT]
> This project uses `getch()` from `<conio.h>`, which is a Windows-specific header. It will not compile on Linux or macOS without modification.

---

## Overview

This project simulates the core functionalities of an ATM system using fundamental C++ concepts including **Object-Oriented Programming (OOP)**, **file handling**, and **menu-driven user interaction**. 

---

## Features

### Account Management

- Create a new account with name, PIN, phone number, CNIC, and address
- Secure login using a unique auto-generated account ID and 4-digit PIN
- Account blocking after **3 consecutive failed login attempts**

### Transactions

- **Deposit** — Add funds to your account
- **Withdraw** — Withdraw funds with balance validation
- **Transfer** — Send money to another account using recipient ID

### Security

- 4-digit PIN entry using `getch()` to mask input on screen
- Automatic account locking after multiple failed attempts

### Data Persistence

- All account data is stored in `DATABASE.txt`, auto-generated on first run
- Data is loaded on startup and written after every operation — no data lost between runs

---

## Project Structure

```
atm-simulation/
├── src/
│   ├──  ATM.cpp     # Main driver — program flow & user interaction
|   └── DATABASE.txt    # Auto-generated on first run; stores all account records
├── LICENSE
└── README.md
```
> [!Tip]
> `DATABASE.txt` is created automatically in the same directory as the compiled binary the first time the program runs. Do not edit it manually — the program reads and writes it in a structured format.

---

## How It Works

### `Account Class`

Defines the `account` class with the following attributes:

| Attribute | Description |
|-----------|-------------|
| `name` | Account holder's full name |
| `id` | Auto-generated unique account ID |
| `balance` | Current account balance |
| `pin` | 4-digit PIN |
| `phone` | Contact phone number |
| `cnic` | CNIC (national ID number) |
| `address` | Residential address |
| `blocked` | Lock flag after failed login attempts |

It also handles:
- Auto-incrementing ID generation
- Deposit, withdrawal, and transfer logic
- Reading all accounts from `DATABASE.txt` into memory at startup
- Writing the updated account list back to `DATABASE.txt` after every operation

### `ATM.cpp`

- Loads account data from `DATABASE.txt` on launch
- Presents a main menu (create account / login / exit)
- After login, presents a transaction menu (balance / deposit / withdraw / transfer / logout)
- Calls corresponding methods from `account class`

---

## Getting Started

### Prerequisites

- **Windows OS** (required — uses `<conio.h>` for masked PIN input)
- A C++ compiler: `g++` via MinGW/MSYS2, or MSVC

>[!Tip]
> C++11 or later is sufficient. The `-std=c++17` flag is listed for compatibility but no C++17-specific features are used.

### Build & Run

```bash
# Clone the repository
git clone https://github.com/mrshaikhmuhammad/atm-simulation.git
cd atm-simulation

# Compile (from the repo root)
g++ src/ATM.cpp -o atm

# Run
./atm
```

---

## Usage

On launch:

```
=============================
      Welcome to ATM
=============================
1. Create New Account
2. Login to Existing Account
3. Exit

Enter your choice: _
```

After a successful login:

```
=============================
      Account Menu
=============================
1. Check Balance
2. Deposit Money
3. Withdraw Money
4. Transfer Funds
5. Logout
```

When creating a new account, you will be prompted for:
- Full name
- 4-digit PIN
- Phone number
- CNIC
- Address

Your **account ID** is auto-generated and displayed after creation — save it, as it is required to log in.

---

## Built With

[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Windows](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://www.microsoft.com/windows)

---

## Author

[![GitHub](https://img.shields.io/badge/GitHub-mrshaikhmuhammad-181717?style=flat&logo=github)](https://github.com/mrshaikhmuhammad)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-mrshaikhmuhammad-0A66C2?style=flat&logo=linkedin)](https://www.linkedin.com/in/mrshaikhmuhammad/)

---

## License

This project is open source and available under the [MIT License](LICENSE).
