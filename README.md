# ATM Machine Simulator
A console-based ATM system built in C++ that simulates real-world banking operations with secure login, account management, and persistent data storage.

---

## Overview

This project simulates the core functionalities of an ATM system using fundamental C++ concepts including **Object-Oriented Programming (OOP)**, **file handling**, and **menu-driven user interaction**. It is structured across two files — `atm.h` for core logic and `ATM.cpp` as the main driver.

---

## Features

### Account Management
- Create a new account with name, PIN, phone number, CNIC, and address
- Secure login using a unique account ID and 4-digit PIN
- Account blocking after **3 consecutive failed login attempts**

### Transactions
- **Deposit** — Add funds to your account
- **Withdraw** — Withdraw funds with balance validation
- **Transfer** — Send money to another account using recipient ID

### Security
- 4-digit PIN entry using `getch()` to hide input on screen
- Automatic account locking after multiple failed attempts

### Data Persistence
- All account data is stored in `DATABASE.txt`
- Data is read on startup and synced after every operation — no data lost between runs

---

## Project Structure

```
ATM-Machine/
├── atm.h          # Core classes, account logic, file sync functions
├── ATM.cpp        # Main driver — program flow & user interaction
└── DATABASE.txt   # Auto-generated file storing account data
```

---

## How It Works

### `atm.h`
- Defines the `account` class with attributes: `name`, `id`, `balance`, `pin`
- Handles ID generation, deposit, withdrawal, transfers
- Manages file read/write synchronization
- Implements account blocking logic

### `ATM.cpp`
- Calls functions from `atm.h`
- Provides a menu-driven interface for all operations
- Manages overall program flow

---

## Getting Started

### Prerequisites
- C++17 compatible compiler (e.g. `g++`, MSVC)

### Build & Run

```bash
# Clone the repository
git clone https://github.com/mrshaikhmuhammad/<repo-name>.git
cd <repo-name>

# Compile
g++ -std=c++17 ATM.cpp -o atm

# Run
./atm
```

---

## Usage

```
=============================
      Welcome to ATM
=============================
1. Create New Account
2. Login to Existing Account
3. Exit

Enter your choice: _
```

After login:
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

---

## Built With

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![File Handling](https://img.shields.io/badge/File_Handling-grey?style=for-the-badge)
![OOP](https://img.shields.io/badge/OOP-blue?style=for-the-badge)

---

## Author 
[![GitHub](https://img.shields.io/badge/GitHub-mrshaikhmuhammad-181717?style=flat&logo=github)](https://github.com/mrshaikhmuhammad) [![LinkedIn](https://img.shields.io/badge/LinkedIn-mrshaikhmuhammad-0A66C2?style=flat&logo=linkedin)](https://www.linkedin.com/in/mrshaikhmuhammad/)

---

## License

This project is open source and available under the [MIT License](LICENSE).
