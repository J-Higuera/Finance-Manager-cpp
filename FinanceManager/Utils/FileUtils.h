#pragma once
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>

// forward declarations of T::fromCSV and T::toCSV
namespace FileUtils {

    // Save any container of unique_ptr<T> where T has toCSV()
    template<typename T>
    bool saveItems(const std::vector<std::unique_ptr<T>>& items,
        const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: cannot open " << filename << " for writing\n";
            return false;
        }
        for (const auto& up : items) {
            file << up->toCSV() << "\n";
        }
        return true;
    }

    // Load into a vector<unique_ptr<T>> where T has static fromCSV()
    template<typename T>
    std::vector<std::unique_ptr<T>> loadItems(const std::string& filename) {
        std::vector<std::unique_ptr<T>> items;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: cannot open " << filename << " for reading\n";
            return items;
        }
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            auto ptr = T::fromCSV(line);
            if (ptr) items.push_back(std::move(ptr));
        }
        return items;
    }

} // namespace FileUtils
