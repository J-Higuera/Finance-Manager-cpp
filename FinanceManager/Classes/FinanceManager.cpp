#include "FinanceManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <ctime>
//utility for CSV import and export
#include "../Utils/FileUtils.h"

using namespace std;

// add a new transaction to the manager.
// if its an expense find the matching budget category and update its spent amount first.
void FinanceManager::addTransaction(unique_ptr<Transaction> transaction) {
    if (transaction->getType() == "expense") {
        for (auto& b : m_budgets) {
            if (b->getCategory() == transaction->getCategory()) {
                b->addSpending(transaction->getAmount());
                break;  // assume one budget per category
            }
        }
    }
    // transfer ownership of the transaction into our vector
    m_transactions.push_back(move(transaction));
}

// display all transactions and group incomes separately from expenses.
// if no items in a group, print "none" to show as empty.
void FinanceManager::displayAllTransactions() const {
    cout << "\n=== Income Transactions ===\n";
    bool anyIncome = false;
    for (const auto& up : m_transactions) {
        const auto& t = *up;
        if (t.getType() == "income") {
            cout << "$" << fixed << setprecision(2) << t.getAmount()
                << ", " << t.getDescription()
                << ", " << t.getCategory() << "\n";
            anyIncome = true;
        }
    }
    if (!anyIncome) cout << "  (none)\n";

    cout << "\n=== Expense Transactions ===\n";
    bool anyExpense = false;
    for (const auto& up : m_transactions) {
        const auto& t = *up;
        if (t.getType() == "expense") {
            cout << "$" << fixed << setprecision(2) << t.getAmount()
                << ", " << t.getDescription()
                << ", " << t.getCategory() << "\n";
            anyExpense = true;
        }
    }
    if (!anyExpense) cout << "  (none)\n";

    cout << "============================\n";
}

// remove a transaction by index (0 based).
// if the index is invalid print an error Otherwise erase and autosave the updated list.
void FinanceManager::deleteTransaction(size_t index) {
    if (index >= m_transactions.size()) {
        cout << "Invalid transaction number.\n";
        return;
    }
    m_transactions.erase(m_transactions.begin() + index);
    cout << "Deleted transaction #" << (index + 1) << "\n";
    FileUtils::saveItems<Transaction>(m_transactions, "transactions.csv");
}

// add a new budget category, spending will be tracked when expenses are added.
void FinanceManager::addBudget(unique_ptr<Budget> budget) {
    m_budgets.push_back(move(budget));
}

// display all budgets with their allocated amounts and current spent totals.
void FinanceManager::displayAllBudgets() const {
    cout << "\n=== All Budgets ===\n";
    for (const auto& up : m_budgets) {
        const auto& b = *up;
        cout << b.getCategory()
            << ", Allocated: $" << fixed << setprecision(2) << b.getAllocatedAmount()
            << ", Spent: $" << fixed << setprecision(2) << b.getSpent()
            << "\n";
    }
    cout << "====================\n";
}

// remove a budget by index, print its category, and autosave the updated list.
void FinanceManager::deleteBudget(size_t index) {
    if (index >= m_budgets.size()) {
        cout << "Invalid budget number.\n";
        return;
    }
    cout << "Deleted budget: " << m_budgets[index]->getCategory() << "\n";
    m_budgets.erase(m_budgets.begin() + index);
    FileUtils::saveItems<Budget>(m_budgets, "budgets.csv");
}

// save both transactions and budgets to their own CSV files.
void FinanceManager::saveData(const string& tf, const string& bf) const {
    FileUtils::saveItems<Transaction>(m_transactions, tf);
    FileUtils::saveItems<Budget>(m_budgets, bf);
}

// load transactions and budgets from CSV then reapply expense amounts
// to each budget so that the spent totals appear correctly.
void FinanceManager::loadData(const string& tf, const string& bf) {
    m_transactions = FileUtils::loadItems<Transaction>(tf);
    m_budgets = FileUtils::loadItems<Budget>(bf);

    // after loading regroup each expense transaction with its budget
    // to rebuild the spent totals.
    for (const auto& up : m_transactions) {
        if (up->getType() == "expense") {
            for (auto& bptr : m_budgets) {
                if (bptr->getCategory() == up->getCategory()) {
                    bptr->addSpending(up->getAmount());
                    break;
                }
            }
        }
    }
}
