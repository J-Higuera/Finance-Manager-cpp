#pragma once

#include <string>
#include <memory>
#include <chrono>

// represents a single financial transaction income or expense
class Transaction {
public:
    // construct a transaction with type "income" or "expense" and amount, category, and description
    Transaction(std::string type,
        double amount,
        std::string category,
        std::string description);

    // accessors
    const std::string& getType() const;   // income or expense
    double              getAmount() const; // value
    const std::string& getCategory() const; // "groceries"
    const std::string& getDescription() const; // additional comments
    std::chrono::system_clock::time_point getDate() const; // timestamp of creation

    // convert this transaction into a CSV formatted string
    std::string toCSV() const;
    // parse a CSV line into a Transaction instance that returns nullptr if parsing fails
    static std::unique_ptr<Transaction> fromCSV(const std::string& line);

private:
    std::string m_type;        // "income" or "expense"
    double      m_amount;      // transaction amount
    std::string m_category;    // category tag
    std::string m_description; // description
    std::chrono::system_clock::time_point m_date; // when transaction was created
};
