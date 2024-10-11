#include <iostream>   // Librería para entrada y salida estándar
#include <map>        // Librería para el uso de mapas (diccionarios)
#include <iomanip>    // Librería para manipulación de entrada/salida (get_time)
#include <sstream>    // Librería para el manejo de cadenas de caracteres y flujos
#include <ctime>      // Librería para manejo de tiempo y fechas
#include <fstream>

using namespace std;  // Para evitar escribir std:: antes de cada uso de objetos de la biblioteca estándar

struct Node{
    Node* next;
    string 
        ip,        // Almacena la dirección IP
        razon,     // Razón del reporte
        dia,       // Día en formato de texto (ej: "1", "15")
        mes,       // Mes en formato de texto (ej: "Jan", "Feb")
        hora     // Hora en formato "HH:MM:SS"
    ;
    long long ipComparableValue; // Dato tipo long long calculado con base a la ip, se usa para comparar ip´s y sus puertos

    // Constructor con sigueinte nodo
    Node(Node* next, string data)
    {
        this->next =next;
        loadDatta(data);
        ipToComparableValue();
    }
    
    // Constructor sin sigueinte nodo
    Node(string data): Node(nullptr, data)
    {
        loadDatta(data);
        ipToComparableValue();
    }
    
    // Metodo que transforma linea de dato a atributos
    void loadDatta(string linea)
    {
        int spaceCount = 0;
            string elemento = "";
            string 
                mes, 
                hora, 
                ip, 
                razon, 
                dia;

            // Procesa los elementos de la línea separados por espacios
        for (size_t i = 0; i < linea.length(); i++) {
            if (spaceCount < 4){
                if (!(linea[i] == ' ')){
                    elemento += linea[i];  // Acumula caracteres hasta encontrar un espacio
                } else {
                    switch (spaceCount){  // Asigna el valor acumulado a la variable correspondiente
                    case 0:
                        this->mes = elemento;
                        elemento = "";
                        break;
                    case 1:
                        this->dia = elemento;
                        elemento = "";
                        break;
                    case 2:
                        this->hora = elemento;
                        elemento = "";
                        break;
                    case 3:
                        this->ip = elemento;
                        elemento = "";
                        break;
                    }
                    spaceCount++;
                }
            } else {
                elemento += linea[i];  // Acumula el resto de la línea como la razón
            }
        }
        this->razon = elemento;
    }
    
    // Metodo para imprimir  linea de datoa en orden 
    void print()
    {
        cout << this->mes << " " << this->dia << " " << this->hora << " "<< this->ip << " " << this->razon << endl;
    }

    // Función para convertir la IP a un valor comparable tipo long
    void ipToComparableValue(){
        int octet1, octet2, octet3, octet4, port = 0;
        char dummy; // Para ignorar los caracteres '.' y ':'
        
        stringstream ss(this->ip);

        // Extraer los octetos y el puerto (si existe)
        ss >> octet1 >> dummy >> octet2 >> dummy >> octet3 >> dummy >> octet4;

        if (ss >> dummy >> port) {
            // Se leyó un puerto, mantener el valor leído
        }

        // Convertir la IP a un valor de tipo long (usando cada octeto como parte del desplazamiento)
        long long ipValue = (static_cast<long long>(octet1) << 24) | (octet2 << 16) | (octet3 << 8) | octet4;

        // Añadir el puerto (si existe) para mantener la diferencia
        // Considerar el puerto en los bits menos significativos si es necesario (por ejemplo, max 65535)
        this->ipComparableValue = (ipValue << 16) | port;
    }

};