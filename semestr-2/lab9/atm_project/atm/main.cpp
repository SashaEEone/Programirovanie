#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <ctime>

#include "file_storage.h"
#include "journal.h"
#include "recovery.h"
#include "atm_engine.h"

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void printSeparator() {
    std::cout << "----------------------------------------\n";
}

static std::string formatTime(std::time_t t) {
    char buf[32];
    std::tm* tm = std::localtime(&t);
    std::strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", tm);
    return buf;
}

static void showHistory(const std::vector<Transaction>& txs) {
    if (txs.empty()) { std::cout << "  История операций пуста\n"; return; }
    std::cout << std::left
              << std::setw(22) << "Дата/Время"
              << std::setw(14) << "Операция"
              << std::setw(12) << "Сумма"
              << "Баланс\n";
    printSeparator();
    for (const auto& t : txs) {
        std::cout << std::setw(22) << formatTime(t.timestamp)
                  << std::setw(14) << t.typeStr()
                  << std::fixed << std::setprecision(2)
                  << std::setw(12) << t.amount
                  << t.balanceAfter << " руб\n";
    }
}

static void mainMenu(AtmEngine& engine) {
    while (true) {
        printSeparator();
        std::cout << "  ГЛАВНОЕ МЕНЮ\n";
        printSeparator();
        std::cout << "  1. Проверить баланс\n"
                  << "  2. Снятие наличных\n"
                  << "  3. Пополнение счёта\n"
                  << "  4. История операций (последние 5)\n"
                  << "  0. Выйти (извлечь карту)\n";
        printSeparator();
        std::cout << "Выбор: ";

        int choice;
        if (!(std::cin >> choice)) { clearInput(); continue; }

        switch (choice) {
        case 1:
            std::cout << "\n  Баланс: " << std::fixed << std::setprecision(2)
                      << engine.balance() << " руб\n";
            break;

        case 2: {
            std::cout << "\n  Сумма для снятия (руб): ";
            double amount;
            if (!(std::cin >> amount) || amount <= 0) {
                clearInput();
                std::cout << "  Некорректная сумма\n";
                break;
            }
            double fee = 0;
            std::string err;
            if (engine.withdraw(amount, fee, err)) {
                std::cout << "  Выдано: " << std::fixed << std::setprecision(2)
                          << amount << " руб\n"
                          << "  Комиссия: " << fee << " руб\n"
                          << "  Остаток: " << engine.balance() << " руб\n";
            } else {
                std::cout << "  Ошибка: " << err << "\n";
            }
            break;
        }

        case 3: {
            std::cout << "\n  Сумма пополнения (руб): ";
            double amount;
            if (!(std::cin >> amount) || amount <= 0) {
                clearInput();
                std::cout << "  Некорректная сумма\n";
                break;
            }
            if (engine.deposit(amount)) {
                std::cout << "  Счёт пополнен на " << std::fixed << std::setprecision(2)
                          << amount << " руб\n"
                          << "  Новый баланс: " << engine.balance() << " руб\n";
            } else {
                std::cout << "  Ошибка при пополнении\n";
            }
            break;
        }

        case 4:
            std::cout << "\n  ИСТОРИЯ ПОСЛЕДНИХ 5 ОПЕРАЦИЙ\n";
            printSeparator();
            showHistory(engine.history());
            break;

        case 0:
            engine.endSession();
            std::cout << "\n  Карта извлечена. До свидания!\n\n";
            return;

        default:
            std::cout << "  Неверный выбор\n";
        }
    }
}

int main() {
    const std::string dataDir    = "data";
    const std::string journalPath = dataDir + "/journal.bin";

    // Create data directory
    system(("mkdir -p " + dataDir).c_str());

    FileStorage storage(dataDir);
    storage.seedIfEmpty();

    Journal  journal(journalPath);
    Recovery recovery(journal, storage);

    // --- Recovery on startup ---
    std::cout << "=== БАНКОМАТ v1.0 ===\n";
    std::cout << "[Запуск] Проверка журнала транзакций...\n";
    int rebuilt = recovery.rebuildAccounts();
    if (rebuilt > 0)
        std::cout << "[Восстановление] Исправлено счетов: " << rebuilt << "\n";
    else
        std::cout << "[Запуск] Данные актуальны\n";
    printSeparator();

    AtmEngine engine(storage, journal);

    while (true) {
        std::cout << "\nВведите номер карты (или 'q' для выхода): ";
        std::string cardNumber;
        std::cin >> cardNumber;
        if (cardNumber == "q" || cardNumber == "Q") break;

        if (!engine.insertCard(cardNumber)) {
            std::cout << "  Карта не найдена\n";
            continue;
        }

        if (engine.isCardBlocked()) {
            std::cout << "  Карта заблокирована. Обратитесь в банк.\n";
            continue;
        }

        // PIN entry
        bool pinOk = false;
        for (int attempt = 1; attempt <= AtmEngine::MAX_PIN_ATTEMPTS; ++attempt) {
            std::cout << "  Введите PIN (" << attempt << "/"
                      << AtmEngine::MAX_PIN_ATTEMPTS << "): ";
            std::string pin;
            std::cin >> pin;

            if (engine.enterPin(pin)) { pinOk = true; break; }

            if (engine.isCardBlocked()) {
                std::cout << "  Карта заблокирована после "
                          << AtmEngine::MAX_PIN_ATTEMPTS << " неверных попыток.\n";
                break;
            }
            std::cout << "  Неверный PIN\n";
        }

        if (pinOk) mainMenu(engine);
    }

    std::cout << "\nСистема выключена.\n";
    return 0;
}
