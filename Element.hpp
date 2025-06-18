#include <iostream>

class Element {
public:
    void* inhalt;  // Inhalt des Elements (ähnlich zu Java's Object)
    Element* next; // Verweis auf das nächste Element
    
    Element() : inhalt(nullptr), next(nullptr) {}
};

int main() {
    Element e;
    std::cout << "Element erstellt!" << std::endl;
    return 0;
}

