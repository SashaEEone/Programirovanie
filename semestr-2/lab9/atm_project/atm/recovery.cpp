#include "recovery.h"
#include <unordered_map>
#include <iostream>

Recovery::Recovery(Journal& journal, FileStorage& storage)
    : m_journal(journal), m_storage(storage) {}

int Recovery::rebuildAccounts() {
    auto records = m_journal.readAll();
    if (records.empty()) return 0;

    // Map cardNumber -> most recent balance from journal
    std::unordered_map<std::string, double>      latestBalance;
    std::unordered_map<std::string, double>      dailyWithdrawn;
    std::unordered_map<std::string, std::time_t> lastDate;

    std::time_t now = std::time(nullptr);
    std::tm* nowTm  = std::localtime(&now);

    for (const auto& t : records) {
        std::string card(t.cardNumber);
        latestBalance[card] = t.balanceAfter;
        lastDate[card]      = t.timestamp;

        if (t.type == TransactionType::WITHDRAWAL) {
            std::tm* txTm = std::localtime(const_cast<std::time_t*>(&t.timestamp));
            if (txTm->tm_yday == nowTm->tm_yday && txTm->tm_year == nowTm->tm_year) {
                dailyWithdrawn[card] += t.amount;
            }
        }
    }

    int rebuilt = 0;
    auto accounts = m_storage.loadAccounts();
    for (auto& a : accounts) {
        auto it = latestBalance.find(a.cardNumber());
        if (it != latestBalance.end()) {
            double journalBalance = it->second;
            if (std::abs(journalBalance - a.balance()) > 0.001) {
                std::cout << "[Восстановление] Счёт " << a.cardNumber()
                          << ": баланс исправлен "
                          << std::fixed << a.balance()
                          << " -> " << journalBalance << " руб\n";
                a.setBalance(journalBalance);
                ++rebuilt;
            }
            if (dailyWithdrawn.count(a.cardNumber()))
                a.setDailyWithdrawn(dailyWithdrawn[a.cardNumber()]);
            if (lastDate.count(a.cardNumber()))
                a.setLastActivityDate(lastDate[a.cardNumber()]);
        }
    }
    if (rebuilt > 0) m_storage.saveAccounts(accounts);
    return rebuilt;
}
