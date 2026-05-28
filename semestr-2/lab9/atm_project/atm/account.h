#pragma once
#include <string>
#include <vector>
#include "transaction.h"

class Account {
public:
    static constexpr double WITHDRAWAL_FEE_RATE  = 0.01;   // 1%
    static constexpr double WITHDRAWAL_FEE_MIN   = 30.0;   // минимум 30 руб
    static constexpr double MAX_SINGLE_WITHDRAWAL = 10000.0;
    static constexpr double DAILY_LIMIT           = 50000.0;

    Account() = default;
    Account(const std::string& cardNumber, double balance);

    const std::string& cardNumber() const { return m_cardNumber; }
    double             balance()    const { return m_balance; }

    // Returns false if limits exceeded or insufficient funds
    bool deposit(double amount);
    bool withdraw(double amount, double& fee);

    double dailyWithdrawn() const { return m_dailyWithdrawn; }
    void   resetDailyLimit();

    // Called by recovery to rebuild state from journal
    void applyTransaction(const Transaction& t);

    // For persistence
    void setBalance(double b)           { m_balance = b; }
    void setDailyWithdrawn(double d)    { m_dailyWithdrawn = d; }
    void setLastActivityDate(std::time_t t) { m_lastActivityDate = t; }
    std::time_t lastActivityDate() const { return m_lastActivityDate; }

private:
    std::string m_cardNumber;
    double      m_balance           = 0.0;
    double      m_dailyWithdrawn    = 0.0;
    std::time_t m_lastActivityDate  = 0;

    void checkDayRollover();
};
