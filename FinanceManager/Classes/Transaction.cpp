#include "Transaction.h"
#include <sstream>      // for CSV parsing/formatting
#include <utility>      // for std::move
#include <memory>       // for std::unique_ptr
#include <chrono>       // for timestamp

using namespace std;

Transaction::Transaction(string type,
    double amount,
    string category,
    string description)
    : m_type(move(type))
    , m_amount(amount)
    , m_category(move(category))
    , m_description(move(description))
    // capture the creation time of this transaction
    , m_date(chrono::system_clock::now())
{
}

const string& Transaction::getType()        const { return m_type; }
double              Transaction::getAmount()  const { return m_amount; }
const string& Transaction::getCategory()    const { return m_category; }
const string& Transaction::getDescription() const { return m_description; }
chrono::system_clock::time_point
Transaction::getDate() const { return m_date; }

// export this transaction as a CSV line type,amount,category,description
string Transaction::toCSV() const {
    ostringstream ss;
    ss << m_type << ","
        << m_amount << ","
        << m_category << ","
        << m_description;
    return ss.str();
}

// construct a Transaction from a CSV line that returns nullptr on parse failure
unique_ptr<Transaction> Transaction::fromCSV(const string& line) {
    istringstream ss(line);
    string type, amtStr, category, description;

    if (!getline(ss, type, ','))       return nullptr;
    if (!getline(ss, amtStr, ','))     return nullptr;
    if (!getline(ss, category, ','))   return nullptr;
    if (!getline(ss, description))     return nullptr;

    double amount = stod(amtStr);
    return make_unique<Transaction>(type, amount, category, description);
}
