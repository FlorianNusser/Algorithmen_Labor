#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>



/******************************* Element.h ********************************/
// Element für LinkedQueue und LinkedStack

struct Element {
    void* inhalt;       // Inhalt des Elements
    Element* next;      // Zeiger auf das nächste Element
};


/****************************** Knoten.h *********************************/
// Knotenstruktur für Bäume mit Konstruktor

struct Knoten {
    void* inhalt;       // Inhalt des Knotens
    Knoten* links;      // linker Teilbaum
    Knoten* rechts;     // rechter Teilbaum

    Knoten(void* x) {
        inhalt = x;
        links = rechts = nullptr;
    }
};


/*************************** LinkedQueue.h *******************************/
// Implementierung einer Queue mit Zeigern


class LinkedQueue {
private:
    Element* head; // Zeiger auf Anfang der Queue
    Element* tail; // Zeiger auf Ende der Queue

public:
    LinkedQueue() : head(nullptr), tail(nullptr) {}

    bool empty() {
        return head == nullptr;
    }

    void enq(void* x) {
        if (empty()) {
            tail = head = new Element();
        } else {
            tail->next = new Element();
            tail = tail->next;
        }
        tail->inhalt = x;
        tail->next = nullptr;
    }

    void deq() {
        if (empty())
            throw std::runtime_error("deq: Queue ist leer");
        Element* temp = head;
        head = head->next;
        if (head == nullptr)
            tail = nullptr;
        delete temp;
    }

    void* front() {
        if (empty())
            throw std::runtime_error("front: Queue ist leer");
        return head->inhalt;
    }
};


/*************************** LinkedStack.h *******************************/
// Implementierung eines Stacks mit Zeigern



class LinkedStack {
private:
    Element* top; // Zeiger auf oberstes Element

public:
    LinkedStack() : top(nullptr) {}

    bool empty() {
        return top == nullptr;
    }

    void push(void* x) {
        Element* neu = new Element();
        neu->inhalt = x;
        neu->next = top;
        top = neu;
    }

    void* peek() {
        if (empty())
            throw std::runtime_error("Stack ist leer");
        return top->inhalt;
    }

    void pop() {
        if (empty())
            throw std::runtime_error("Stack ist leer");
        Element* temp = top;
        top = top->next;
        delete temp;
    }
};


/**************************** LinkedTree.h *******************************/
// Baumklasse mit Konstruktoren und Methoden

class LinkedTree;

class Tree {
public:
    virtual bool empty() = 0;
    virtual Tree* left() = 0;
    virtual Tree* right() = 0;
    virtual void* value() = 0;
    virtual ~Tree() {}
};

class LinkedTree : public Tree {
protected:
    Knoten* wurzel;

    LinkedTree(Knoten* k) : wurzel(k) {} // Nur intern genutzt

public:
    LinkedTree() : wurzel(nullptr) {}
    LinkedTree(void* x) : wurzel(new Knoten(x)) {}
    LinkedTree(LinkedTree* l, void* x, LinkedTree* r) {
        wurzel = new Knoten(x);
        if (l) wurzel->links = l->wurzel;
        if (r) wurzel->rechts = r->wurzel;
    }

    bool empty() override {
        return wurzel == nullptr;
    }

    void* value() override {
        if (empty()) throw std::runtime_error("Baum ist leer");
        return wurzel->inhalt;
    }

    Tree* left() override {
        if (empty()) throw std::runtime_error("Baum ist leer");
        return new LinkedTree(wurzel->links);
    }

    Tree* right() override {
        if (empty()) throw std::runtime_error("Baum ist leer");
        return new LinkedTree(wurzel->rechts);
    }
};


class SearchTree : public LinkedTree {
private:
    // Gibt den Knoten mit dem größten char-Wert zurück
    Knoten* findMax(Knoten* t) {
        while (t->rechts != nullptr)
            t = t->rechts;
        return t;
    }

    // Hilfsmethode zum Vergleich von char-Pointern
    int compareChars(void* a, void* b) {
        return *(char*)a - *(char*)b;
    }

public:
    void* lookup(char* x) {
        Knoten* k = wurzel;
        while (k != nullptr) {
            int cmp = compareChars(x, k->inhalt);
            if (cmp < 0)
                k = k->links;
            else if (cmp > 0)
                k = k->rechts;
            else
                return k->inhalt;
        }
        return nullptr;
    }

    bool insert(char* x) {
        if (wurzel == nullptr) {
            wurzel = new Knoten(x);
            return true;
        }

        Knoten* vater = nullptr;
        Knoten* k = wurzel;

        while (k != nullptr) {
            vater = k;
            int cmp = compareChars(x, k->inhalt);
            if (cmp < 0)
                k = k->links;
            else if (cmp > 0)
                k = k->rechts;
            else
                return false; // Schon vorhanden
        }

        if (compareChars(x, vater->inhalt) < 0)
            vater->links = new Knoten(x);
        else
            vater->rechts = new Knoten(x);
        return true;
    }

