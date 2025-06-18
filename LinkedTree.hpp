
#ifndef LINKED_TREE_HPP
#define LINKED_TREE_HPP

#include <iostream>
#include "Knoten.hpp"

class LinkedTree {
private:
    Knoten* wurzel; // Wurzel des Baums

public:
    // Konstruktor für einen leeren Baum
    LinkedTree() : wurzel(nullptr) {}

    // Konstruktor für ein Blatt
    LinkedTree(int x) {
        wurzel = new Knoten(x);
    }

    // Neuer Konstruktor für internen Gebrauch (aus Knoten*)
    LinkedTree(Knoten* k) : wurzel(k) {}

    // Konstruktor für einen Baum mit linken und rechten Teilbaum
    LinkedTree(LinkedTree* l, int x, LinkedTree* r) {
        wurzel = new Knoten(x);
        if (l != nullptr) wurzel->links = l->wurzel;
        if (r != nullptr) wurzel->rechts = r->wurzel;
    }

    // Überprüft, ob der Baum leer ist
    bool empty() const {
        return wurzel == nullptr;
    }

    // Gibt das Element in der Wurzel zurück
    void* value() const {
        if (empty()) throw std::runtime_error("Baum ist leer");
        return (void*)(intptr_t)wurzel->inhalt;
    }

    // Gibt den linken Teilbaum zurück
    LinkedTree* left() const {
        if (empty()) throw std::runtime_error("Baum ist leer");
        return wurzel->links ? new LinkedTree(wurzel->links) : new LinkedTree();
    }

    // Gibt den rechten Teilbaum zurück
    LinkedTree* right() const {
        if (empty()) throw std::runtime_error("Baum ist leer");
        return wurzel->rechts ? new LinkedTree(wurzel->rechts) : new LinkedTree();
    }
};

#endif // LINKED_TREE_HPP
