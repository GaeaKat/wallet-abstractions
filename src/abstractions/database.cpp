#include <abstractions/database.hpp>

namespace abstractions
{
    
    template <typename K, typename V>
    database_map<K, V>::database_map(database_map<K, V>&& db) {
        if (db.Command == nullptr) Database = db.Database;
        else if (db.Command.use_count() == 1) {
            Database = db.Command->execute(db.Database);
            Command = nullptr;
        }
        db.Command = nullptr;
        db.Database = nullptr;
    }
    
}
