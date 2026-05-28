#include "card.h"
#include <functional>
#include <sstream>
#include <iomanip>

Card::Card(const std::string& number, const std::string& pinHash, bool blocked)
    : m_number(number), m_pinHash(pinHash), m_blocked(blocked) {}

bool Card::verifyPin(const std::string& pin) const {
    return hashPin(pin) == m_pinHash;
}

void Card::block() {
    m_blocked = true;
}

void Card::resetAttempts() {
    m_failedAttempts = 0;
}

void Card::incrementAttempts() {
    ++m_failedAttempts;
}

// Simple deterministic hash (not cryptographic, suitable for demo)
std::string Card::hashPin(const std::string& pin) {
    std::size_t h = std::hash<std::string>{}(pin + "atm_salt_2024");
    std::ostringstream oss;
    oss << std::hex << std::setw(16) << std::setfill('0') << h;
    return oss.str();
}
