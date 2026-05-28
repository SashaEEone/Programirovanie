#pragma once
#include "journal.h"
#include "account.h"
#include "file_storage.h"
#include <vector>

// Replays the binary journal to rebuild account balances after a crash.
class Recovery {
public:
    Recovery(Journal& journal, FileStorage& storage);

    // Reads all journal entries and writes corrected balances back to storage.
    // Returns number of accounts rebuilt.
    int rebuildAccounts();

private:
    Journal&     m_journal;
    FileStorage& m_storage;
};
