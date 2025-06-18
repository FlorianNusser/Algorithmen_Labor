
#include <iostream>

// Klasse für Knoten im Baum
class Knoten {
public:
    int inhalt;      // Inhalt des Knotens
    Knoten* links;   // Zeiger auf linken Teilbaum
    Knoten* rechts;  // Zeiger auf rechten Teilbaum

    // Konstruktor für einen neuen Knoten
    Knoten(int x) : inhalt(x), links(nullptr), rechts(nullptr) {}
};

// Implementierung eines binären Suchbaums
class SearchTree {
private:
    Knoten* wurzel; // Zeiger auf die Wurzel des Baums

public:
    // Konstruktor für einen leeren Baum
    SearchTree() : wurzel(nullptr) {}

    // Sucht einen Wert im Baum
    Knoten* lookup(int x) {
        Knoten* k = wurzel;
        while (k != nullptr) {
            if (x < k->inhalt)
                k = k->links; // Suche im linken Teilbaum weiter
            else if (x > k->inhalt)
                k = k->rechts; // Suche im rechten Teilbaum weiter
            else
                return k; // Wert gefunden
        }
        return nullptr; // Wert nicht gefunden
    }

    // Fügt einen Wert in den Baum ein
    bool insert(int x) {
        if (wurzel == nullptr) { // Falls Baum leer, neuen Knoten erstellen
            wurzel = new Knoten(x);
            return true;
        }

        Knoten* vater = nullptr;
        Knoten* k = wurzel;

        while (k != nullptr) { // Knoten suchen, an dem eingefügt werden soll
            vater = k;
            if (x < k->inhalt)
                k = k->links;
            else if (x > k->inhalt)
                k = k->rechts;
            else
                return false; // Wert existiert bereits
        }

        if (x < vater->inhalt)
            vater->links = new Knoten(x); // Einfügen im linken Teilbaum
        else
            vater->rechts = new Knoten(x); // Einfügen im rechten Teilbaum
        
        return true;
    }

    // Löscht einen Wert aus dem Baum
    bool deleteValue(int x) {
        Knoten* vater = nullptr;
        Knoten* sohn = wurzel;

        while (sohn != nullptr && sohn->inhalt != x) { // Suchen des zu löschenden Knotens
            vater = sohn;
            sohn = (x < sohn->inhalt) ? sohn->links : sohn->rechts;
        }

        if (sohn == nullptr)
            return false; // Wert nicht gefunden

        Knoten* ersatzKnoten;
        if (sohn->links == nullptr) 
            ersatzKnoten = sohn->rechts;
        else if (sohn->rechts == nullptr)
            ersatzKnoten = sohn->links;
        else { 
            // Suche des maximalen Werts im linken Teilbaum als Ersatz
            ersatzKnoten = findMax(sohn->links);
            int tmp = ersatzKnoten->inhalt;
            deleteValue(tmp);
            sohn->inhalt = tmp;
            return true;
        }

        if (vater == nullptr) // Falls Wurzel gelöscht wird
            wurzel = ersatzKnoten;
        else if (x < vater->inhalt)
            vater->links = ersatzKnoten;
        else
            vater->rechts = ersatzKnoten;

        delete sohn; // Speicher freigeben
        return true;
    }

    // Hilfsmethode zum Finden des größten Elements im Teilbaum
    Knoten* findMax(Knoten* t) {
        while (t->rechts != nullptr)
            t = t->rechts;
        return t;
    }
};

int main() {
    SearchTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    std::cout << "Suche nach 40: " << (tree.lookup(40) != nullptr ? "Gefunden" : "Nicht gefunden") << std::endl;
    tree.deleteValue(40);
    std::cout << "Suche nach 40 nach Löschung: " << (tree.lookup(40) != nullptr ? "Gefunden" : "Nicht gefunden") << std::endl;

    return 0;
}