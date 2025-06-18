#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <iostream>

class Element {
public:
    void* inhalt;  // Inhalt des Elements (ähnlich zu Java's Object)
    Element* next; // Verweis auf das nächste Element
    
    Element(void* data) : inhalt(data), next(nullptr) {}

};


#endif


