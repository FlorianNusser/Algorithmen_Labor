#ifndef KNOTEN_HPP
#define KNOTEN_HPP


#include <iostream>

class Knoten {
public:
    int inhalt;  // Inhalt des Knotens (ähnlich zu Java's Object)
    Knoten* links; // Verweis auf den linken Teilbaum
    Knoten* rechts; // Verweis auf den rechten Teilbaum

    // Konstruktor zum Initialisieren des Knotens mit Inhalt
    Knoten(int x) : inhalt(x), links(nullptr), rechts(nullptr) {}
};

#endif


