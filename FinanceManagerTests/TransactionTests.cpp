
#define CATCH_CONFIG_MAIN    // instruct Catch to provide a main() 
#include "catch_amalgamated.hpp"
#include "../Classes/Transaction.h"

using namespace Catch;

// verify that the transaction constructor and getters work correctly
TEST_CASE("Transaction getters work", "[Transaction]") {
    // create a sample income transaction
    Transaction t("income", 123.45, "salary", "April paycheck");

    // each getter should return the value passed into the constructor
    REQUIRE(t.getType() == "income");
    REQUIRE(t.getAmount() == Approx(123.45));
    REQUIRE(t.getCategory() == "salary");
    REQUIRE(t.getDescription() == "April paycheck");
}

// ensure that export to CSV and import back gives the same Transaction
TEST_CASE("Transaction CSV round‑trip", "[Transaction]") {
    // create an expense transaction and export it
    auto orig = std::make_unique<Transaction>("expense", 9.99, "food", "coffee");
    std::string line = orig->toCSV();

    // parse the CSV string back into a new Transaction instance
    auto restored = Transaction::fromCSV(line);
    REQUIRE(restored);  // Parsing should succeed and return a non-null pointer

    // the restored objects fields must match the original
    CHECK(restored->getType() == "expense");
    CHECK(restored->getAmount() == Approx(9.99));
    CHECK(restored->getCategory() == "food");
    CHECK(restored->getDescription() == "coffee");
}
