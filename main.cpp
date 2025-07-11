#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>
#include <memory>
#include <random>
#include <iomanip>
#include <cmath>

/******************************* Element.h ********************************/
// Element für LinkedQueue und LinkedStack

template <typename T>
struct Element
{
    T inhalt;      // Inhalt des Elements
    Element *next; // Zeiger auf das nächste Element
};

/****************************** Knoten.h *********************************/
// Knotenstruktur für Bäume mit Konstruktor

template <typename T>
struct Knoten
{
    std::shared_ptr<T> inhalt;         // Inhalt des Knotens mit smart pointer
    std::shared_ptr<Knoten<T> > links;  // linker Teilbaum
    std::shared_ptr<Knoten<T> > rechts; // rechter Teilbaum

    Knoten(std::shared_ptr<T> x) : inhalt(x), links(nullptr), rechts(nullptr) {}
};

/*************************** LinkedQueue.h *******************************/
// Implementierung einer Queue mit Zeigern

template <typename T>
class LinkedQueue
{
private:
    Element<T> *head; // Zeiger auf Anfang der Queue (Vorderstes Element)
    Element<T> *tail; // Zeiger auf Ende der Queue (Letztes Element)

public:
    LinkedQueue() : head(nullptr), tail(nullptr) {}

    bool empty()
    {
        return head == nullptr;
    }

    // Fügt ein neues Element am Ende hinzu
    void enq(T x)
    {
        if (empty())
        {
            tail = head = new Element<T>();
        }
        else
        {
            tail->next = new Element<T>();
            tail = tail->next;
        }
        tail->inhalt = x;
        tail->next = nullptr;
    }

    // Entfernt das vorderste Element
    void deq()
    {
        if (empty())
            throw std::runtime_error("deq: Queue ist leer");
        Element<T> *temp = head;
        head = head->next;
        if (head == nullptr)
            tail = nullptr; // falls letztes Element entfernt wurde
        delete temp;
    }

    // Gibt Inhalt des vordersten Elements zurück
    T front()
    {
        if (empty())
            throw std::runtime_error("front: Queue ist leer");
        return head->inhalt;
    }
};

/*************************** LinkedStack.h *******************************/
// Implementierung eines verketteten Stacks mit Zeigern

template <typename T>
class LinkedStack
{
private:
    Element<T> *top; // Zeiger auf oberstes Element

public:
    LinkedStack() : top(nullptr) {}

    bool empty() const
    {
        return top == nullptr;
    }

    // Fügt ein neues Element oben auf den Stack
    void push(T x)
    {
        Element<T> *neu = new Element<T>{x, top}; // Evtl. Fehler dank meines Kompilers
        top = neu;
    }

    // Gibt das oberste Element zurück (ohne Entfernen)
    T peek()
    {
        if (empty())
            throw std::runtime_error("Stack ist leer");
        return top->inhalt;
    }

    // Entfernt das oberste Element
    void pop()
    {
        if (empty())
            throw std::runtime_error("Stack ist leer");
        Element<T> *temp = top;
        top = top->next;
        delete temp;
    }
};

/**************************** LinkedTree.h *******************************/
// Baumklasse mit Konstruktoren und Methoden

template <typename T>
class Tree
{
public:
    virtual bool empty() = 0;
    virtual Tree<T> *left() = 0;
    virtual Tree<T> *right() = 0;
    virtual T value() = 0;
    virtual ~Tree() {}
};

// Konkrete Implementierung des Baumes
template <typename T>
class LinkedTree : public Tree<T>
{
protected:
    std::shared_ptr<Knoten<T> > wurzel;

    // interner Konstruktor (z.B. für left()/right())
    LinkedTree(std::shared_ptr<Knoten<T> > k) : wurzel(k) {}

public:
    LinkedTree() : wurzel(nullptr) {}
    LinkedTree(T x)
    {
        auto inhaltPtr = std::make_shared<T>(x);
        wurzel = std::make_shared<Knoten<T> >(inhaltPtr);
    }

