#include "Cola.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>

using namespace std;

Cola::Cola() {
    primero = NULL;
    ultimo = NULL;
    cuantos = 0;
}

Cola::~Cola() {
    Caja *p;

    while(primero) {
        p = primero;
        primero = p->siguiente;
        delete(p);
    }
    ultimo = NULL;
    cuantos = 0;
}

void Cola::limpiar() {
    Caja *p;

    while(primero) {
        p = primero;
        primero = p->siguiente;
        delete(p);
    }
    ultimo = NULL;
    cuantos = 0;
    delete(this);
}

void Cola::nuevo() {
    primero = NULL;
    ultimo = NULL;
    cuantos = 0;
}

void Cola::agregar(Nodo* n) {
    Caja *p;
    p = new Caja;
    p->nodo = n;

    if(primero == NULL) {
        p->siguiente  =  NULL;
        primero = p;
        ultimo = p;
    }else {
        p->siguiente = NULL;
        ultimo->siguiente = p;
        ultimo = p;
    }
    cuantos++;
}

Nodo* Cola::sacar() {
    Caja *p;
    Nodo* nodo;

    if(primero == NULL) {
      return NULL;
    }else {
        p = primero;
        primero = p->siguiente;
        nodo = p->nodo;
        delete(p);
        cuantos--;

        if (cuantos == 0) {
            ultimo = NULL;
        }
    }
    return nodo;
}
