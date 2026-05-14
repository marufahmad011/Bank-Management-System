
A comprehensive, automated, and secure console-based banking application written entirely in the **C programming language**. This system digitizes manual banking operations, providing real-time balance updates, secure authentication, and permanent transaction records using C File Handling (without relying on external databases).

## 🎓 Academic Context
This project was developed as the final semester project for **Software Development I (CSE1290)**.
* **Institution:** Northern University Bangladesh (NUB)
* **Department:** Computer Science and Engineering (CSE)
* **Semester:** 2nd | **Section:** 2C
* **Supervised By:** Zarin Tasnim Rothy (Lecturer, Dept. of CSE)
* **Developed By:** * Maruf Ahmad (ID: 42230100448)
  * Uzzol Sing (ID: 42250302921)

---

## ✨ Core Features

1. **Account Creation:** Automatically generates unique Account Numbers and registers users with their Name, Initial Deposit, and Account Type (Savings/Current).
2. **Secure Login:** Two-factor styled console authentication requiring an Account Number and a 4-digit PIN.
3. **Balance Inquiry:** Real-time retrieval of available funds from the secure database file.
4. **Cash Deposit:** Validates positive integer inputs and safely updates user balances.
5. **Cash Withdrawal:** Includes strict logic to check for sufficient funds to prevent overdrafts.
6. **Fund Transfer:** Secure peer-to-peer transfers that independently verify the recipient, deduct from the sender, and update both files simultaneously.
7. **Transaction Logging:** Maintains a permanent, time-stamped audit trail (`transactions.txt`) of all deposits, withdrawals, and transfers.
8. **Update Profile:** Allows users to dynamically update their registered Contact Number or securely change their PIN.
9. **Mini-Statement:** Generates a concise history of the user's last 5 financial activities using efficient file pointer loops.
10. **Admin Dashboard:** A protected portal (requiring a master password) for bank employees to view system logs and monitor all registered accounts.

---

## 🛠️ Technology Stack
* **Language:** C Programming Language
* **Compiler:** GCC (GNU Compiler Collection)
* **IDE:** Visual Studio Code (VS Code)
* **Data Storage:** Native C File Handling (`.txt` files)
* **Core Libraries Used:** `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<time.h>`

---

## 📁 Repository Structure

```text
Bank-Management-System/
│
├── src/                  # Source Code Files
│   ├── main.c            # Application entry point & main menus
│   ├── account.c         # Logic for creation, login, and profiles
│   ├── transaction.c     # Logic for deposits, withdrawals, transfers
│   ├── admin.c           # Admin panel and logging logic
│   └── utils.c           # Safe input handling (fgets) & time functions
│
├── include/              # Header Files
│   ├── account.h
│   ├── transaction.h
│   ├── admin.h
│   └── utils.h
│
├── data/                 # Database Files (Generated on runtime)
│   ├── accounts.txt      # Stores user credentials and balances
│   ├── transactions.txt  # Stores time-stamped transaction logs
│   ├── logs.txt          # Stores system activity logs
│   └── temp.txt          # Temporary buffer for safe file modifications
│
└── README.md             # Project documentation