    // Konstruktor mit linken & rechten Teilbaum
    LinkedTree(LinkedTree<T> *l, T x, LinkedTree<T> *r)
    {
        auto inhaltPtr = std::make_shared<T>(x);
        wurzel = std::make_shared<Knoten<T> >(inhaltPtr);
        if (l)
            wurzel->links = l->wurzel;
        if (r)
            wurzel->rechts = r->wurzel;
    }

    bool empty() override
    {
        return wurzel == nullptr;
    }

    T value() override
    {
        if (empty())
            throw std::runtime_error("Baum ist leer");
        return *(wurzel->inhalt);
    }

    Tree<T> *left() override
    {
        if (empty())
            throw std::runtime_error("Baum ist leer");
        return new LinkedTree<T>(wurzel->links);
    }

    Tree<T> *right() override
    {
        if (empty())
            throw std::runtime_error("Baum ist leer");
        return new LinkedTree<T>(wurzel->rechts);
    }
    ~LinkedTree() {}
};

template <typename T, typename Compare = std::less<T> >
class SearchTree : public LinkedTree<T>
{
private:
    // Gibt den Knoten mit dem größten char-Wert im Teilbaum t zurück
    using LinkedTree<T>::wurzel;
    Compare comp;

    std::shared_ptr<Knoten<T> > findMax(std::shared_ptr<Knoten<T> > node)
    {
        while (node->rechts) // geht so weit wie möglich nach rechts
            node = node->rechts;
        return node;
    }

    // Hilfsmethode zum Vergleich von char-Pointern
    int compareChars(void *a, void *b)
    {
        return *(char *)a - *(char *)b; // lexikografischer Vergleich
    }

public:
    // Sucht ein Element mit dem Wert x (char*) im Suchbaum
    T *lookup(T x)
    {
        auto node = wurzel;
        while (node)
        {
            if (comp(x, *(node->inhalt)))
                node = node->links; // links weiter suchen
            else if (comp(*(node->inhalt), x))
                node = node->rechts; // rechts weiter suchen
            else
                return node->inhalt.get(); // gefunden
        }
        return nullptr; // nicht gefunden
    }

    // Füht ein neues Element x ein, falls es noch nicht existiert
    bool insert(T x)
    {
        auto neu = std::make_shared<T>(x);
        if (!wurzel)
        {
            wurzel = std::make_shared<Knoten<T> >(neu); // neuer Wurzelknoten
            return true;
        }

        std::shared_ptr<Knoten<T> > vater = nullptr;
        auto current = wurzel;

        while (current)
        {
            vater = current;
            if (comp(x, *(current->inhalt)))
                current = current->links;
            else if (comp(*(current->inhalt), x))
                current = current->rechts;
            else
                return false; // Schon vorhanden
        }

        // Neuen Knoten als Kind des gefundenen "Vaters" eingefügen
        if (comp(x, *(vater->inhalt)))
            vater->links = std::make_shared<Knoten<T> >(neu);
        else
            vater->rechts = std::make_shared<Knoten<T> >(neu);
        return true;
    }

    // Löscht das Element mit dem Wert x aus dem Baum
    bool deleteNode(char *x)
    {
        Knoten<T> *vater = nullptr;
        Knoten<T> *sohn = wurzel;

        // Suche nach dem zu löschenden Knoten
        while (sohn != nullptr && compareChars(x, sohn->inhalt.get()) != 0)
        {
            vater = sohn;
            if (compareChars(x, sohn->inhalt.get()) < 0)
                sohn = sohn->links;
            else
                sohn = sohn->rechts;
        }

        // Fall: nur ein Kind oder kein Kind
        if (sohn != nullptr)
        {
            Knoten<T> *ersatzKnoten;
            if (sohn->links == nullptr)
                ersatzKnoten = sohn->rechts;
            else if (sohn->rechts == nullptr)
                ersatzKnoten = sohn->links;
            else
            {
                // Zwei Kinder: FInde größtes Element im linken Teilbaum
                ersatzKnoten = sohn;
                char *tmp = (char *)findMax(sohn->links)->inhalt.get();
                deleteNode(tmp);                                   // rekursiv löschen
                ersatzKnoten->inhalt = std::make_shared<char>(*tmp); // Wert ersetzen 
                return true;
            }

            // Zeiger des Elternknotens anpassen
            if (vater == nullptr)
                wurzel = ersatzKnoten;
            else if (compareChars(x, vater->inhalt.get()) < 0)
                vater->links = ersatzKnoten;
            else
                vater->rechts = ersatzKnoten;

            return true;
        }

        return false; // Element nicht gefunden
    }
};

