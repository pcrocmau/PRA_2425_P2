#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <iostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() : tree(new BSTree<TableEntry<V>>()) {}

    ~BSTreeDict() {
        delete tree;
    }

    int entries() override {
        return tree->size();
    }

    void insert(std::string key, V value) override {
        tree->insert(TableEntry<V>(key, value));
    }

    V search(std::string key) override {
        TableEntry<V> e = tree->search(TableEntry<V>(key));
        return e.value;
    }

    V remove(std::string key) override {
        TableEntry<V> e = tree->search(TableEntry<V>(key));
        tree->remove(TableEntry<V>(key));
        return e.value;
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& d) {
        out << *(d.tree);
        return out;
    }
};

#endif

