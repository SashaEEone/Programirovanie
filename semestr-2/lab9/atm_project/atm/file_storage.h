#pragma once
#include "card.h"
#include "account.h"
#include <string>
#include <vector>
#include <optional>

// Stores cards and accounts as plain-text CSV files.
// Format cards.csv:   number,pinHash,blocked
// Format accounts.csv: cardNumber,balance,dailyWithdrawn,lastActivityDate
class FileStorage {
public:
    explicit FileStorage(const std::string& dataDir);

    // Cards
    std::vector<Card>           loadCards()  const;
    bool                        saveCards(const std::vector<Card>& cards) const;
    std::optional<Card>         findCard(const std::string& number) const;
    bool                        updateCard(const Card& card) const;

    // Accounts
    std::vector<Account>        loadAccounts() const;
    bool                        saveAccounts(const std::vector<Account>& accounts) const;
    std::optional<Account>      findAccount(const std::string& cardNumber) const;
    bool                        updateAccount(const Account& account) const;

    // Seed demo data if files don't exist
    void seedIfEmpty() const;

private:
    std::string m_dataDir;
    std::string cardsPath()    const;
    std::string accountsPath() const;
};
