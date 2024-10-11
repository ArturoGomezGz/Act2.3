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
    void ordenarPorId();
    void exportToTxt(string fileName);
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

// Implementacion faltante
void LinkedList::ordenarPorId()
{
    // Ordenar elemnetos usando ipComparableValue

    Node* temp = this->head;
    while (temp) {
        

        // Logica aqui puto

        temp = temp->next;
    }
}

// Implementacion faltante
void LinkedList::exportToTxt(string fileName)
{
    // Recorrer lista y escribir en documento

    Node* temp = this->head;
    while (temp) {
        

        // Logica aqui puto

        temp = temp->next;
    }
}
