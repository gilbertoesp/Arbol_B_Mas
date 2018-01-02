#ifndef COLA_H
#define COLA_H

    #include "Nodo.h"

    struct caja{
        Nodo* nodo;
        caja* siguiente;
    };

    class Cola
    {
        caja* primero;
        caja* ultimo;
        int cuantos;

        public:
            Cola();
            ~Cola();
            void nuevo();
            void limpiar();
            void agregar(Nodo*);
            Nodo* sacar();
            void pintar();
            bool estaVacia(){return cuantos==0;}

};

#endif // COLA_H

