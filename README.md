🏦 Bank Management System

A comprehensive console-based banking management system built with C++ featuring client management, transactions, user authentication, and currency exchange capabilities.
📋 Table of Contents

    Features
    System Architecture
    Prerequisites
    Installation
    Usage
    User Roles & Permissions
    File Structure
    Data Storage
    Security Features
    Screenshots
    Contributing
    License

✨ Features
👥 Client Management

    Add new clients with account details
    Update existing client information
    Delete client accounts
    Find clients by account number
    View all clients list
    Display client cards with complete information

💰 Transaction Operations

    Deposit: Add funds to client accounts
    Withdraw: Remove funds from client accounts (with balance validation)
    Transfer: Transfer money between accounts with logging
    Total Balances: View all client balances and total bank balance
    Transfer Log: Complete history of all transfer transactions

💱 Currency Exchange

    List all available currencies (190+ currencies supported)
    Find currency by code or country name
    Update currency exchange rates
    Currency calculator for conversions
    Real-time exchange rate calculations

🔐 User Management & Security

    User authentication system
    Role-based access control (RBAC)
    Granular permission system
    Login attempt limiting (3 failed attempts = lockout)
    Password encryption
    Login history tracking
    User CRUD operations (Create, Read, Update, Delete)

📊 Reporting & Logging

    Login register with timestamps
    Transfer log with complete transaction details
    Balance reports with text representation
    User activity tracking

🏗️ System Architecture

The system follows Object-Oriented Programming principles with the following class hierarchy:

clsPerson (Base Class)
    ├── clsBankClient (Client Management)
    └── clsUser (User Management & Authentication)

clsScreen (Base Screen Class)
    ├── Client Screens
    │   ├── clsClientsListScreen
    │   ├── clsAddNewClientScreen
    │   ├── clsDeleteClientScreen
    │   ├── clsUpdateClientScreen
    │   └── clsFindClientScreen
    ├── Transaction Screens
    │   ├── clsDepositScreen
    │   ├── clsWithdrawScreen
    │   ├── clsTransferScreen
    │   ├── clsTransferLogScreen
    │   └── clsTotalBalancesScreen
    ├── User Management Screens
    │   ├── clsListUsersScreen
    │   ├── clsAddNewUserScreen
    │   ├── clsDeleteUserScreen
    │   ├── clsUpdateUserScreen
    │   └── clsFindUserScreen
    ├── Currency Screens
    │   ├── clsCurrenciesListScreen
    │   ├── clsFindCurrencyScreen
    │   ├── clsUpdateCurrencyRateScreen
    │   └── clsCurrencyCalculatorScreen
    └── Main Navigation Screens
        ├── clsLoginScreen
        ├── clsMainScreen
        ├── clsTransactionsScreen
        ├── clsManageUsersScreen
        └── clsCurrencyExchangeMainScreen

🔧 Prerequisites

    C++ Compiler: GCC, Clang, or MSVC with C++11 or later
    Operating System: Windows (uses Windows-specific commands like system("cls") and system("pause>0"))
    Dependencies:
        clsInputValidate library
        clsString library
        clsDate library
        clsUtil library

📥 Installation

    Clone the repository:

bash

git clone https://github.com/yourusername/bank-management-system.git
cd bank-management-system

    Ensure all required library files are in the correct paths:
        clsInputValidate.h
        clsString.h
        clsDate.h
        clsUtil.h
    Create the required data files (if not present):
        Clients.txt
        Users.txt
        Currencies.txt
        LoginRegister.txt
        TransferLog.txt
    Compile the project:

bash

g++ Project3_MS.cpp -o BankSystem.exe

    Run the application:

bash

./BankSystem.exe

🚀 Usage
First Time Setup

    The system comes with sample data in the text files
    Default users can be found in Users.txt
    Login with valid credentials (Username and Password)

Main Menu Options

After successful login, users will see menu options based on their permissions:

    Show Clients List - Display all bank clients
    Add New Client - Register a new client account
    Delete Client - Remove a client from the system
    Update Client Info - Modify client details
    Find Client - Search for a specific client
    Transactions - Access transaction submenu
    Manage Users - Access user management submenu (Admin only)
    Login Register - View login history (Admin only)
    Currency Exchange - Access currency operations
    Logout - Exit to login screen

Transactions Submenu

    Deposit - Add money to a client account
    Withdraw - Remove money from a client account
    Total Balances - View all account balances
    Transfer - Transfer money between accounts
    Transfer Log - View transfer history
    Main Menu - Return to main menu

Currency Exchange Submenu

    List Currencies - Display all available currencies
    Find Currency - Search by code or country
    Update Rate - Modify exchange rates
    Currency Calculator - Convert between currencies
    Main Menu - Return to main menu

🔑 User Roles & Permissions

