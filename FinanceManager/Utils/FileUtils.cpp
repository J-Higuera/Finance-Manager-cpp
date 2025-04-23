#include "FileUtils.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace FileUtils {

    bool saveTransactions(const std::vector<Transaction>& transactions, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open " << filename << " for writing.\n";
            return false;
        }

        // CSV Format: type,amount,category,description
        for (const auto& t : transactions) {
            file << t.getType() << ","
                << t.getAmount() << ","
                << t.getCategory() << ","
                << t.getDescription() << "\n";
        }

        file.close();
        return true;
    }

    bool saveBudgets(const std::vector<Budget>& budgets, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open " << filename << " for writing.\n";
            return false;
        }

        // CSV Format: category,allocated,spent
        for (const auto& b : budgets) {
            file << b.getCategory() << ","
                << b.getAllocatedAmount() << ","
                << b.getSpent() << "\n";
        }

        file.close();
        return true;
    }

    std::vector<Transaction> loadTransactions(const std::string& filename) {
        std::vector<Transaction> transactions;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open " << filename << " for reading.\n";
            return transactions;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue; // skip empty lines
            std::stringstream ss(line);
            std::string type, amountStr, category, description;

            // Read CSV fields
            if (!std::getline(ss, type, ',')) continue;
            if (!std::getline(ss, amountStr, ',')) continue;
            if (!std::getline(ss, category, ',')) continue;
            if (!std::getline(ss, description, ',')) continue;

            double amount = std::stod(amountStr);

            Transaction t(type, amount, category, description);
            transactions.push_back(t);
        }
        file.close();
        return transactions;
    }

    std::vector<Budget> loadBudgets(const std::string& filename) {
        std::vector<Budget> budgets;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open " << filename << " for reading.\n";
            return budgets;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string category, allocatedStr, spentStr;

            if (!std::getline(ss, category, ',')) continue;
            if (!std::getline(ss, allocatedStr, ',')) continue;
            if (!std::getline(ss, spentStr, ',')) continue;

            double allocated = std::stod(allocatedStr);
            double spent = std::stod(spentStr);

            Budget b(category, allocated);
            // Manually apply the spent amount
            b.addSpending(spent);
            budgets.push_back(b);
        }
        file.close();
        return budgets;
    }

} // namespace FileUtils
