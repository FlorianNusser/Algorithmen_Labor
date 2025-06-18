#include <iostream>
#include "Element.hpp"

class LinkedQueue {
private:
    Element* head;
    Element* tail;

public:
    LinkedQueue() : head(nullptr), tail(nullptr) {}

    bool empty() const {
        return head == nullptr;
    }

    void enq(void* x) {
        Element* newElement = new Element(x);

        if (empty()) {
            head = tail = newElement;
        } else {
            tail->next = newElement;
            tail = tail->next;
        }
    }

    void deq() {
        if (empty()) {
            throw std::runtime_error("deq: Queue ist leer");
        }

        Element* temp = head;
        head = head->next;
        delete temp;  // Speicher freigeben

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void* front() const {
        if (empty()) {
            throw std::runtime_error("front: Queue ist leer");
        }
        return head->inhalt;
    }
};



