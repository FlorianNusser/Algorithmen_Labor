#ifndef LINKED_STACK_HPP
#define LINKED_STACK_HPP

#include <iostream>
#include "Element.hpp"


class LinkedStack {
private:
    Element* topElem; // Verweist auf das oberste Stack-Element

public:
    LinkedStack() : topElem(nullptr) {}

    bool empty() const {
        return topElem == nullptr;
    }

    void push(void* x) {
        Element* hilf = new Element(x);
        hilf->next = topElem;
        topElem = hilf;
    }

    void* top() const {
        if (empty()) {
            throw std::runtime_error("Stack ist leer");
        }
        return topElem->inhalt;
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("Stack ist leer");
        }
        Element* temp = topElem;
        topElem = topElem->next;
        delete temp; // Speicher freigeben
    }
};
#endif // LINKED_STACK_HPP