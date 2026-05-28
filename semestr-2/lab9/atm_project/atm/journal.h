#pragma once
#include "transaction.h"
#include <string>
#include <vector>
#include <fstream>

// Append-only binary journal of all transactions.
// Binary format per record: sizeof(Transaction) bytes (POD struct).
class Journal {
public:
    explicit Journal(const std::string& path);
    ~Journal();

    bool append(const Transaction& t);

    // Read all records from the file (for recovery / history)
    std::vector<Transaction> readAll() const;

    // Returns last N transactions for a given card
    std::vector<Transaction> lastN(const std::string& cardNumber, int n) const;

    const std::string& path() const { return m_path; }

private:
    std::string   m_path;
    std::ofstream m_out;

    bool openAppend();
};
