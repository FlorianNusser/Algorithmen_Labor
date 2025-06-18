#include <iostream>

class Element {
public:
    void* inhalt;  // Inhalt des Elements (ähnlich zu Java's Object)
    Element* next; // Verweis auf das nächste Element
    
    Element() : inhalt(nullptr), next(nullptr) {}
};



