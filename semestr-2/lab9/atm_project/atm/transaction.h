#pragma once
#include <ctime>
#include <cstdint>
#include <string>

enum class TransactionType : uint8_t {
    DEPOSIT    = 1,
    WITHDRAWAL = 2,
    BALANCE    = 3
};

struct Transaction {
    TransactionType type;
    double          amount;
    double          balanceAfter;
    std::time_t     timestamp;
    char            cardNumber[20];  // fixed-size for binary serialization

    std::string typeStr() const {
        switch (type) {
            case TransactionType::DEPOSIT:    return "Пополнение";
            case TransactionType::WITHDRAWAL: return "Снятие";
            case TransactionType::BALANCE:    return "Баланс";
        }
        return "Неизвестно";
    }
};