/**************************** TreeTools.h *******************************/
// Tools für Bäume (nur Gerüst, Methoden müssen noch implementiert werden)

template <typename T>
class TreeTools
{
// Fügt alle Elemente des Baums in sortierter Reihenfolge auf den Stack
private:
static void tree2SortedStack(Tree<int>* b, LinkedStack<int>& k) {
    if (b == nullptr || b->empty()) return;
    tree2SortedStack(b->right(), k);       // rechts zuerst (damit es auf dem Stack umgekehrt sortiert ist)
    k.push(b->value());                    // aktuelle Wurzel
    tree2SortedStack(b->left(), k);        // dann links
}

public:
    // Berechnet die Höhe des Baums
    static int treeHeight(Tree<T> *b)
    {
        if (b == nullptr || b->empty())
            return 0;
        return 1 + std::max(treeHeight(b->left()), treeHeight(b->right()));
    }

    // Zählt die Anzahl aller Knoten im Baum
    static int anzahlKnoten(Tree<T> *b)
    {
        if (b == nullptr || b->empty())
            return 0;
        return 1 + anzahlKnoten(b->left()) + anzahlKnoten(b->right());
    }

    // Gibt den Baum in Inorder-Notation mit Klammern aus
    static void printTreeInorderWithParenthesis(Tree<T> *b)
    {
        if (b == nullptr || b->empty())
            return;

        std::cout << "(";
        printTreeInorderWithParenthesis(b->left());
        std::cout << " " << b->value() << " ";
        printTreeInorderWithParenthesis(b->right());
        std::cout << ")";
    }
    // Levelorder-Ausgabe (Breitensuche)
    static void printTreeLevelorder(Tree<T> *b)
    {
        if (b == nullptr || b->empty())
            return;

        std::queue<Tree<T> *> q;
        q.push(b);

        while (!q.empty())
        {
            Tree<T> *current = q.front();
            q.pop();

            if (current != nullptr && !current->empty())
            {
                std::cout << current->value() << " ";

                Tree<T> *l = current->left();
                Tree<T> *r = current->right();
                if (l && !l->empty())
                    q.push(l);
                if (r && !r->empty())
                    q.push(r);
            }
        }
    }

    static int *searchTreeSort(int *zahlen, int size)
    {
        SearchTree<int> tree;

        // Alle Zahlen in den Suchbaum einfügen
        for (int i = 0; i < size; ++i)
        {
            tree.insert(zahlen[i]);
        }

        //Stack füllen
        LinkedStack<int> stack;
        tree2SortedStack(&tree, stack); //rekursive Füllung

        // Stack zurück in Array schreiben
        int* result = new int[size];
        for (int i = 0; i < size; ++i) {
            result[i] = stack.peek();
            stack.pop();
        }

        return result;
    }

    // Baum als Level-Ausgabe (grafisch)
    static void printTree(Tree<T> *b)
    {
        int resthoehe = treeHeight(b);
        for (int i = 0; i < resthoehe; i++)
        {
            printLevel(b, i, spaces(resthoehe - i));
            std::cout << std::endl
                      << std::endl;
        }
    }

