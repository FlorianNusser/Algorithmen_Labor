#include <iostream>

class Queue {
public:
    virtual bool empty() const = 0; // Testet, ob die Queue leer ist
    virtual void enq(void* x) = 0; // Fügt x hinten ein
    virtual void* front() const = 0; // Liefert vorderstes Element
    virtual void deq() = 0; // Entfernt vorderstes Element

    virtual ~Queue() {} // Virtueller Destruktor für korrektes Polymorphismus-Verhalten
};
