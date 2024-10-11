#include "node.h"
#include <conio.h>


class LinkedList
{
private:
    int size; 
    Node *head;
public:
    LinkedList();
    ~LinkedList();
    Node* getHead();
    void addFileBySrc(string src);
    void addFile(string fileName);
    void insertFirst(string data);
    void print();
    void realizarBusqueda();
    void exportToTxt(string fileName);

    // Ordenamiento -->
    void sortByIp();
    Node* mergeSort(Node* head);
    Node* split(Node* head);
    Node* mergeLists(Node* first, Node* second);
};

LinkedList::LinkedList()
{
    this->head = nullptr;
    this->size = 0;
}

LinkedList::~LinkedList()
{
}

Node* LinkedList::getHead()
{
    return this->head;
}

void LinkedList::addFile(string fileName)
{
    ifstream file("./"+fileName+".txt");  // Abre el archivo de texto
    
    cout << "documento abierto con exito" << endl;

    string line;

    // Procesa cada línea del archivo
    while (getline(file, line))
    {
        insertFirst(line);
    }
    cout << "documento cargado con exito" << endl;
    system("cls");

    file.close();
}

void LinkedList::insertFirst(string data)
{
    Node* newNode = new Node(this->head, data);
    this->head = newNode;
    this->size++;
}

void LinkedList::print()
{
    Node* temp = this->head; // Comenzar desde la cabeza
    while (temp) {
        temp->print();
        temp = temp->next;
    }
}

// Implementacion faltante
void LinkedList::realizarBusqueda()
{
    bool continuar = true;
    int contador = 0;
    while (continuar) {
        contador++;


        // Logica del metodo


        cout << "Deseas hacer otra busqueda? y/n" << endl;
        char opt = _getch();
        continuar = (opt == 'y');
    }
}

void LinkedList::sortByIp()
{
    this->head = this->mergeSort(this->head);
}

void LinkedList::exportToTxt(string fileName)
{
    ofstream file("./"+fileName+".txt");
    Node* temp = this->head;
    while (temp) {
        
        file << temp->writeLine() << endl;
        
        temp = temp->next;
    }
    file.close();
}

Node* LinkedList::mergeSort(Node* head) {

    if (head == nullptr || head->next == nullptr)
        return head;

    Node* second = split(head);

    head = mergeSort(head);
    second = mergeSort(second);

    return mergeLists(head, second);
}

Node* LinkedList::split(Node* head) {
    Node *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* temp = slow->next;
    slow->next = nullptr;
    return temp;
}

Node* LinkedList::mergeLists(Node* first, Node* second) {
    if (!first) return second;
    if (!second) return first;

    if (first->ipComparableValue < second->ipComparableValue) {
        first->next = mergeLists(first->next, second);
        return first;
    } else {
        second->next = mergeLists(first, second->next);
        return second;
    }
}