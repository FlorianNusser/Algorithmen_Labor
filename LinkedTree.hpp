#include <iostream>

class Knoten {
public:
    void* inhalt;  // Generischer Inhalt des Knotens
    Knoten* links; // Zeiger auf den linken Teilbaum
    Knoten* rechts; // Zeiger auf den rechten Teilbaum

    // Konstruktor für einen Knoten mit Inhalt
    Knoten(void* x) : inhalt(x), links(nullptr), rechts(nullptr) {}
};

class LinkedTree {
private:
    Knoten* wurzel; // Wurzel des Baums

public:
    // Konstruktor für einen leeren Baum
    LinkedTree() : wurzel(nullptr) {}

    // Konstruktor für ein Blatt
    LinkedTree(void* x) {
        wurzel = new Knoten(x);
    }

    // Konstruktor für einen Baum mit linken und rechten Teilbaum
    LinkedTree(LinkedTree* l, void* x, LinkedTree* r) {
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
        return wurzel->inhalt;
    }

    // Gibt den linken Teilbaum zurück
    LinkedTree* left() const {
        if (empty()) throw std::runtime_error("Baum ist leer");
        return new LinkedTree(wurzel->links);
    }

    // Gibt den rechten Teilbaum zurück
    LinkedTree* right() const {
        if (empty()) throw std::runtime_error("Baum ist leer");
        return new LinkedTree(wurzel->rechts);
    }
};


