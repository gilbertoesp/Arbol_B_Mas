#ifndef NODO_H
#define NODO_H

    struct Nodo;
    enum posicion {Vacio,Principio,EnMedio,Final};
    enum boolean { NO = false, SI = true };

    /*
        Esta estructura contiene la informacion de cada elemento de la lista.
    */
    struct CajaValor{
        int valor;
        CajaValor *siguiente;
    };


    /*
        Esta clase forma una lista ordenada con elementos caja.
    */
    class ListaValor{
        CajaValor *principio, *anterior;
        posicion donde;
        boolean encontrado;
        int cuantosVal;

        public:
            ListaValor();
            ~ListaValor();

            void nuevo();
            void limpiar();

            void buscar(int a);
            int agregar(int a);
            int borrar(int a);
            int sacar(void);
            void pintar(void);
            int CuantosVal();
            CajaValor* dondePrincipio();
    };



    /*
        Esta estructura contiene la informacion de cada elemento de la lista.
    */
    struct CajaDireccion{
        Nodo *direccion;
        CajaDireccion *siguiente;
    };


    /*
        Esta clase forma una lista ordenada con elementos caja.
    */
    class ListaDireccion{
        CajaDireccion *principio, *anterior;
        posicion donde;
        boolean encontrado;
        int cuantosDir;

        public:
            ListaDireccion();
            ~ListaDireccion();

            void nuevo();
            void limpiar();

            void buscar(Nodo *p);
            int agregar(Nodo *p);
            int borrar(Nodo *p);
            void buscarBorrar(Nodo *p);
            Nodo* sacar(void);
            int CuantosDir();
            CajaDireccion* dondePrincipio();
    };


    struct Nodo{
            ListaValor llaves;       //Un arreglo que contiene valores enteros.
            ListaDireccion direccion;  //Un arreglo de direcciones que contiene a sus posibles hijos.
            bool esHoja;        //Indica si el nodo es una hoja del arbol.
            Nodo* padre;        //Indica la direccion del padre del nodo.
    };

#endif


