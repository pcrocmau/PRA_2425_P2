#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "TableEntry.h"

#include "../../Pr1/PRA_2425_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;
    int max;
    ListLinked<TableEntry<V>>** table;

    int h(std::string key) {
        int sum = 0;
        for (size_t i = 0; i < key.size(); ++i)
            sum += int(key.at(i));
        return sum % max;
    }

public:
    HashTable(int size) : n(0), max(size) {
        if (max <= 0) throw std::invalid_argument("HashTable: invalid size");
        table = new ListLinked<TableEntry<V>>*[max];
        for (int i = 0; i < max; ++i)
            table[i] = new ListLinked<TableEntry<V>>();
    }

    ~HashTable() {
        if (table) {
            for (int i = 0; i < max; ++i)
                delete table[i];
            delete[] table;
        }
    }

    int capacity() { return max; }

    void insert(std::string key, V value) override {
        int idx = h(key);
        TableEntry<V> probe(key);
        for (int i = 0; i < table[idx]->size(); ++i) {
            if (table[idx]->get(i) == probe)
                throw std::runtime_error("HashTable::insert: key already exists");
        }
        table[idx]->append(TableEntry<V>(key, value));
        n++;
    }

    V search(std::string key) override {
        int idx = h(key);
        TableEntry<V> probe(key);
        for (int i = 0; i < table[idx]->size(); ++i) {
            if (table[idx]->get(i) == probe)
                return table[idx]->get(i).value;
        }
        throw std::runtime_error("HashTable::search: key not found");
    }

    V remove(std::string key) override {
        int idx = h(key);
        TableEntry<V> probe(key);
        for (int i = 0; i < table[idx]->size(); ++i) {
            if (table[idx]->get(i) == probe) {
                V val = table[idx]->get(i).value;
                table[idx]->remove(i);
                n--;
                return val;
            }
        }
        throw std::runtime_error("HashTable::remove: key not found");
    }

    int entries() override { return n; }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
        out << "HashTable(n=" << ht.n << ", max=" << ht.max << ")\n";
        for (int i = 0; i < ht.max; ++i) {
            out << i << ": ";
            if (ht.table[i]->size() == 0) {
                out << "NULL";
            } else {
                for (int j = 0; j < ht.table[i]->size(); ++j) {
                    out << ht.table[i]->get(j);
                    if (j + 1 < ht.table[i]->size())
                        out << " -> ";
                }
                out << " -> NULL";
            }
            out << "\n";
        }
        return out;
    }
};

#endif

