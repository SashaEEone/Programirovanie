#pragma once
#include <string>

class Card {
public:
    Card() = default;
    Card(const std::string& number, const std::string& pinHash, bool blocked = false);

    const std::string& number()   const { return m_number; }
    bool               isBlocked() const { return m_blocked; }

    bool  verifyPin(const std::string& pin) const;
    void  block();
    void  resetAttempts();
    int   failedAttempts() const { return m_failedAttempts; }
    void  incrementAttempts();

    // For persistence
    const std::string& pinHash() const { return m_pinHash; }

private:
    std::string m_number;
    std::string m_pinHash;
    bool        m_blocked       = false;
    int         m_failedAttempts = 0;

    static std::string hashPin(const std::string& pin);
};
