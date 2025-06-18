#include <iostream>

// Dummy-Klasse für LinkedTree zur Veranschaulichung
class LinkedTree {
private:
    char inhalt;
    LinkedTree* links;
    LinkedTree* rechts;

public:
    // Konstruktor für ein Blatt
    LinkedTree(char x) : inhalt(x), links(nullptr), rechts(nullptr) {}

    // Konstruktor für einen Baum mit linken und rechten Teilbaum
    LinkedTree(LinkedTree* l, char x, LinkedTree* r) 
        : inhalt(x), links(l), rechts(r) {}

    // Prüft, ob der Baum leer ist
    bool empty() const {
        return this == nullptr;
    }

    // Gibt den linken Teilbaum zurück
    LinkedTree* left() const {
        return links;
    }

    // Gibt den rechten Teilbaum zurück
    LinkedTree* right() const {
        return rechts;
    }

    // Gibt den Wert der Wurzel zurück
    char value() const {
        return inhalt;
    }
};

// Dummy-Klasse für TreeTools zur Veranschaulichung
class TreeTools {
public:
    // Berechnet die Höhe eines Baums
    static int treeHeight(LinkedTree* b) {
        if (b == nullptr || b->empty())
            return 0;
        return 1 + std::max(treeHeight(b->left()), treeHeight(b->right()));
    }

    // Berechnet die Anzahl der Knoten eines Baums
    static int anzahlKnoten(LinkedTree* b) {
        if (b == nullptr || b->empty())
            return 0;
        return 1 + anzahlKnoten(b->left()) + anzahlKnoten(b->right());
    }

    // Gibt den Baum in Inorder-Traversierung mit Klammerung aus
    static void printTreeInorderWithParenthesis(LinkedTree* b) {
        if (b == nullptr || b->empty())
            return;

        std::cout << "(";
        printTreeInorderWithParenthesis(b->left());
        std::cout << " " << b->value() << " ";
        printTreeInorderWithParenthesis(b->right());
        std::cout << ")";
    }
};

