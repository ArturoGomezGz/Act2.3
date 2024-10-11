#include "node.h"
#include <conio.h>


class LinkedList
{
private:
    int size; 
    Node *head;

    Node* mergeSort(Node* head);
    Node* split(Node* head);
    Node* mergeLists(Node* first, Node* second);

    Node* binarySearch(string ip);
    long long ipToComparableValue(string ipStr);
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
    void sortByIp();
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

void LinkedList::addFileBySrc(string src)
{
    ifstream file(src);  // Abre el archivo de texto
    
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

void LinkedList::realizarBusqueda()
{
    bool continuar = true;
    int contador = 0;
    while (continuar) {
        contador++;

        string 
            ipIni = "",
            ipFin = ""
        ;

        cout << "ip inicial:" << endl;
        cin >> ipIni;
        cout << "ip final:" << endl;
        cin >> ipFin;

        if (ipToComparableValue(ipIni) < ipToComparableValue(ipFin))
        {
            ofstream file("./busquedas/salida"+ to_string(contador) +"-Eq2.txt");
            Node* actual = binarySearch(ipIni);
            while (actual->ipComparableValue <= ipToComparableValue(ipFin))
            {
                file << actual->writeLine() << endl;
                actual->print();
                actual = actual->next;
            }
            file.close();
        } else {
            cout << "la ip inicial debe ser menos a la ip final" << endl;
            contador--;
        }

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
    ofstream file("./outputs/"+fileName+".txt");
    Node* temp = this->head;
    while (temp) {
        
        file << temp->writeLine() << endl;
        
        temp = temp->next;
    }
    file.close();
}

Node* LinkedList::mergeSort(Node* head)
{

    if (head == nullptr || head->next == nullptr)
        return head;

    Node* second = split(head);

    head = mergeSort(head);
    second = mergeSort(second);

    return mergeLists(head, second);
}

Node* LinkedList::split(Node* head)
{
    Node *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* temp = slow->next;
    slow->next = nullptr;
    return temp;
}

Node* LinkedList::mergeLists(Node* first, Node* second)
{
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

long long LinkedList::ipToComparableValue(string ipStr)
{
    int octet1, octet2, octet3, octet4, port = 0;
    char dummy; // Para ignorar los caracteres '.' y ':'
    
    stringstream ss(ipStr);

    // Extraer los octetos y el puerto (si existe)
    ss >> octet1 >> dummy >> octet2 >> dummy >> octet3 >> dummy >> octet4;

    if (ss >> dummy >> port) {
        // Se leyó un puerto, mantener el valor leído
    }

    // Convertir la IP a un valor de tipo long (usando cada octeto como parte del desplazamiento)
    long long ipValue = (static_cast<long long>(octet1) << 24) | (octet2 << 16) | (octet3 << 8) | octet4;

    // Añadir el puerto (si existe) para mantener la diferencia
    // Considerar el puerto en los bits menos significativos si es necesario (por ejemplo, max 65535)
    return ((ipValue << 16) | port);
}

Node* LinkedList::binarySearch(string ipStr)
{
    long long targetValue = ipToComparableValue(ipStr);

    Node *start = head;
    Node *end = nullptr;

    Node *closestNext = nullptr;

    while (start != end) {
        Node *mid = start;
        Node *fast = start;

        while (fast != end && fast->next != end) {
            fast = fast->next->next;
            mid = mid->next;
        }

        if (mid->ipComparableValue == targetValue) {
            return mid;
        } else if (mid->ipComparableValue < targetValue) {
            start = mid->next;
        } else {
            closestNext = mid;
            end = mid;
        }
    }

    return closestNext;
}
