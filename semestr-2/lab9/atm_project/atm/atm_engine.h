#pragma once
#include "card.h"
#include "account.h"
#include "journal.h"
#include "file_storage.h"
#include <string>
#include <optional>

// Core ATM session logic: PIN entry, operations, limits.
class AtmEngine {
public:
    static constexpr int MAX_PIN_ATTEMPTS = 3;

    AtmEngine(FileStorage& storage, Journal& journal);

    // Returns false if card not found
    bool insertCard(const std::string& cardNumber);

    // Returns true on success; blocks card after MAX_PIN_ATTEMPTS
    bool enterPin(const std::string& pin);

    bool isAuthenticated() const { return m_authenticated; }
    bool isCardBlocked()   const;

    double balance() const;
    bool   deposit(double amount);
    bool   withdraw(double amount, double& fee, std::string& error);

    // Last 5 transactions for current card
    std::vector<Transaction> history() const;

    void endSession();

private:
    FileStorage& m_storage;
    Journal&     m_journal;

    std::optional<Card>    m_card;
    std::optional<Account> m_account;
    bool                   m_authenticated = false;

    void persistCard();
    void persistAccount();
    Transaction makeTransaction(TransactionType type, double amount, double balAfter);
};
