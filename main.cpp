#include <iostream>

#include "Element.hpp"
#include "Knoten.hpp"
#include "LinkedQueue.hpp"
#include "LinkedStack.hpp"
#include "LinkedTree.hpp"
#include "Menge.hpp"
#include "Queue.hpp"
#include "SearchTree.hpp"
#include "Stack.hpp"
#include "Tree.hpp"
#include "TreeTools.hpp"
#include "TreeToolsTest.hpp"

int main(){

    Element e;
    std::cout << "Element erstellt!" << std::endl;

    int wert = 42; // Beispielwert
    Knoten k(&wert);
    std::cout << "Knoten erstellt mit Wert: " << *(int*)k.inhalt << std::endl;

    LinkedQueue queue;
    int a = 42, b = 17;

    queue.enq(&a);
    queue.enq(&b);

    std::cout << "Erstes Element: " << *(int*)queue.front() << std::endl;
    queue.deq();
    std::cout << "Nach Deq erstes Element: " << *(int*)queue.front() << std::endl;

    LinkedStack stack;
    
    stack.push(&a);
    stack.push(&b);

    std::cout << "Oberstes Element: " << *(int*)stack.topElement() << std::endl;
    stack.pop();
    std::cout << "Nach Pop oberstes Element: " << *(int*)stack.topElement() << std::endl;

    int c = 99;

    LinkedTree leftTree(&a);
    LinkedTree rightTree(&b);
    LinkedTree tree(&leftTree, &c, &rightTree);

    std::cout << "Wurzelwert: " << *(int*)tree.value() << std::endl;
    std::cout << "Linker Teilbaum: " << *(int*)tree.left()->value() << std::endl;
    std::cout << "Rechter Teilbaum: " << *(int*)tree.right()->value() << std::endl;

    SearchTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    std::cout << "Suche nach 40: " << (tree.lookup(40) != nullptr ? "Gefunden" : "Nicht gefunden") << std::endl;
    tree.deleteValue(40);
    std::cout << "Suche nach 40 nach Löschung: " << (tree.lookup(40) != nullptr ? "Gefunden" : "Nicht gefunden") << std::endl;

        // Erzeuge einen Test-Baum
    LinkedTree* a = new LinkedTree('A');
    LinkedTree* b = new LinkedTree('B');
    LinkedTree* m = new LinkedTree(a, '*', b);
    LinkedTree* f = new LinkedTree('F');
    LinkedTree* p = new LinkedTree(f, '+', m);
    LinkedTree* x = new LinkedTree('X');
    LinkedTree* y = new LinkedTree('Y');
    LinkedTree* n = new LinkedTree(x, '-', y);
    LinkedTree* d = new LinkedTree(p, '/', n);

    // Test treeHeight() und anzahlKnoten()
    std::cout << "Baumhoehe laut Methode (sollte 4 sein): "
              << TreeTools::treeHeight(d) << std::endl;

    std::cout << "Anzahl Knoten laut Methode (sollte 9 sein): "
              << TreeTools::anzahlKnoten(d) << std::endl;

    std::cout << "Ausdruck mit Klammerung: ";
    TreeTools::printTreeInorderWithParenthesis(d);
    std::cout << std::endl;

    // Speicherfreigabe (für vollständige Implementierung erforderlich)
    delete a;
    delete b;
    delete m;
    delete f;
    delete p;
    delete x;
    delete y;
    delete n;
    delete d;

    return 0;
}