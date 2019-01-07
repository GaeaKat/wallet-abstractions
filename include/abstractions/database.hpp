#ifndef ABSTRACTIONS_DATABASE_HPP
#define ABSTRACTIONS_DATABASE_HPP

#include "association.hpp"
#include "fundamental.hpp"

namespace abstractions
{
    
    template <typename K, typename V> 
    class database : association<K, V> {
    public:
        virtual bool insert(K k, V v) = 0;
        
        virtual bool remove(K k) = 0;
        
        virtual bool commit() = 0;
    };
    
    template <typename K, typename V> 
    class database_command {
        virtual abstract_map<K, V>* run(abstract_map<K, V>* db) const = 0;
    public:
        pointer<database_command<K, V>> Previous;
        database_command(database_command<K, V>* p) : Previous{p} {}
        
        virtual abstract_map<K, V>* execute(abstract_map<K, V>* db) const {
            if (Previous != nullptr) return run(database_command<K, V>::Previous->execute(db));
            return run(db);
        }
        
        virtual const V get(K k, abstract_map<K, V>* db) const = 0;
        
        database_command<K, V>* insert(K k, V v) const final override; // TODO
        
        database_command<K, V>* remove(K k) const final override; // TODO
    };
    
    template <typename K, typename V>
    class database_command_insert : database_command<K, V> {
        K Key;
        V Value;
        
        const V get(K k, abstract_map<K, V>* db) const final override {
            if (k == Key) return Value;
            return database_command<K, V>::Previous->get(k, db);
        };
        
        virtual abstract_map<K, V>* execute(abstract_map<K, V>* db) const final override {
            if (db == nullptr) return nullptr;
            return db->insert(Key, Value);
        };
    };
    
    template <typename K, typename V>
    class database_command_remove : database_command<K, V> {
        K Key;
        
        const V get(K k, abstract_map<K, V>* db) const {
            if (k == Key) return V{};
            return database_command<K, V>::Previous->get(k, db);
        };
        
        virtual abstract_map<K, V>* execute(abstract_map<K, V>* db) const {
            if (db == nullptr) return nullptr;
            return db->remove(Key);
        };
    };
    
    template <typename K, typename V>
    class database_map {
        // proof that this abstract class implements map. 
        static data::map::definition::map<database_map<K, V>*, K, V> is_map{};
        static data::map::definition::removable<database_map<K, V>*, K> is_removable{};
        
        abstract_map<K, V>* Database; 
        pointer<database_command<K, V>> Command;
        database_map(abstract_map<K, V>* db, pointer<database_command<K, V>> cmd) : Database{db}, Command{cmd} {}
        
    public:
        database_map(abstract_map<K, V>* db) : Database{db}, Command{nullptr} {}
        database_map(const database_map<K, V>& db) : Database{db.Database}, Command{db.Command} {}
        database_map(database_map<K, V>&& db);
        
        const V get(K k) const final override {
            return Command->get(k, Database);
        };

        database_map<K, V> insert(K k, V v) const {
            return new database_map{Database, Command->insert(k, v)};
        };
        
        database_map<K, V> remove(K k) const {
            return new database_map{Database, Command->remove(k)};
        };

    };
    
}

#endif

