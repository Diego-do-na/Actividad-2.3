//Actividad Integradora 2.3 
//Diego Israel Dominguez Najera A01782831
//Andrea Marlene Ramos Tiscareño A01646342
//Samuel Rodriguez Torres A01637408
//9 de Octubre del 2025

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "bitacora.h"
#include "bitacora.cpp"
using namespace std;

//Mismo codigo que el metodo de la bitacora
vector<int> convertirIP(string ip_string) {
    vector<int> ip_vector;
    string temp = "";

    for (char ch : ip_string) {
        if (ch == '.' || ch == ':') {
            ip_vector.push_back(stoi(temp));
            temp.clear();
        } else {
            temp += ch;
        }
    }

    if (!temp.empty()) {
        ip_vector.push_back(stoi(temp));
    }

    return ip_vector;
}

int main() {
    vector<string> lineas;
    string linea;
    ifstream archivoEntrada("bitacora.txt");
    if (!archivoEntrada.is_open()) {
        cerr << "No se pudo abrir el archivo bitacora.txt" << endl;
        return 1;
    }
    while (getline(archivoEntrada, linea)) {
        lineas.push_back(linea);
    }
    archivoEntrada.close();

    bitacora b(lineas);
    b.ordenar();
    string ip_inicio_str;
    cout << "----------------------------------" <<endl;
    cout << "Bitacora." << endl;
    cout << "----------------------------------" <<endl;
    cout << "\nBusqueda por rango de IPs." << endl;

    bool continuar = true;
    while (continuar){
        cout << "Introduce la IP de inicio (en el formato ###.###.###.###): ";
        getline(cin, ip_inicio_str);
        string ip_fin_str;
        cout << "Introduce la IP de fin (en el formato ###.###.###.###): ";
        getline(cin, ip_fin_str);

        vector<int> ip_inicio = convertirIP(ip_inicio_str);
        vector<int> ip_fin = convertirIP(ip_fin_str);
        b.buscar(ip_inicio, ip_fin);  //Guardamos en el archivo de salida
        cout << "Tu busqueda ha sido completada de una forma exitosa. Los resultados han sido guardados en el archivo de salida" << endl;
        char respuesta;
        cout << "¿Deseas realizar otra busqueda? (s/n): ";
        cin >> respuesta;
        if (respuesta != 's' || respuesta != 'n'){
            cout << "Respuesta no valida. Saliendo del programa." << endl;
            break;
        }
        else if(respuesta == 'n'){
            continuar = false;
            cout << "Saliendo del programa." << endl;
        }
    }
    return 0;
}
