//Actividad Integradora 2.3 
//Diego Israel Dominguez Najera A01782831
//Andrea Marlene Ramos Tiscareño A01646342
//Samuel Rodriguez Torres A01637408
//9 de Octubre del 2025

#pragma once

#include <vector>
#include <string> 
using namespace std;

struct nodo{
    vector<int> ip;
    nodo* next;
    nodo(vector<int> ip, nodo* next){
        this -> ip = ip;
        this -> next = next;
    }
    nodo(vector<int> ip): nodo(ip, nullptr) {}
};

class LinkedList{
    public:
        int size = 0;
        nodo* head;
        nodo* tail;
        LinkedList();
        ~LinkedList();
        void insertFirst(vector<int> data);
        void insertLast(vector<int> data);
};

class bitacora{
    private:
        int contadorBusquedas = 1;
        LinkedList lista_ips;
        LinkedList lista_ordenada;
        vector<string> lineas_iniciales;
    public:
        bitacora(vector<string> l);
        bool comparar(nodo* a, nodo* b);
        void crear_archivo(const LinkedList& lista, int option);
        void ordenar();
        bool ipMenoroIgual(vector<int> a, vector<int> b);
        bool ipMayoroIgual(vector<int> a, vector<int> b);
        void buscar(vector<int> ip_busqueda_inicio, vector<int> ip_busqueda_fin);
        LinkedList merge(nodo* izq, nodo* der);
        LinkedList mergeSort(const LinkedList& lista);
};