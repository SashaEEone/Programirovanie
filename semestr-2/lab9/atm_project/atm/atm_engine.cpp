#include "atm_engine.h"
#include <cstring>
#include <iostream>

AtmEngine::AtmEngine(FileStorage& storage, Journal& journal)
    : m_storage(storage), m_journal(journal) {}

bool AtmEngine::insertCard(const std::string& cardNumber) {
    m_authenticated = false;
    auto card = m_storage.findCard(cardNumber);
    if (!card) return false;
    m_card    = card;
    m_account = m_storage.findAccount(cardNumber);
    return true;
}

bool AtmEngine::enterPin(const std::string& pin) {
    if (!m_card || m_card->isBlocked()) return false;

    if (m_card->verifyPin(pin)) {
        m_card->resetAttempts();
        persistCard();
        m_authenticated = true;
        return true;
    }

    m_card->incrementAttempts();
    if (m_card->failedAttempts() >= MAX_PIN_ATTEMPTS) {
        m_card->block();
    }
    persistCard();
    return false;
}

bool AtmEngine::isCardBlocked() const {
    return m_card && m_card->isBlocked();
}

double AtmEngine::balance() const {
    return m_account ? m_account->balance() : 0.0;
}

bool AtmEngine::deposit(double amount) {
    if (!m_authenticated || !m_account) return false;
    if (!m_account->deposit(amount)) return false;
    auto t = makeTransaction(TransactionType::DEPOSIT, amount, m_account->balance());
    m_journal.append(t);
    persistAccount();
    return true;
}

bool AtmEngine::withdraw(double amount, double& fee, std::string& error) {
    if (!m_authenticated || !m_account) { error = "Сессия не активна"; return false; }

    if (amount > Account::MAX_SINGLE_WITHDRAWAL) {
        error = "Превышен лимит за одну операцию (10 000 руб)";
        return false;
    }
    if (m_account->dailyWithdrawn() + amount > Account::DAILY_LIMIT) {
        error = "Превышен суточный лимит (50 000 руб)";
        return false;
    }

    if (!m_account->withdraw(amount, fee)) {
        error = "Недостаточно средств";
        return false;
    }
    auto t = makeTransaction(TransactionType::WITHDRAWAL, amount, m_account->balance());
    m_journal.append(t);
    persistAccount();
    return true;
}

std::vector<Transaction> AtmEngine::history() const {
    if (!m_card) return {};
    return m_journal.lastN(m_card->number(), 5);
}

void AtmEngine::endSession() {
    m_card          = std::nullopt;
    m_account       = std::nullopt;
    m_authenticated = false;
}

void AtmEngine::persistCard() {
    if (m_card) m_storage.updateCard(*m_card);
}

void AtmEngine::persistAccount() {
    if (m_account) m_storage.updateAccount(*m_account);
}

Transaction AtmEngine::makeTransaction(TransactionType type, double amount, double balAfter) {
    Transaction t{};
    t.type        = type;
    t.amount      = amount;
    t.balanceAfter = balAfter;
    t.timestamp   = std::time(nullptr);
    std::strncpy(t.cardNumber, m_card->number().c_str(), sizeof(t.cardNumber) - 1);
    return t;
}
