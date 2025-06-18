
#ifndef TREE_TOOLS_HPP
#define TREE_TOOLS_HPP

#include <iostream>
#include <queue>


// Hilfsklasse mit Baum-Algorithmen
class TreeTools {
public:
    // Berechnet die Höhe eines Baums (rekursiv)
    static int treeHeight(Tree* b) {
        if (b == nullptr || b->empty())
            return 0;
        return 1 + std::max(treeHeight(b->left()), treeHeight(b->right()));
    }

    // Berechnet die Anzahl der Knoten eines Baumes (rekursiv)
    static int anzahlKnoten(Tree* b) {
        if (b == nullptr || b->empty())
            return 0;
        return 1 + anzahlKnoten(b->left()) + anzahlKnoten(b->right());
    }

    // Gibt den Baum in Inorder-Traversierung mit Klammerung aus
    static void printTreeInorderWithParenthesis(Tree* b) {
        if (b == nullptr || b->empty())
            return;

        std::cout << "(";
        printTreeInorderWithParenthesis(b->left());
        std::cout << " " << b->value() << " ";
        printTreeInorderWithParenthesis(b->right());
        std::cout << ")";
    }

    // Gibt den Baum in Levelorder-Traversierung aus (Breitensuche)
    static void printTreeLevelorder(Tree* b) {
        if (b == nullptr || b->empty())
            return;

        std::queue<Tree*> q;
        q.push(b);

        while (!q.empty()) {
            Tree* current = q.front();
            q.pop();

            std::cout << current->value() << " ";

            if (current->left() != nullptr)
                q.push(current->left());
            if (current->right() != nullptr)
                q.push(current->right());
        }
    }

    // Sortiert eine Zahlenfolge per Suchbaum (Platzhalter)
    static int* searchTreeSort(int* zahlen, int size) {
        // TODO: Implementierung mit einem Suchbaum
        return zahlen;
    }

    // Druckt einen Baum ebenenweise aus
    static void printTree(Tree* b) {
        int resthoehe = treeHeight(b);
        for (int i = 0; i < resthoehe; i++) {
            printLevel(b, i, spaces(resthoehe - i));
            std::cout << std::endl << std::endl;
        }
    }

private:
    // Druckt eine Ebene eines Baumes basierend auf Level-Order Traversierung
    static void printLevel(Tree* b, int level, int spaces) {
        if (level == 0) {
            for (int i = 0; i < spaces; i++) std::cout << " ";
            if (b != nullptr) {
                std::cout << b->value();
            } else {
                std::cout << " ";
            }
            for (int i = 0; i <= spaces; i++) std::cout << " ";
        } else {
            if (b != nullptr && !b->left()->empty()) {
                printLevel(b->left(), level - 1, spaces);
            } else {
                printLevel(nullptr, level - 1, spaces);
            }
            if (b != nullptr && !b->right()->empty()) {
                printLevel(b->right(), level - 1, spaces);
            } else {
                printLevel(nullptr, level - 1, spaces);
            }
        }
    }

    // Berechnet Leerzeichen für korrekte Einrückung
    static int spaces(int level) {
        return (level == 1) ? 0 : 2 * spaces(level - 1) + 1;
    }
};

#endif // TREE_TOOLS_HPP