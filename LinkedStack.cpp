#include <iostream>

class Element {
public:
    void* inhalt;  // Generischer Inhalt des Elements
    Element* next; // Zeiger auf das nächste Element

    Element(void* data) : inhalt(data), next(nullptr) {}
};

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

int main() {
    LinkedStack stack;
    int a = 42, b = 17;

    stack.push(&a);
    stack.push(&b);

    std::cout << "Oberstes Element: " << *(int*)stack.topElement() << std::endl;
    stack.pop();
    std::cout << "Nach Pop oberstes Element: " << *(int*)stack.topElement() << std::endl;

    return 0;
}