The system implements a bitwise permission system with the following permissions:
Permission	Value	Description
Full Access	-1	All permissions enabled
List Clients	1	View client list
Add New Client	2	Create new clients
Delete Client	4	Remove clients
Update Client	8	Modify client info
Find Client	16	Search for clients
Transactions	32	Access transaction features
Manage Users	64	User management access
Login Register	128	View login history
Currency Exchange	256	Access currency features

Permission Value Calculation: Permissions are combined using bitwise OR operations. For example:

    List Clients (1) + Add Client (2) + Find Client (16) = 19

📁 File Structure

bank-management-system/
│
├── Project3_MS.cpp              # Main application entry point
├── Global.h                     # Global variables (CurrentUser)
│
├── Core Classes/
│   ├── clsPerson.h              # Base person class
│   ├── clsBankClient.h          # Client business logic
│   ├── clsUser.h                # User authentication & management
│   ├── clsCurrency.h            # Currency operations
│   └── clsScreen.h              # Base screen class
│
├── Client Management Screens/
│   ├── clsClientsListScreen.h
│   ├── clsAddNewClientScreen.h
│   ├── clsDeleteClientScreen.h
│   ├── clsUpdateClientScreen.h
│   └── clsFindClientScreen.h
│
├── Transaction Screens/
│   ├── clsDepositScreen.h
│   ├── clsWithdrawScreen.h
│   ├── clsTransferScreen.h
│   ├── clsTransferLogScreen.h
│   ├── clsTotalBalancesScreen.h
│   └── clsTransactionsScreen.h
│
├── User Management Screens/
│   ├── clsListUsersScreen.h
│   ├── clsAddNewUserScreen.h
│   ├── clsDeleteUserScreen.h
│   ├── clsUpdateUserScreen.h
│   ├── clsFindUserScreen.h
│   └── clsManageUsersScreen.h
│
├── Currency Screens/
│   ├── clsCurrenciesListScreen.h
│   ├── clsFindCurrencyScreen.h
│   ├── clsUpdateCurrencyRateScreen.h
│   ├── clsCurrencyCalculatorScreen.h
│   └── clsCurrencyExchangeMainScreen.h
│
├── Navigation Screens/
│   ├── clsLoginScreen.h
│   ├── clsMainScreen.h
│   └── clsLoginRegisterScreen.h
│
└── Data Files/
    ├── Clients.txt              # Client records
    ├── Users.txt                # User accounts
    ├── Currencies.txt           # Currency data
    ├── LoginRegister.txt        # Login history
    └── TransferLog.txt          # Transfer transactions

💾 Data Storage
File Format

All data is stored in plain text files using the delimiter #//#:

Clients.txt:

FirstName#//#LastName#//#Email#//#Phone#//#AccountNumber#//#PinCode#//#Balance

Users.txt:

FirstName#//#LastName#//#Email#//#Phone#//#Username#//#EncryptedPassword#//#Permissions

Currencies.txt:

Country#//#CurrencyCode#//#CurrencyName#//#ExchangeRate

TransferLog.txt:

DateTime#//#SourceAccount#//#DestinationAccount#//#Amount#//#SourceBalance#//#DestBalance#//#Username

LoginRegister.txt:

DateTime#//#Username#//#EncryptedPassword#//#Permissions

🔒 Security Features

    Password Encryption: User passwords are encrypted using a simple encryption algorithm before storage
    Login Attempt Limiting: Maximum 3 failed login attempts before account lockout
    Permission-Based Access Control: Each screen checks user permissions before displaying
    Session Management: Current user context maintained throughout the session
    Audit Trail: All logins and transfers are logged with timestamps
    Input Validation: All user inputs are validated to prevent errors

📸 Screenshots

Add screenshots of your application here showing:

    Login screen
    Main menu
    Client list
    Transaction screen
    Currency exchange
    User management

🤝 Contributing

Contributions are welcome! Please follow these steps:

    Fork the repository
    Create a feature branch (git checkout -b feature/AmazingFeature)
    Commit your changes (git commit -m 'Add some AmazingFeature')
    Push to the branch (git push origin feature/AmazingFeature)
    Open a Pull Request

Coding Standards

    Follow C++ best practices
    Use meaningful variable and function names
    Comment complex logic
    Test all new features thoroughly

📝 Future Enhancements

    Database integration (MySQL/PostgreSQL)
    GUI interface using Qt or similar framework
    Enhanced encryption (AES, RSA)
    Email notifications
    Account statements generation
    Loan management system
    Credit/Debit card management
    Mobile banking integration
    Multi-language support
    Cross-platform compatibility (Linux, macOS)

🐛 Known Issues

    Windows-specific system calls limit cross-platform compatibility
    Plain text storage is not recommended for production use
    Simple encryption algorithm should be replaced with industry-standard encryption

📄 License

This project is licensed under the MIT License - see the LICENSE file for details.
👨‍💻 Author

🙏 Acknowledgments

    Programming Advices Course for the project foundation
    All contributors who help improve this project

⭐ If you found this project helpful, please consider giving it a star!
