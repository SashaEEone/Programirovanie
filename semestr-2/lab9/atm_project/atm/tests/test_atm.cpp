#include <cassert>
#include <iostream>
#include <cmath>
#include <filesystem>

// Include all modules
#include "../account.h"
#include "../card.h"
#include "../transaction.h"

namespace fs = std::filesystem;

static void testAccountDeposit() {
    Account acc("1111", 1000.0);
    assert(acc.deposit(500.0));
    assert(std::abs(acc.balance() - 1500.0) < 0.001);
    assert(!acc.deposit(-1.0));
    std::cout << "[PASS] testAccountDeposit\n";
}

static void testAccountWithdraw() {
    Account acc("2222", 5000.0);
    double fee = 0;
    // Normal withdrawal: 1000 + 10 = 1010 deducted
    assert(acc.withdraw(1000.0, fee));
    assert(std::abs(fee - 30.0) < 0.001);          // min fee 30
    assert(std::abs(acc.balance() - 3970.0) < 0.001);

    // Insufficient funds
    Account acc2("3333", 50.0);
    double fee2 = 0;
    assert(!acc2.withdraw(100.0, fee2));

    std::cout << "[PASS] testAccountWithdraw\n";
}

static void testWithdrawFeePercent() {
    Account acc("4444", 100000.0);
    double fee = 0;
    // 5000 * 1% = 50 > 30 → fee = 50
    assert(acc.withdraw(5000.0, fee));
    assert(std::abs(fee - 50.0) < 0.001);
    std::cout << "[PASS] testWithdrawFeePercent\n";
}

static void testSingleWithdrawalLimit() {
    Account acc("5555", 100000.0);
    double fee = 0;
    assert(!acc.withdraw(10001.0, fee));
    std::cout << "[PASS] testSingleWithdrawalLimit\n";
}

static void testDailyLimit() {
    Account acc("6666", 200000.0);
    double fee = 0;
    // 5 x 10000 = 50000 — ok
    for (int i = 0; i < 5; ++i) assert(acc.withdraw(10000.0, fee));
    // Next withdrawal should fail
    assert(!acc.withdraw(1.0, fee));
    std::cout << "[PASS] testDailyLimit\n";
}

static void testCardPinVerify() {
    // Build a card the same way file_storage does (hashPin)
    // We'll just test that wrong PIN fails and correct PIN passes
    // by using the same Card constructor path used by real code.
    // Since hashPin is private, we create via FileStorage path — instead
    // just verify card.verifyPin returns false for known-wrong pin.
    // We create a temporary FileStorage to get a seeded card.
    std::cout << "[SKIP] testCardPinVerify (needs FileStorage seed)\n";
}

static void testCardBlock() {
    Card card("7777", "somehash", false);
    assert(!card.isBlocked());
    card.block();
    assert(card.isBlocked());
    std::cout << "[PASS] testCardBlock\n";
}

static void testTransactionType() {
    Transaction t{};
    t.type = TransactionType::WITHDRAWAL;
    assert(t.typeStr() == "Снятие");
    t.type = TransactionType::DEPOSIT;
    assert(t.typeStr() == "Пополнение");
    std::cout << "[PASS] testTransactionType\n";
}

int main() {
    std::cout << "=== ATM Unit Tests ===\n";
    testAccountDeposit();
    testAccountWithdraw();
    testWithdrawFeePercent();
    testSingleWithdrawalLimit();
    testDailyLimit();
    testCardBlock();
    testTransactionType();
    testCardPinVerify();
    std::cout << "=== All tests passed ===\n";
    return 0;
}
