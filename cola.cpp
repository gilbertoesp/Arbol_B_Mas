#include "Cola.h"

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
using namespace std;
Cola::Cola()
{
    primero=NULL;
    ultimo=NULL;
    cuantos=0;
}

Cola::~Cola(){
    caja*p;

    while(primero){
        p=primero;
        primero=p->siguiente;
        free(p);
    }
    ultimo=NULL;
    cuantos=0;
}

void Cola::limpiar(){
    caja*p;

    while(primero){
        p=primero;
        primero=p->siguiente;
        free(p);
    }
    ultimo=NULL;
    cuantos=0;
    free(this);
}

void Cola::nuevo(){
    primero=NULL;
    ultimo=NULL;
    cuantos=0;
}

void Cola::agregar(Nodo* n){
    caja*p;
    p=(caja*)malloc(sizeof(caja));
    p->nodo=n;

    if(primero==NULL){
        p->siguiente = NULL;
        primero=p;
        ultimo=p;
    }else{
        p->siguiente=NULL;
        ultimo->siguiente=p;
        ultimo=p;
        }
    cuantos++;
}

Nodo* Cola::sacar(){
    caja*p;
    Nodo* nodo;

    if(primero==NULL){
      return NULL;
    }else{
        p=primero;
        primero = p->siguiente;
        nodo = p->nodo;
        free(p);
        cuantos--;

        if (cuantos==0){
            ultimo = NULL;
        }
    }
    return nodo;
}




