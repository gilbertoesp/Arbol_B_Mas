#ifndef COLA_H
#define COLA_H
#include "Nodo.h"

struct Caja {
    Nodo* nodo;
    Caja* siguiente;
};

class Cola {
    private:
        Caja *primero, *ultimo;
        int cuantos;

    public:
        Cola();
        ~Cola();
        void nuevo();
        void limpiar();
        void agregar(Nodo*);
        Nodo* sacar();
        void pintar();
        bool estaVacia(){ return cuantos == 0; }
};

#endif
