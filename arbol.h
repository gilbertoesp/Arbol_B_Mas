#ifndef ARBOL_H
#define ARBOL_H

#include <iostream>
#include "cola.h"
using namespace std;

class Arbol{
    private:
        Nodo* raiz;         //Indica el nodo de la raiz del arbol.
        int orden;          //Indica la cantidad de valores maximo de los nodos hoja.
        bool encontrado;    //Indica si se encontro un valor en el arbol.
        Nodo* donde;        //Indica donde se encontro el valor que se busco.

    public:
        Arbol(int a);
        ~Arbol();

        //Pemite buscar un valor en el arbol o la ubicacion donde va a agregarse.
        int buscar(int a);

        //Este metodo permite agregar un valor al arbol y ajustarlo en caso de ser necesario.
        void agregar(int a);
        //Este metodo auxiliar del agregar permite dividir los nodos hojas en caso de llenarse el nodo.
        void dividirHojas(int a, Nodo *p);
        //Este metodo auxiliar del agregar permite dividir los nodos intermedios para ajustar el arbol.
        void dividirPadres(Nodo *p);

        //Este metodo permite borrar un valor al arbol y ajustarlo en caso de ser necesario.
        int borrar(int a);
        //Este metodo auxiliar del borrar permite ajustar los nodos hojas en caso de tener menos valores de los minimos permitidos.
        void modificarHojas(int a, Nodo *p);
        //Este metodo auxiliar del borrar permite ajustar los nodos intermedios para ajustar el arbol cuando el nodo tenga menos direcciones de las permitidas.
        void modificarPadres(Nodo *p);

        //Este metodo permite leer un archivo con los valores que se agregaran al arbol.
        void lecturaLlaves(string mensaje);
        //Este metodo permite leer un archivo con los valores que se borraran del arbol.
        void borradoLlaves(string mensaje);

        //Este metodo permite pintar los nodos del arbol con todos los valores que contenga.
        void pintar();

};

#endif

