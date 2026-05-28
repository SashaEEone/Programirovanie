#include "journal.h"
#include <cstring>
#include <iostream>
#include <algorithm>

Journal::Journal(const std::string& path) : m_path(path) {
    openAppend();
}

Journal::~Journal() {
    if (m_out.is_open()) m_out.close();
}

bool Journal::openAppend() {
    m_out.open(m_path, std::ios::binary | std::ios::app);
    return m_out.is_open();
}

bool Journal::append(const Transaction& t) {
    if (!m_out.is_open()) return false;
    m_out.write(reinterpret_cast<const char*>(&t), sizeof(Transaction));
    m_out.flush();
    return m_out.good();
}

std::vector<Transaction> Journal::readAll() const {
    std::vector<Transaction> records;
    std::ifstream in(m_path, std::ios::binary);
    if (!in.is_open()) return records;

    Transaction t;
    while (in.read(reinterpret_cast<char*>(&t), sizeof(Transaction))) {
        records.push_back(t);
    }
    return records;
}

std::vector<Transaction> Journal::lastN(const std::string& cardNumber, int n) const {
    auto all = readAll();
    std::vector<Transaction> result;
    for (auto it = all.rbegin(); it != all.rend(); ++it) {
        if (std::string(it->cardNumber) == cardNumber) {
            result.push_back(*it);
            if ((int)result.size() >= n) break;
        }
    }
    // Reverse so oldest first
    std::reverse(result.begin(), result.end());
    return result;
}
