//Actividad Integradora 2.3
//Diego Israel Dominguez Najera A01782831
//Andrea Marlene Ramos Tiscareño A01646342
//Samuel Rodriguez Torres A01637408
//9 de Octubre del 2025

#include "bitacora.h"
#include <iostream>
#include <fstream>
using namespace std;

//Métodos de la LinkedList
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

void LinkedList::insertFirst(vector<int> data) {
    nodo* nuevo = new nodo(data, this -> head);
    if (this -> size == 0){
        this -> tail = nuevo;
    }
    this -> head = nuevo;
    this -> size++;
}

void LinkedList::insertLast(vector<int> data) {
    nodo* nuevo = new nodo(data, nullptr);
    if (this -> size == 0){
        this -> head = nuevo;
        this -> tail = nuevo;
    }
    else{
        this -> tail -> next = nuevo;
        this -> tail = nuevo;
    }
    this -> size++;
}

// Métodos de la Bitacora
bitacora::bitacora(vector<string> l) {
    lineas_iniciales = l;
    for (int c = 0; c < l.size(); ++c) {
        string linea = l[c];
        string ip_string = linea.substr(15, linea.find(" ", 16) - 16); //Justificar
        vector<int> ip_vector;
        string temp;

        for (char ch : ip_string) {
            if (ch == '.' || ch == ':') {
                ip_vector.push_back(stoi(temp)); // Stoi: String to int
                temp.clear(); //Importante justificar
            } else {
                temp += ch; //Concatenar el caracter al string temporal
            }
        }

        if (!temp.empty()) {
            ip_vector.push_back(stoi(temp)); // Agregar el último segmento
        }

        ip_vector.push_back(c);
        if (c == 0) {
            lista_ips.insertFirst(ip_vector);
        }
        else{
            lista_ips.insertLast(ip_vector);
        }
    }
}

void bitacora::crear_archivo(LinkedList lista, int option) {
    string nombre_archivo;
    if (option == 1) {
        nombre_archivo = "bitacoraOrdenadaa1.3-eq6.txt";
    }
    else if (option == 2) {
        nombre_archivo = "salida"+to_string(contadorBusquedas)+"-eq6.txt";
    }

    ofstream archivo(nombre_archivo);
    if (archivo.is_open()) {
        nodo* current = lista.head;
        while (current != nullptr) {
            vector<int> ip = current -> ip;
            archivo << lineas_iniciales[ip[5]] << endl;
            current = current -> next;
        }
        archivo.close();
    }
    else {
        cout << "No se pudo crear el archivo." << endl;
    }
}

bool bitacora::comparar(nodo* a, nodo* b) {
    vector<int> ip_a = a -> ip; 
    vector<int> ip_b = b -> ip;
    
    if (ip_a[0] != ip_b[0]) {
        return ip_a[0] < ip_b[0];
    }
    else if (ip_a[1] != ip_b[1]) {
        return ip_a[1] < ip_b[1];
    }
    else if (ip_a[2] != ip_b[2]) {
        return ip_a[2] < ip_b[2];
    }
    else if (ip_a[3] != ip_b[3]) {
        return ip_a[3] < ip_b[3];
    }
    else if (ip_a[4] != ip_b[4]) {
        return ip_a[4] < ip_b[4];
    }
    else{
        return false;
    }
}
 
LinkedList bitacora::merge(nodo* izq, nodo* der) {
    LinkedList resultado;
    nodo* tail = nullptr;

    while (izq != nullptr && der != nullptr) {
        nodo* temp = nullptr;
        if (comparar(izq, der)) {
            temp = new nodo(izq->ip);
            izq = izq->next;
        } 
        else {
            temp = new nodo(der->ip);
            der = der->next;
        }

        if (resultado.head == nullptr) {
            resultado.head = tail = temp;
        } 
        else {
            tail->next = temp;
            tail = tail->next;
        }
        resultado.size++;
    }

    while (izq != nullptr) {
        nodo* temp = new nodo(izq->ip);
        if (resultado.head == nullptr) {
            resultado.head = tail = temp;
        } 
        else {
            tail->next = temp;
            tail = tail->next;
        }
        izq = izq->next;
        resultado.size++;
    }

    while (der != nullptr) {
        nodo* temp = new nodo(der->ip);
        if (resultado.head == nullptr) {
            resultado.head = tail = temp;
        } 
        else {
            tail->next = temp;
            tail = tail->next;
        }
        der = der->next;
        resultado.size++;
    }

    resultado.tail = tail;
    return resultado;
}

LinkedList bitacora::mergeSort(const LinkedList &lista) {
    if (lista.size <= 1) {
        return lista;
    }

    int mitad = lista.size / 2;
    nodo* temp = lista.head;
    for (int i = 1; i < mitad; i++) {
        temp = temp->next;
    }

    nodo* mid = temp->next;
    temp->next = nullptr;

    LinkedList izq;
    izq.head = lista.head;
    izq.size = mitad;

    LinkedList der;
    der.head = mid;
    der.size = lista.size - mitad;

    LinkedList izq_ordenada = mergeSort(izq);
    LinkedList der_ordenada = mergeSort(der);

    return merge(izq_ordenada.head, der_ordenada.head);
}

void bitacora::ordenar() {
    lista_ordenada = mergeSort(lista_ips);
    crear_archivo(lista_ordenada, 1);
}

void bitacora::buscar(vector<int> ip_busqueda_inicio, vector<int> ip_busqueda_fin) {
    LinkedList resultados;
    nodo* current = lista_ordenada.head;

    while (current != nullptr) {
        vector<int> ip = current -> ip;
        if (ip[0] > ip_busqueda_inicio[0] && ip[1] > ip_busqueda_inicio[1] && ip[2] > ip_busqueda_inicio[2] && ip[3] > ip_busqueda_inicio[3] && ip[4] >= ip_busqueda_inicio[4] &&
            ip[0] < ip_busqueda_fin[0] && ip[1] < ip_busqueda_fin[1] && ip[2] < ip_busqueda_fin[2] && ip[3] < ip_busqueda_fin[3] && ip[4] <= ip_busqueda_fin[4]) {
            if (resultados.size == 0) {
                resultados.insertFirst(ip);
            }
            else{
                resultados.insertLast(ip);
            }
        }
        current = current -> next;
    }
   crear_archivo(resultados, 2);
   contadorBusquedas++;
}
  
