#ifndef NODO_H
#define NODO_H

    struct Nodo;
    enum posicion {
      Vacio,
      Principio,
      EnMedio,
      Final
    };
    enum boolean { NO = false, SI = true };
///////////////////////////////Caja de datos////////////////////////////////////
    /*
        Estructura que contiene la informacion de cada elemento de la lista.
    */
    struct cajaVal{
        int valor;
        cajaVal *siguiente;
    };
    //////////////////////////////lista ordenada////////////////////////////////////
    /*
        Clase que forma una lista ordenada con elementos caja.
    */
    class listaVal{
        cajaVal *principio, *anterior;
        posicion donde;
        boolean encontrado;
        int cuantos_Val;

        public:
            listaVal();
            ~listaVal();

            void nuevo();
            void limpiar();

            void buscar(int a);
            int agregar(int a);
            int borrar(int a);
            int sacar(void);
            void pintar(void);
            int cuantosVal();
            cajaVal* dondePrincipio();
    };


    ///////////////////////////////Caja de datos////////////////////////////////////
    /*
        Estructura que contiene la informacion de cada elemento de la lista.
    */
    struct cajaDir{
        Nodo *dir;
        cajaDir *siguiente;
    };
    //////////////////////////////lista ordenada////////////////////////////////////
    /*
        Clase que forma una lista ordenada con elementos caja.
    */
    class listaDir{
        cajaDir *principio, *anterior;
        posicion donde;
        boolean encontrado;
        int cuantos_Dir;

        public:
            listaDir();
            ~listaDir();

            void nuevo();
            void limpiar();

            void buscar(Nodo *p);
            int agregar(Nodo *p);
            int borrar(Nodo *p);
            void buscarBorrar(Nodo *p);
            Nodo* sacar(void);
            int cuantosDir();
            cajaDir* dondePrincipio();
    };
    ////////////////////////

    struct Nodo{
            listaVal llaves;       //Un arreglo que contiene valores enteros.
            listaDir direccion;  //Un arreglo de direcciones que contiene a sus posibles hijos.
            bool esHoja;        //Indica si el nodo es una hoja del arbol.
            Nodo* padre;        //Indica la direccion del padre del nodo.

    };

#endif


