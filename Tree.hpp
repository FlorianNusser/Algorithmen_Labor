#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>

class Tree {
public:
    virtual bool empty() const = 0; // Prüft, ob der Baum leer ist
    virtual Tree* left() const = 0; // Gibt den linken Teilbaum zurück
    virtual Tree* right() const = 0; // Gibt den rechten Teilbaum zurück
    virtual void* value() const = 0; // Gibt das Wurzel-Element zurück

    virtual ~Tree() {} // Virtueller Destruktor für korrekte Speicherverwaltung
};

#endif // TREE_HPP