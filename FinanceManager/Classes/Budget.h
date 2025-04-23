#pragma once

#include <string>
#include <memory>

class Budget {
public:
    Budget(std::string category, double allocated, bool resetMonthly = true);

    // category of this budget
    const std::string& getCategory() const;

    // The total allocated amount
    double getAllocatedAmount() const;

    // name for tests: same as getAllocatedAmount()
    double getAmount() const { return getAllocatedAmount(); }

    // how much has actually been spent so far
    double getSpent() const;

    // record additional spending against this budget
    void addSpending(double amount);

    // reset spent back to zero 
    void resetSpent();

    bool isResetMonthly() const { return m_resetMonthly; }

    // CSV export
    std::string toCSV() const;
    static std::unique_ptr<Budget> fromCSV(const std::string& line);

private:
    std::string m_category;
    double      m_allocatedAmount;
    double      m_spent;
    bool        m_resetMonthly;
};