    bool deleteNode(char* x) {
        Knoten* vater = nullptr;
        Knoten* sohn = wurzel;

        while (sohn != nullptr && compareChars(x, sohn->inhalt) != 0) {
            vater = sohn;
            if (compareChars(x, sohn->inhalt) < 0)
                sohn = sohn->links;
            else
                sohn = sohn->rechts;
        }

        if (sohn != nullptr) {
            Knoten* ersatzKnoten;
            if (sohn->links == nullptr)
                ersatzKnoten = sohn->rechts;
            else if (sohn->rechts == nullptr)
                ersatzKnoten = sohn->links;
            else {
                ersatzKnoten = sohn;
                char* tmp = (char*)findMax(sohn->links)->inhalt;
                deleteNode(tmp);
                ersatzKnoten->inhalt = tmp;
                return true;
            }

            if (vater == nullptr)
                wurzel = ersatzKnoten;
            else if (compareChars(x, vater->inhalt) < 0)
                vater->links = ersatzKnoten;
            else
                vater->rechts = ersatzKnoten;

            delete sohn;
            return true;
        }

        return false;
    }
};


/**************************** TreeTools.h *******************************/
// Tools für Bäume (nur Gerüst, Methoden müssen noch implementiert werden)

class TreeTools {
public:
    static int treeHeight(Tree* b) {
        if (b == nullptr || b->empty())
            return 0;
        return 1 + std::max(treeHeight(b->left()), treeHeight(b->right()));
    }

    static int anzahlKnoten(Tree* b) {
        if (b == nullptr || b->empty())
            return 0;
        return 1 + anzahlKnoten(b->left()) + anzahlKnoten(b->right());
    }

    static void printTreeInorderWithParenthesis(Tree* b) {
        if (b == nullptr || b->empty())
            return;

        std::cout << "(";
        printTreeInorderWithParenthesis(b->left());
        std::cout << " " << *(char*)b->value() << " ";
        printTreeInorderWithParenthesis(b->right());
        std::cout << ")";
    }

    static void printTreeLevelorder(Tree* b) {
        if (b == nullptr || b->empty())
            return;

        std::queue<Tree*> q;
        q.push(b);

        while (!q.empty()) {
            Tree* current = q.front();
        q.pop();


        if (current != nullptr && !current->empty()) {
            std::cout << *(char*)current->value() << " ";

            Tree* leftChild = current->left();
            if (leftChild != nullptr && !leftChild->empty())
                q.push(leftChild);

            Tree* rightChild = current->right();
            if (rightChild != nullptr && !rightChild->empty())
                q.push(rightChild);
        }
        }
    }

    static int* searchTreeSort(int* zahlen, int size) {
        // TODO
        return nullptr;
    }

    static void printTree(Tree* b) {
        int resthoehe = treeHeight(b);
        for (int i = 0; i < resthoehe; i++) {
            printLevel(b, i, spaces(resthoehe - i));
            std::cout << std::endl << std::endl;
        }
    }

    static void printLevel(Tree* b, int level, int space) {
        if (level == 0) {
            for (int i = 0; i < space; ++i) std::cout << " ";
            if (b != nullptr) std::cout << b->value();
            else std::cout << " ";
            for (int i = 0; i <= space; ++i) std::cout << " ";
        } else {
            printLevel((b && !b->left()->empty()) ? b->left() : nullptr, level - 1, space);
            printLevel((b && !b->right()->empty()) ? b->right() : nullptr, level - 1, space);
        }
    }

    static int spaces(int level) {
        if (level == 1) return 0;
        return 2 * spaces(level - 1) + 1;
    }
};


//Hier beginnt Tree Tools Test, bzw die Main Datei

/******************************  TreeToolsTest.cpp  **************************/




int main() {
    // Erzeuge einen Test-Baum:
    //        /
    //      /   \
    //     +     -
    //    / \   / \
    //   F  *  X   Y
    //     / \
    //    A   B

    LinkedTree* a = new LinkedTree(new char('A'));
    LinkedTree* b = new LinkedTree(new char('B'));
    LinkedTree* m = new LinkedTree(a, new char('*'), b);
    LinkedTree* f = new LinkedTree(new char('F'));
    LinkedTree* p = new LinkedTree(f, new char('+'), m);
    LinkedTree* x = new LinkedTree(new char('X'));
    LinkedTree* y = new LinkedTree(new char('Y'));
    LinkedTree* n = new LinkedTree(x, new char('-'), y);
    LinkedTree* d = new LinkedTree(p, new char('/'), n);

    std::cout << "Baumstruktur (Inorder mit Klammern):" << std::endl;
    TreeTools::printTreeInorderWithParenthesis(d);
    std::cout << std::endl << std::endl;

    std::cout << "Baumstruktur (Levelorder):" << std::endl;
    TreeTools::printTreeLevelorder(d);
    std::cout << std::endl;

    std::cout << "Baumhöhe: " << TreeTools::treeHeight(d) << std::endl;
    std::cout << "Anzahl der Knoten: " << TreeTools::anzahlKnoten(d) << std::endl;

    return 0;
}


