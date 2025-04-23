
#ifndef CATCH_CONFIG_MAIN

#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <iomanip>
#include "Classes/FinanceManager.h"

using namespace std;

// Displays the menu options to the console
static void showMenu() {
    cout << "\n===== Finance Manager Menu =====\n"
        << "1) Add Transaction\n"
        << "2) View All Transactions\n"
        << "3) Delete Transaction\n"
        << "4) Add Budget\n"
        << "5) View All Budgets\n"
        << "6) Delete Budget\n"          
        << "0) Exit\n"
        << "================================\n"
        << "Enter choice: ";
}

int main() {
    FinanceManager fm;
    // Load existing data files at startup
    fm.loadData("transactions.csv", "budgets.csv");

    bool running = true;
    while (running) {
        showMenu();
        int choice;
        // Validate numeric input
        if (!(cin >> choice)) {
            cin.clear(); // reset error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Delete rest of line

        switch (choice) {
        case 1: {  // add a new transaction
            string type, category, description;
            double amount;
            cout << "Enter transaction type (income/expense): ";
            getline(cin, type);
            cout << "Enter amount: ";
            cin >> amount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter category: ";
            getline(cin, category);
            cout << "Enter description (e.g. card name or notes): ";
            getline(cin, description);

            fm.addTransaction(make_unique<Transaction>(
                type, amount, category, description
            ));
            fm.saveData("transactions.csv", "budgets.csv");  // autosave after adding
            cout << "Transaction added!\n";
            break;
        }

        case 2:  // display all transactions
            fm.displayAllTransactions();
            break;

        case 3: {  // delete an existing transaction
            const auto& txs = fm.getTransactions();
            if (txs.empty()) {
                cout << "No transactions to delete.\n";
                break;
            }
            cout << "\n=== All Transactions ===\n";
            for (size_t i = 0; i < txs.size(); ++i) {
                const auto& t = *txs[i];
                cout << (i + 1) << ") $"
                    << fixed << setprecision(2) << t.getAmount()
                    << ", " << t.getDescription()
                    << ", " << t.getCategory()
                    << "\n";
            }
            cout << "Enter transaction number to delete: ";
            size_t tn;
            cin >> tn;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (tn < 1 || tn > txs.size()) {
                cout << "Invalid choice.\n";
            }
            else {
                fm.deleteTransaction(tn - 1);
                fm.saveData("transactions.csv", "budgets.csv");
            }
            break;
        }

        case 4: {  // add a new budget category
            string category;
            double amount;
            cout << "Enter budget category: ";
            getline(cin, category);
            cout << "Enter allocated amount: ";
            cin >> amount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            fm.addBudget(make_unique<Budget>(category, amount));
            fm.saveData("transactions.csv", "budgets.csv");
            cout << "Budget added!\n";
            break;
        }

        case 5:  // display all budgets
            fm.displayAllBudgets();
            break;

        case 6: {  // delete an existing budget
            const auto& bgs = fm.getBudgets();
            if (bgs.empty()) {
                cout << "No budgets to delete.\n";
                break;
            }
            cout << "\n=== All Budgets ===\n";
            for (size_t i = 0; i < bgs.size(); ++i) {
                const auto& b = *bgs[i];
                cout << (i + 1) << ") "
                    << b.getCategory()
                    << ", Allocated: $" << fixed << setprecision(2) << b.getAllocatedAmount()
                    << ", Spent: $" << fixed << setprecision(2) << b.getSpent()
                    << "\n";
            }
            cout << "Enter budget number to delete: ";
            size_t bn;
            cin >> bn;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (bn < 1 || bn > bgs.size()) {
                cout << "Invalid choice.\n";
            }
            else {
                fm.deleteBudget(bn - 1);
                fm.saveData("transactions.csv", "budgets.csv");
                cout << "Deleted budget #" << bn << "\n";
            }
            break;
        }

        case 0:  // exit program
            fm.saveData("transactions.csv", "budgets.csv");  // final save
            running = false;
            break;

        default:
            cout << "Invalid choice.\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}

#endif // CATCH_CONFIG_MAIN
