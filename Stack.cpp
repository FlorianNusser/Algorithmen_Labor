#include <iostream>

class Stack {
public:
    virtual bool empty() const = 0; // Prüft, ob der Stack leer ist
    virtual void push(void* x) = 0; // Fügt x auf den Stack hinzu
    virtual void* top() const = 0; // Gibt das oberste Element zurück
    virtual void pop() = 0; // Entfernt das oberste Element

    virtual ~Stack() {} // Virtueller Destruktor für korrekte Speicherverwaltung
};

