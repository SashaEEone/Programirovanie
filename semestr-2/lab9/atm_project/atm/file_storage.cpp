#include "file_storage.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>
#include <iomanip>

// --- helpers ---
static std::string hashPin(const std::string& pin) {
    std::size_t h = std::hash<std::string>{}(pin + "atm_salt_2024");
    std::ostringstream oss;
    oss << std::hex << std::setw(16) << std::setfill('0') << h;
    return oss.str();
}

static std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string f;
    while (std::getline(ss, f, ',')) fields.push_back(f);
    return fields;
}

FileStorage::FileStorage(const std::string& dataDir) : m_dataDir(dataDir) {}

std::string FileStorage::cardsPath()    const { return m_dataDir + "/cards.csv"; }
std::string FileStorage::accountsPath() const { return m_dataDir + "/accounts.csv"; }

std::vector<Card> FileStorage::loadCards() const {
    std::vector<Card> cards;
    std::ifstream f(cardsPath());
    if (!f.is_open()) return cards;
    std::string line;
    std::getline(f, line); // skip header
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        auto fields = splitCSV(line);
        if (fields.size() < 3) continue;
        bool blocked = (fields[2] == "1");
        cards.emplace_back(fields[0], fields[1], blocked);
    }
    return cards;
}

bool FileStorage::saveCards(const std::vector<Card>& cards) const {
    std::ofstream f(cardsPath());
    if (!f.is_open()) return false;
    f << "number,pinHash,blocked\n";
    for (const auto& c : cards)
        f << c.number() << "," << c.pinHash() << "," << (c.isBlocked() ? "1" : "0") << "\n";
    return true;
}

std::optional<Card> FileStorage::findCard(const std::string& number) const {
    for (const auto& c : loadCards())
        if (c.number() == number) return c;
    return std::nullopt;
}

bool FileStorage::updateCard(const Card& card) const {
    auto cards = loadCards();
    for (auto& c : cards) {
        if (c.number() == card.number()) { c = card; return saveCards(cards); }
    }
    return false;
}

std::vector<Account> FileStorage::loadAccounts() const {
    std::vector<Account> accounts;
    std::ifstream f(accountsPath());
    if (!f.is_open()) return accounts;
    std::string line;
    std::getline(f, line); // skip header
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        auto fields = splitCSV(line);
        if (fields.size() < 4) continue;
        Account a(fields[0], std::stod(fields[1]));
        a.setDailyWithdrawn(std::stod(fields[2]));
        a.setLastActivityDate(static_cast<std::time_t>(std::stoll(fields[3])));
        accounts.push_back(a);
    }
    return accounts;
}

bool FileStorage::saveAccounts(const std::vector<Account>& accounts) const {
    std::ofstream f(accountsPath());
    if (!f.is_open()) return false;
    f << "cardNumber,balance,dailyWithdrawn,lastActivityDate\n";
    for (const auto& a : accounts)
        f << a.cardNumber() << "," << std::fixed << std::setprecision(2)
          << a.balance() << "," << a.dailyWithdrawn() << ","
          << static_cast<long long>(a.lastActivityDate()) << "\n";
    return true;
}

std::optional<Account> FileStorage::findAccount(const std::string& cardNumber) const {
    for (const auto& a : loadAccounts())
        if (a.cardNumber() == cardNumber) return a;
    return std::nullopt;
}

bool FileStorage::updateAccount(const Account& account) const {
    auto accounts = loadAccounts();
    for (auto& a : accounts) {
        if (a.cardNumber() == account.cardNumber()) {
            a = account;
            return saveAccounts(accounts);
        }
    }
    return false;
}

void FileStorage::seedIfEmpty() const {
    std::ifstream fc(cardsPath());
    if (fc.is_open()) return; // already exists

    // Demo cards: PIN 1234 and 5678
    std::ofstream f(cardsPath());
    f << "number,pinHash,blocked\n";
    f << "1234567890123456," << hashPin("1234") << ",0\n";
    f << "9876543210987654," << hashPin("5678") << ",0\n";
    f.close();

    std::ofstream fa(accountsPath());
    fa << "cardNumber,balance,dailyWithdrawn,lastActivityDate\n";
    fa << "1234567890123456,100000.00,0.00,0\n";
    fa << "9876543210987654,25000.00,0.00,0\n";
    fa.close();
}
