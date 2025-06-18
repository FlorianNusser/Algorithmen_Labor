#include <iostream>

class LinkedStack {
private:
    Element* top; // Verweist auf das oberste Stack-Element

public:
    LinkedStack() : top(nullptr) {}

    bool empty() const {
        return top == nullptr;
    }

    void push(void* x) {
        Element* hilf = new Element(x);
        hilf->next = top;
        top = hilf;
    }

    void* topElement() const {
        if (empty()) {
            throw std::runtime_error("Stack ist leer");
        }
        return top->inhalt;
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("Stack ist leer");
        }
        Element* temp = top;
        top = top->next;
        delete temp; // Speicher freigeben
    }
};
