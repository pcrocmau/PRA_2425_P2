#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;
    BSNode<T>* root;

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) throw std::runtime_error("BSTree::search: element not found");
        if (n->elem < e) return search(n->right, e);
        if (n->elem > e) return search(n->left, e);
        return n;
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        }
        if (n->elem < e) {
            n->right = insert(n->right, e);
        } else if (n->elem > e) {
            n->left = insert(n->left, e);
        } else {
            throw std::runtime_error("BSTree::insert: element already exists");
        }
        return n;
    }

    void print_inorder(std::ostream& out, BSNode<T>* n) const {
        if (n == nullptr) return;
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }

    T max(BSNode<T>* n) const {
        if (n == nullptr) throw std::runtime_error("BSTree::max: empty subtree");
        if (n->right == nullptr) return n->elem;
        return max(n->right);
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n == nullptr) return nullptr;
        if (n->right == nullptr) {
            BSNode<T>* left = n->left;
            delete n;
            nelem--;
            return left;
        }
        n->right = remove_max(n->right);
        return n;
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) throw std::runtime_error("BSTree::remove: element not found");

        if (n->elem < e) {
            n->right = remove(n->right, e);
            return n;
        }
        if (n->elem > e) {
            n->left = remove(n->left, e);
            return n;
        }

        if (n->left == nullptr && n->right == nullptr) {
            delete n;
            nelem--;
            return nullptr;
        }
        if (n->left == nullptr) {
            BSNode<T>* r = n->right;
            delete n;
            nelem--;
            return r;
        }
        if (n->right == nullptr) {
            BSNode<T>* l = n->left;
            delete n;
            nelem--;
            return l;
        }

        T pred = max(n->left);
        n->elem = pred;
        n->left = remove_max(n->left);
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (n == nullptr) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:
    BSTree() : nelem(0), root(nullptr) {}

    int size() const { return nelem; }

    T search(T e) const {
        BSNode<T>* n = search(root, e);
        return n->elem;
    }

    T operator[](T e) const { return search(e); }

    void insert(T e) { root = insert(root, e); }

    void remove(T e) { root = remove(root, e); }

    ~BSTree() { delete_cascade(root); }

    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif

