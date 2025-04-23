# Finance Manager Program

A command line personal finance manager in C++ that lets you track income and expenses, set budgets, and saves your data to CSV files. Includes a complete suite of Catch2 unit tests to verify all functionality.

# Features

- Transactions: Add, view, and delete income or expense transactions each with a category and description.
- Budgets: Create, view, and delete category budgets, track spending against each budget.
- Persistence: Save and load data to/from CSV files ("transactions.csv" and "budgets.csv").
- Unit Tests: Comprehensive Catch2 test suite covering "Transaction", "Budget", and "FinanceManager" classes, plus I/O.

# Prerequisites

- Compiler: A C++14-compatible compiler (e.g., MSVC v143 in Visual Studio 2022).  
- Catch2: The single-header Catch2 test framework ("catch_amalgamated.hpp") included under "FinanceManagerTests/Header Files".

# Repository Layout

```
FinanceManager/            # Core library project (builds a .lib)
  Classes/                # Core class headers and implementations
    Budget.h/.cpp
    Transaction.h/.cpp
    FinanceManager.h/.cpp
  Utils/                  # FileUtils.h/.cpp for CSV load/save
FinanceManagerApp/         # Console application project
  Main.cpp                # CLI menu, calls into FinanceManager
  CMakeLists.txt (optional)
FinanceManagerTests/       # Unit‐test project (Catch2)
  BudgetTests.cpp
  TransactionTests.cpp
  FinanceManagerTests.cpp
  catch_amalgamated.hpp   # Catch2 header
transactions.csv           # Sample data file (auto-copied into App output)
budgets.csv                # Sample data file (auto-copied into App output)
README.md                  # Project documentation (this file)
```

# Building

1. Open the "FinanceManager.sln" solution in Visual Studio 2022.  
2. Make sure the FinanceManagerApp and FinanceManagerTests projects reference the "FinanceManager" project.  
3. Set the solution’s startup project to FinanceManagerApp, then Build & Run to launch the console UI.  
4. To run the unit tests, switch the startup project to FinanceManagerTests, then Debug ▶ Start without Debugging.

Tip: The CSV files ("transactions.csv" and "budgets.csv") are marked as _Content_ and _Copy to Output Directory_ so they appear next to the ".exe" automatically.

# Running the App

When you launch the app you’ll see a menu:

===== Finance Manager Menu =====
1 Add Transaction
2 View All Transactions
3 Delete Transaction
4 Add Budget
5 View All Budgets
6 Delete Budget
0 Exit
================================
Enter choice: 

Follow the prompts to manage your data. All changes are auto-saved to "transactions.csv" and "budgets.csv" in the same folder as the executable.

# Running Tests

The test suite covers:

- Transaction getters and CSV serialization/deserialization
- Budget: getters, spending accumulation, reset and CSV round-trip
- FinanceManager: add/delete, combined I/O save/load

To execute:
1. Set FinanceManagerTests as the Startup Project.  
2. Run it; you should see "All tests passed" if everything is green.

# Future Work

- Monthly reset scheduler: Automatically reset budgets each month.  
- Search & filtering: Filter transactions by date, category, or amount.  
- Reporting: Generate simple console-based spending reports or export to JSON.  
- GUI: Port the menu to a lightweight GUI (e.g., with Qt or ImGui).