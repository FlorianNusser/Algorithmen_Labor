#include <iostream>

class Menge {
public:
    virtual bool empty() const = 0; // Testet, ob die Menge leer ist
    virtual void* lookup(void* x) const = 0; // Sucht x in der Menge
    virtual bool insert(void* x) = 0; // Fügt x in die Menge ein
    virtual bool remove(void* x) = 0; // Entfernt x aus der Menge

    virtual ~Menge() {} // Virtueller Destruktor für korrektes Polymorphismus-Verhalten
};

