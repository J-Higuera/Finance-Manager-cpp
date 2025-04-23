#include "catch_amalgamated.hpp"      // Catch2 test framework
#include "../Classes/FinanceManager.h" // FinanceManager under test
#include "../Classes/Budget.h"         // Budget class under test

using namespace Catch;

// verify that a new FinanceManager starts with no budgets
TEST_CASE("Budgets start empty", "[Budget]") {
    FinanceManager fm;
    REQUIRE(fm.getBudgets().empty());
}

// verify that adding a Budget increases the collection and retains its data
TEST_CASE("Can add a budget", "[FinanceManager]") {
    FinanceManager fm;
    // create a new Budget for "rent" with $1200 allocation
    auto b = std::make_unique<Budget>("rent", 1200.0);
    fm.addBudget(std::move(b));

    const auto& budgets = fm.getBudgets();
    // expect exactly one budget stored
    REQUIRE(budgets.size() == 1);
    // verify its category and allocated amount
    CHECK(budgets[0]->getCategory() == "rent");
    CHECK(budgets[0]->getAllocatedAmount() == Approx(1200.0));
}

// verify that deleting a Budget removes it from the manager
TEST_CASE("Can delete a budget", "[FinanceManager]") {
    FinanceManager fm;
    // start with one budget
    fm.addBudget(std::make_unique<Budget>("food", 300.0));
    REQUIRE(fm.getBudgets().size() == 1);

    // delete the budget at index 0
    fm.deleteBudget(0);
    // expect no budgets remain
    REQUIRE(fm.getBudgets().empty());
}

// round‑trip serialization: toCSV() / fromCSV()
TEST_CASE("Budget CSV round‑trip", "[Budget]") {
    auto orig = std::make_unique<Budget>("utilities", 200.0);
    orig->addSpending(50.0);
    std::string line = orig->toCSV();

    auto restored = Budget::fromCSV(line);
    REQUIRE(restored);
    CHECK(restored->getCategory() == "utilities");
    CHECK(restored->getAllocatedAmount() == Approx(200.0));
    CHECK(restored->getSpent() == Approx(50.0));
    CHECK(restored->isResetMonthly() == true);
}
