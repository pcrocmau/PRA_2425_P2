#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <iostream>

template <typename V>
class TableEntry {
public:
    std::string key;
    V value;

    TableEntry(std::string key, V value) : key(key), value(value) {}
    TableEntry(std::string key) : key(key), value(V{}) {}
    TableEntry() : key(""), value(V{}) {}

    friend bool operator==(const TableEntry<V>& e1, const TableEntry<V>& e2) {
        return e1.key == e2.key;
    }

    friend bool operator!=(const TableEntry<V>& e1, const TableEntry<V>& e2) {
        return e1.key != e2.key;
    }

    friend bool operator<(const TableEntry<V>& e1, const TableEntry<V>& e2) {
        return e1.key < e2.key;
    }

    friend bool operator>(const TableEntry<V>& e1, const TableEntry<V>& e2) {
        return e1.key > e2.key;
    }

    friend std::ostream& operator<<(std::ostream& out, const TableEntry<V>& e) {
        out << "{" << e.key << ": " << e.value << "}";
        return out;
    }
};

#endif

