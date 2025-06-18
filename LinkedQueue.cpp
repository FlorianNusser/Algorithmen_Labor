#include <iostream>

class Element {
public:
    void* inhalt;  // Inhalt des Elements (generischer Typ)
    Element* next; // Verweis auf das nächste Element

    Element(void* data) : inhalt(data), next(nullptr) {}
};

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

int main() {
    LinkedQueue queue;
    int a = 42, b = 17;

    queue.enq(&a);
    queue.enq(&b);

    std::cout << "Erstes Element: " << *(int*)queue.front() << std::endl;
    queue.deq();
    std::cout << "Nach Deq erstes Element: " << *(int*)queue.front() << std::endl;

    return 0;
}

