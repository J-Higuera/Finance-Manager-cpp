
#include "Budget.h"
#include <sstream>
#include <memory>
#include <utility>

using namespace std;

// construct a budget with a category name, and allocated amount.
// initializes spent to zero.
Budget::Budget(string category, double allocated, bool resetMonthly)
    : m_category(move(category))
    , m_allocatedAmount(allocated)
    , m_spent(0.0)
    , m_resetMonthly(resetMonthly)
{
}

// Accessors
const string& Budget::getCategory()        const { return m_category; }
double        Budget::getAllocatedAmount() const { return m_allocatedAmount; }
double        Budget::getSpent()           const { return m_spent; }

// record additional spending in this budget
void Budget::addSpending(double amount) {
    m_spent += amount;
}

// reset the spent total back to zero at the start of every month
void Budget::resetSpent() {
    m_spent = 0.0;
}

// export the Budget to a CSV line with category,allocated,spent,resetFlag
string Budget::toCSV() const {
    ostringstream ss;
    ss << m_category << ","
        << m_allocatedAmount << ","
        << m_spent << ","
        << (m_resetMonthly ? "1" : "0");  
    return ss.str();
}

// import a CSV line into a Budget object.
// format: category,allocated,spent,resetFlag
unique_ptr<Budget> Budget::fromCSV(const string& line) {
    istringstream ss(line);
    string category, allocStr, spentStr, resetStr;

    // parse each field if any fail return nullptr
    if (!getline(ss, category, ',')) return nullptr;
    if (!getline(ss, allocStr, ',')) return nullptr;
    if (!getline(ss, spentStr, ','))  return nullptr;
    if (!getline(ss, resetStr))       return nullptr;

    // convert numeric strings to double
    double allocated = stod(allocStr);
    double spent = stod(spentStr);
    bool   resetMonthly = (resetStr == "1");  // '1' means true

    // create and initialize a new Budget, then apply the spent amount
    auto b = make_unique<Budget>(category, allocated, resetMonthly);
    b->addSpending(spent);
    return b;
}
