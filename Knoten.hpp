#include <iostream>

class Knoten {
public:
    void* inhalt;  // Inhalt des Knotens (ähnlich zu Java's Object)
    Knoten* links; // Verweis auf den linken Teilbaum
    Knoten* rechts; // Verweis auf den rechten Teilbaum

    // Konstruktor zum Initialisieren des Knotens mit Inhalt
    Knoten(void* x) : inhalt(x), links(nullptr), rechts(nullptr) {}
};



