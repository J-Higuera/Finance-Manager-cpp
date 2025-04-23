#pragma once

#include "Transaction.h"
#include "Budget.h"
#include <vector>
#include <memory>
#include <string>

// manages all transactions and budgets for the application
class FinanceManager {
public:
    // record a new transaction and if it's an expense update the matching budget
    void addTransaction(std::unique_ptr<Transaction> transaction);

    // print all transactions, grouped by income and expense
    void displayAllTransactions() const;

    // remove a transaction by its index in the list
    void deleteTransaction(size_t index);

    // add a new budget category to track spending against
    void addBudget(std::unique_ptr<Budget> budget);

    // print all budget categories with their allocated and spent amounts
    void displayAllBudgets() const;

    // remove a budget by its index in the list
    void deleteBudget(size_t index);

    // accessors for UI loops or unit tests to inspect current data
    const std::vector<std::unique_ptr<Transaction>>& getTransactions() const { return m_transactions; }
    const std::vector<std::unique_ptr<Budget>>& getBudgets()      const { return m_budgets; }

    // persist all transactions and budgets to CSV files
    void saveData(const std::string& transactionFile, const std::string& budgetFile) const;
    // load transactions and budgets from CSV files restoring state
    void loadData(const std::string& transactionFile, const std::string& budgetFile);

private:
    // containers owning dynamically allocated Transaction and Budget objects.
    std::vector<std::unique_ptr<Transaction>> m_transactions;
    std::vector<std::unique_ptr<Budget>>      m_budgets;
};
