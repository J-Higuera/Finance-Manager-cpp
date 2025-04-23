#include "catch_amalgamated.hpp"        // Catch2 test framework
#include "../Classes/Transaction.h"     // Transaction class under test
#include "../Classes/Budget.h"          // Budget class under test (for expense tracking)
#include "../Classes/FinanceManager.h"  // FinanceManager under test

using namespace Catch;

// Verify a fresh FinanceManager has no data
TEST_CASE("FinanceManager starts empty", "[FinanceManager]") {
    FinanceManager fm;
    REQUIRE(fm.getTransactions().empty());  // no transactions initially
    REQUIRE(fm.getBudgets().empty());       // no budgets initially
}

// Test adding then removing a single transaction
TEST_CASE("Add and remove transactions", "[FinanceManager]") {
    FinanceManager fm;
    // create an expense transaction: $42 for "food", with description "lunch"
    auto tx = std::make_unique<Transaction>("expense", 42.0, "food", "lunch");
    fm.addTransaction(std::move(tx));       // store it

    REQUIRE(fm.getTransactions().size() == 1u);  // one transaction present

    fm.deleteTransaction(0);               // remove the first (and only) transaction
    REQUIRE(fm.getTransactions().empty()); // now none should remain
}

// Test adding then removing a single budget
TEST_CASE("Add and remove budgets", "[FinanceManager]") {
    FinanceManager fm;
    // create a budget of $300 for "groceries"
    auto b = std::make_unique<Budget>("groceries", 300.0);
    fm.addBudget(std::move(b));            // store it

    REQUIRE(fm.getBudgets().size() == 1u); // one budget present

    fm.deleteBudget(0);                    // remove that budget
    REQUIRE(fm.getBudgets().empty());      // none should remain afterwards
}

// Test that saveData/loadData round‑trips both transactions and budgets to CSV files
TEST_CASE("FinanceManager save and load", "[FinanceManager][IO]") {
    // Set up manager with one transaction and one budget
    FinanceManager fm1;
    fm1.addTransaction(std::make_unique<Transaction>("income", 100.0, "pay", "job"));
    fm1.addBudget(std::make_unique<Budget>("food", 50.0));
    fm1.saveData("test_tx.csv", "test_bg.csv");  // write to temporary CSVs

    // Load into a fresh manager
    FinanceManager fm2;
    fm2.loadData("test_tx.csv", "test_bg.csv");

    REQUIRE(fm2.getTransactions().size() == 1u); // transaction count preserved
    REQUIRE(fm2.getBudgets().size() == 1u); // budget count preserved

    // (Optionally: delete test_tx.csv and test_bg.csv here)
}
