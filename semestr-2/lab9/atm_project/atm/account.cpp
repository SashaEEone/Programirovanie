#include "account.h"
#include <stdexcept>
#include <cmath>

Account::Account(const std::string& cardNumber, double balance)
    : m_cardNumber(cardNumber), m_balance(balance) {}

void Account::checkDayRollover() {
    std::time_t now = std::time(nullptr);
    std::tm* nowTm  = std::localtime(&now);
    std::tm* lastTm = std::localtime(&m_lastActivityDate);

    if (m_lastActivityDate == 0 ||
        nowTm->tm_yday  != lastTm->tm_yday ||
        nowTm->tm_year  != lastTm->tm_year) {
        m_dailyWithdrawn = 0.0;
    }
    m_lastActivityDate = now;
}

bool Account::deposit(double amount) {
    if (amount <= 0) return false;
    checkDayRollover();
    m_balance += amount;
    return true;
}

bool Account::withdraw(double amount, double& fee) {
    if (amount <= 0) return false;
    if (amount > MAX_SINGLE_WITHDRAWAL) return false;

    checkDayRollover();
    if (m_dailyWithdrawn + amount > DAILY_LIMIT) return false;

    fee = std::max(amount * WITHDRAWAL_FEE_RATE, WITHDRAWAL_FEE_MIN);
    double total = amount + fee;
    if (m_balance < total) return false;

    m_balance        -= total;
    m_dailyWithdrawn += amount;
    return true;
}

void Account::resetDailyLimit() {
    m_dailyWithdrawn = 0.0;
}

void Account::applyTransaction(const Transaction& t) {
    switch (t.type) {
        case TransactionType::DEPOSIT:
            m_balance = t.balanceAfter;
            break;
        case TransactionType::WITHDRAWAL:
            m_balance        = t.balanceAfter;
            // Rebuild daily withdrawn (best-effort: only today's)
            {
                std::time_t now = std::time(nullptr);
                std::tm* nowTm  = std::localtime(&now);
                std::tm* txTm   = std::localtime(const_cast<std::time_t*>(&t.timestamp));
                if (nowTm->tm_yday == txTm->tm_yday && nowTm->tm_year == txTm->tm_year) {
                    m_dailyWithdrawn += t.amount;
                }
            }
            break;
        default:
            break;
    }
    m_lastActivityDate = t.timestamp;
}