    static void printLevel(Tree<T> *b, int level, int space)
    {
        if (level == 0)
        {
            for (int i = 0; i < space; ++i)
                std::cout << " ";
            if (b != nullptr)
                std::cout << b->value();
            else
                std::cout << " ";
            for (int i = 0; i <= space; ++i)
                std::cout << " ";
        }
        else
        {
            printLevel((b && !b->left()->empty()) ? b->left() : nullptr, level - 1, space);
            printLevel((b && !b->right()->empty()) ? b->right() : nullptr, level - 1, space);
        }
    }

    static int spaces(int level)
    {
        if (level == 1)
            return 0;
        return 2 * spaces(level - 1) + 1;
    }
};



//Shuffled Search Tree Funktion zur Erstellung zufälliger Suchbäume


SearchTree<int> generateShuffledSearchTree(int knots)
{
    SearchTree<int> randomTree;
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(1, knots);

    for (int i = 0; i < knots; ++i)
    {
        int treevariable = distribution(generator);
        randomTree.insert(treevariable);
    }

    return randomTree;
}

// Hier beginnt Tree Tools Test, bzw die Main Datei

/******************************  TreeToolsTest.cpp  **************************/

int main()
{
    // Erzeuge einen Test-Baum:
    //        /
    //      /   \
    //     +     -
    //    / \   / \
    //   F  *  X   Y
    //     / \
    //    A   B

    // Blattknoten
    LinkedTree<char> *a = new LinkedTree<char>('A');
    LinkedTree<char> *b = new LinkedTree<char>('B');

    // Teilbaum * mit A und B
    LinkedTree<char> *m = new LinkedTree<char>(a, '*', b);

    // linkwe Teilbaum: + mit F und +
    LinkedTree<char> *f = new LinkedTree<char>('F');
    LinkedTree<char> *p = new LinkedTree<char>(f, '+', m);

    // rechter Teilbaum: - mit X und Y
    LinkedTree<char> *x = new LinkedTree<char>('X');
    LinkedTree<char> *y = new LinkedTree<char>('Y');
    LinkedTree<char> *n = new LinkedTree<char>(x, '-', y);

    // Wurzelbaum mit /
    LinkedTree<char> *d = new LinkedTree<char>(p, '/', n);

    std::cout << "Baumstruktur (Inorder mit Klammern):" << std::endl;
    TreeTools<char>::printTreeInorderWithParenthesis(d);
    std::cout << std::endl
              << std::endl;

    std::cout << "Baumstruktur (Levelorder):" << std::endl;
    TreeTools<char>::printTreeLevelorder(d);
    std::cout << std::endl;

    std::cout << "Baumhöhe: " << TreeTools<char>::treeHeight(d) << std::endl;
    std::cout << "Anzahl der Knoten: " << TreeTools<char>::anzahlKnoten(d) << std::endl;

    int arr[] = {5, 3, 9, 1, 7};
    int size = sizeof(arr) / sizeof(int);
    int* sorted = TreeTools<int>::searchTreeSort(arr, size);

    std::cout << "Sortiertes Array: ";
    for (int i = 0; i < size; ++i) {
    std::cout << sorted[i] << " ";
    }
    std::cout << std::endl;

    delete[] sorted;


    //Aufgabe b)
    int knots, runs, totalHeight = 0;
    double averageHeight, logarithmus;
    std::cout << "Aufgabe b)\n" << std::endl;
    std::cout << "Anzahl an Knoten: ";
    std::cin >> knots;
    std::cout << "\nAnzahl der Durchläufe: ";
    std::cin >> runs;

for (int i = 0; i < runs; i++)
{
    SearchTree<int> randomTree = generateShuffledSearchTree(knots);
    int height = TreeTools<int>::treeHeight(&randomTree);
    std::cout << "Höhe Suchbaum " << i+1 << ": " << height << std::endl;
    totalHeight += height;
}
    averageHeight = totalHeight/runs;
    logarithmus = std::log(averageHeight) / std::log(2);
    std::cout << "Durchschnittliche Höhe: " << averageHeight << " (entspricht " << std::setprecision(2) << logarithmus << " * log₂ n)" << std::endl;

    return 0;
}
