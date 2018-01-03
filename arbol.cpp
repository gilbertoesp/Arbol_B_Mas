#include "arbol.h"
#include "cola.h"

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
using namespace std;

/////////////////////////////////////////////////////Constructor/////////////////////////////////////////////////////
Arbol::Arbol(int a)
{
    orden=a;
    raiz = NULL;
    encontrado=false;
}
/////////////////////////////////////////////////////Destructor/////////////////////////////////////////////////////
Arbol::~Arbol()
{
    Nodo *p;
    int minimo;
    while(raiz!=NULL){//Busca el mayor valor en el arbol y lo borra del arbol mientras exista algo en el arbol
        p=raiz;
        while(p->esHoja==false){
            p=p->direccion.dondePrincipio()->direccion;
        }
        minimo=p->llaves.dondePrincipio()->valor;
        borrar(minimo);
    }
    raiz=NULL;
    orden=0;
    encontrado=false;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Busca la ubicacion para agregar el nuevo valor, si esta repetido no se agrega.

    int a: el valor que se buscara en el arbol.
*/
int Arbol::buscar(int a){
    Nodo *p=raiz;
    CajaValor *val;
    CajaDireccion *q;

    int n=0;
    while(true){//Busca la hoja del valor
        if(p->esHoja==true){//Busca si esta agregado el elemento en esa hoja

            val=p->llaves.dondePrincipio();

            while(val!=NULL){
                if(val->valor==a){
                    encontrado=true;
                    donde=p;
                    return 0;
                }
                val=val->siguiente;

            }

            encontrado = false;
            donde=p;
            return 1;

        }else{//Busca en que direccion del nodo del arbol debe bajar

            n=0;
            val=p->llaves.dondePrincipio();
            q=p->direccion.dondePrincipio();

            while(q!=NULL && val!=NULL){
                    if(a>=val->valor){
                        n++;

                        val=val->siguiente;

                        q=q->siguiente;
                    }else{
                        val=NULL;
                    }

            }
            p=q->direccion;
        }

    }


}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Permite agregar un valor al arbol y ajustar el arbol en caso de ser necesario.

    int a: el valor que se desea agregar al arbol.
*/
void Arbol::agregar(int a){
    Nodo *p;
    if(raiz==NULL){//Si el arbol no contiene elementos

        p= new Nodo;
        p->llaves.nuevo();
        p->direccion.nuevo();
        p->esHoja = true;
        p->padre=NULL;

        p->llaves.agregar(a);
        raiz = p;
        return;

    }else{//Si el arbol contiene elementos y se debe buscar donde se agregara el valor

        buscar(a);

        if(encontrado==true){
            return;
        }

        p=donde;

        if(p->llaves.CuantosVal()<orden-1){//Si despues de agregar no se debe modificar los nodos del arbol
            p->llaves.agregar(a);
        }else{//Si al agregar el valor se debera reajustar el arbol
            dividirHojas(a, p);
        }
        return;

    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Permite dividir las hojas del arbol y en caso de ser necesarios reajustar los nodos padres del arbol.

    int a: el valor que se desea agregar al arbol.
    Nodo *p: la direccion del nodo donde se agregara el valor.
*/
void Arbol::dividirHojas(int a, Nodo *p){

    p->llaves.agregar(a);

    int medio = orden/2, val;
    if(p==raiz){//Si la raiz es una hoja y debe dividirse por estar lleno el nodo

        //Crear padre y hermano derecho
        Nodo* padre = new Nodo;
        padre->llaves.nuevo();
        padre->direccion.nuevo();
        padre->esHoja = false;
        padre->padre = NULL;

        Nodo* hijo2 = new Nodo;
        hijo2->llaves.nuevo();
        hijo2->direccion.nuevo();
        hijo2->esHoja = true;
        hijo2->padre=padre;

        Nodo *hijo1 = p;


        //pasar valores del nodo al hermano derecho
        for(int i=medio; i<orden; i++){
            val=hijo1->llaves.sacar();

            hijo2->llaves.agregar(val);

        }

        //Agregar direcciones y valor al nodo padre
        padre->llaves.agregar(hijo2->llaves.dondePrincipio()->valor);

        padre->direccion.agregar(hijo1);

        padre->direccion.agregar(hijo2);

        //asignar nueva raiz
        raiz = padre;

        //asignar padres
        hijo1->padre=padre;

        //Asignar nuevas hojas
        hijo1->esHoja = true;


    }else if((p->padre)->llaves.CuantosVal()<orden-1 && p->esHoja==true){//Si el padre del nodo le cabe otra direccion

        //Crear hermano derecho
        Nodo* hijo2 = new Nodo;
        hijo2->llaves.nuevo();
        hijo2->direccion.nuevo();
        hijo2->esHoja=true;
        hijo2->padre=p->padre;

        //enviar valores al hermano derecho
        for(int i=medio; i<orden; i++){
            val=p->llaves.sacar();

            hijo2->llaves.agregar(val);

        }

        //Agrega una direccion y una llave al hermano derecho
        (p->padre)->llaves.agregar(hijo2->llaves.dondePrincipio()->valor);

        (p->padre)->direccion.agregar(hijo2);

    }else{//Si el padre se llenara y debera separarse en nodos intermedios

        //Crea nuevo hijo
        Nodo* hijo2 = new Nodo;
        hijo2->llaves.nuevo();
        hijo2->direccion.nuevo();
        hijo2->padre=p->padre;
        hijo2->esHoja=true;

        //Agrega los valores al hijo nuevo
        for(int i=medio; i<orden; i++){
            val=p->llaves.sacar();

            hijo2->llaves.agregar(val);

        }
        //Asigna las propiedades del hijo

        (p->padre)->llaves.agregar(hijo2->llaves.dondePrincipio()->valor);

        (p->padre)->direccion.agregar(hijo2);



        Cola Q;
        Nodo *next, *q;
        q=p->padre;
        int sigue=1;
        //Se agregan todos los nodos intermedios que se han llenado a una cola
        if(q->llaves.CuantosVal()==orden){
            Q.agregar(q);
            q=q->padre;
            if(q!=NULL){
                while(q!=raiz  && sigue==1){
                    if(q->llaves.CuantosVal()==(orden-1) ){
                        Q.agregar(q);
                        q=q->padre;
                    }else{
                        sigue=0;
                    }
                }
                if(sigue==1){
                    if(q->llaves.CuantosVal()==orden-1){
                        Q.agregar(q);
                    }
                }
            }
            //Todos los nodos de la cola se deberan separar
            while(!Q.estaVacia()){
                next= Q.sacar();
                dividirPadres(next);
            }

        }
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Permite dividir los nodos intermedios y reajustar el arbol.

    Nodo *p: la direccion del nodo que se debera ajustar en el arbol.
*/
void Arbol::dividirPadres(Nodo *p){

    int medio = orden/2;
    int valM, val;
    Nodo *direccion;


    Nodo* hijo2 = new Nodo;
    hijo2->llaves.nuevo();
    hijo2->direccion.nuevo();
    hijo2->esHoja=false;
    hijo2->padre=NULL;

    //Agregar valores hijo derecho
    for(int i=medio+1; i<orden; i++){

        val=p->llaves.sacar();

        hijo2->llaves.agregar(val);

    }
    //Sacar el valor central
    valM=p->llaves.sacar();

    //Agregar direcciones hijo derecho
    for(int i=medio+1; i<orden+1; i++){
        direccion=p->direccion.sacar();
        hijo2->direccion.agregar(direccion);
        //asigno nuevo padre
        direccion->padre=hijo2;
    }

    if(p!=raiz){
        if(p->esHoja==true){
            val=hijo2->llaves.dondePrincipio()->valor;
            (p->padre)->llaves.agregar(val);
            (p->padre)->direccion.agregar(hijo2);
            hijo2->padre=p->padre;
        }else{
            (p->padre)->llaves.agregar(valM);
            (p->padre)->direccion.agregar(hijo2);
            hijo2->padre=p->padre;
        }
    }else{
        Nodo* padre = new Nodo;
        padre->llaves.nuevo();
        padre->direccion.nuevo();
        padre->esHoja=false;
        padre->padre=NULL;

        padre->llaves.agregar(valM);
        padre->direccion.agregar(p);
        padre->direccion.agregar(hijo2);
        raiz = padre;
        p->padre=padre;
        hijo2->padre=padre;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Recibe un valor que debera ser borrado del arbol.

    int a:valor que se desea borrar.
*/

int Arbol::borrar(int a){
    Nodo *p;
    buscar(a);

    if(encontrado==false){//Si no se encuentra no se hace nada
        return 0;
    }
    p=donde;//La ubicacion donde se encontro el valor
    if(p==raiz){//Si solo se tiene la raiz
        if(p->llaves.CuantosVal()==1){//Si la raiz solo tiene un elemento se borra y se deja el arbol como al principio
            p->direccion.limpiar();
            p->llaves.limpiar();
            p->esHoja=false;
            p->padre=NULL;
            delete p;
            raiz=NULL;
            return 1;
        }else{//Si la raiz tiene mas de un elemento solo se borra el numero
            p->llaves.borrar(a);
            return 1;
        }

    }else{//Si el arbol tiene mas de un nodo

        if(p->llaves.CuantosVal()>(int)orden/2){//Si la hoja tiene mas llaves que las minimas requeridas
            if(a!=p->llaves.dondePrincipio()->valor || (p->padre)->direccion.dondePrincipio()->direccion==p){//Si no es el primer elemento del nodo o cuelga como primer hijo solo se saca la hoja
                p->llaves.borrar(a);
            }else{// En este caso se debe sacar el menor valor en el nodo en el nodo padre y agregar el que queda en primera posicion
                p->llaves.borrar(a);
                (p->padre)->llaves.borrar(a);
                (p->padre)->llaves.agregar(p->llaves.dondePrincipio()->valor);
            }
            return 1;

        }else{//Si el nodo tiene menos llaves de las requeridas y es necesario reorganizar el arbol
            modificarHojas(a, p);
        }
    }
    return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Modifica las hojas del arbol y ajusta el arbol de ser necesario.

    int a:valor que se desea borrar.
    Nodo *p la direccion del nodo donde se encuentra el valor.
*/
void Arbol::modificarHojas(int a, Nodo *p){
    Nodo *h_der, *h_izq, *padre, *aux;
    int indice, valor;
    CajaDireccion *q, *i;
    CajaValor *v;
    //Se saca el valor de la hoja
    p->llaves.borrar(a);

    padre=p->padre;
    indice=0;
    //Se busca en que indice del padre esta colgado esa hoja
    q=padre->direccion.dondePrincipio();
    while(q->direccion!=p){
        indice+=1;
        if(q->siguiente!=NULL){
            if(q->siguiente->direccion==p){
                i=q;
            }
        }
        q=q->siguiente;
    }

    if(indice==0){// Si cuelga en la posicion 0 del padre

        //Debe tener hermano derecho
        h_der=q->siguiente->direccion;

        if(h_der->llaves.CuantosVal()>(int)orden/2){   //CASO 1           //Se revisa si el hermano derecho puede prestar un valor
            //Se saca la primera llave del hermano derecho y se agrega al nodo actual
            valor=h_der->llaves.dondePrincipio()->valor;
            h_der->llaves.borrar(valor);
            p->llaves.agregar(valor);

            //Se cambia la llave en el padre que indica el primer elemento del hermano derecho(ya que se presto el primer valor del hermano derecho)
            padre->llaves.dondePrincipio()->valor=h_der->llaves.dondePrincipio()->valor;

        }else{      //CASO 2         //Si el hermano derecho no le puede prestar, se fucionan en el actual y se limpia el hermano derecho.
            //se saca la primera llave del padre ya que el nodo hermano derecho ya no existira
            padre->llaves.borrar(padre->llaves.dondePrincipio()->valor);

            //Se transfieren las llaves del hermano derecho al nodo actual, ya que al ser hoja no tiene direcciones
            while(h_der->llaves.CuantosVal()>0){
                valor=h_der->llaves.dondePrincipio()->valor;
                h_der->llaves.borrar(valor);
                p->llaves.agregar(valor);
            }
            //Se desconecta el hermano derecho del padre.
            padre->direccion.borrar(h_der);

            //Se libera memoria
            h_der->direccion.limpiar();
            h_der->llaves.limpiar();
            h_der->esHoja=false;
            h_der->padre=NULL;
            delete h_der;

        }

    }else if(indice<orden-1){//Si el nodo cuelga entre la llaves[1] y llaves[orden-1]

        //Debe tener hermano izquierdo
        h_izq=i->direccion;

        v=padre->llaves.dondePrincipio();
        for(int i=1; i<indice; i++){
            v=v->siguiente;
        }
        if(q->siguiente!=NULL){   //checar si tiene hermano derecho

            h_der=q->siguiente->direccion;

            if(h_der->llaves.CuantosVal()>(int)orden/2||h_izq->llaves.CuantosVal()>(int)orden/2){//Se revisa si alguno de sus hermanos le puede prestar una llave

                if(h_der->llaves.CuantosVal()>(int)orden/2){       //CASO 3    //Se revisa primero el hermano derecho(si los dos le pueden prestar se usara el hermano derecho)
                    //Se saca la primera llave del hermano derecho y se agrega al nodo actual
                    valor=h_der->llaves.dondePrincipio()->valor;
                    h_der->llaves.borrar(valor);
                    p->llaves.agregar(valor);

                    //Si se borro el primer elemento del nodo actual actualizar el indice en el padre

                    if(v->valor!=p->llaves.dondePrincipio()->valor){
                        v->valor=p->llaves.dondePrincipio()->valor;
                    }

                    //Se cambia la llave en el padre que indica el primer elemento del hermano derecho(ya que se presto el primer valor del hermano derecho)
                    (v->siguiente)->valor=h_der->llaves.dondePrincipio()->valor;

                }else{      //CASO 4     //Solo el hermano izquierdo es viable para prestarle una llave
                    //Se pide la ultima llave del hermano izquierdo para agregar al actual
                    valor=h_izq->llaves.sacar();
                    h_izq->llaves.borrar(valor);
                    p->llaves.agregar(valor);

                    //Se cambia la llave en el padre que indica el primer elemento del nodo actual(Ya que al pedir prestado al hermano izquierdo, la llave nueva sera la menor del nodo actual)
                    v->valor=valor;

                }
            }else{    //CASO 5      //Como no se puede pedir a los hermanos, las llaves del hermano derecho se unen al nodo actual
                //Se saca el indice de la primera llave del hermano derecho en el nodo padre
                valor=(v->siguiente)->valor;
                padre->llaves.borrar(valor);
                //Se saca la direccion del hermano derecho en el padre
                padre->direccion.borrar(h_der);

                //Se sacan las llaves del hermano derecho para agregarse al nodo actual
                while(h_der->llaves.CuantosVal()>0){
                    valor=h_der->llaves.dondePrincipio()->valor;
                    h_der->llaves.borrar(valor);
                    p->llaves.agregar(valor);
                }
                //Si se borro el primer elemento del nodo actual actualizar el indice en el padre
                if(v->valor!=p->llaves.dondePrincipio()->valor){
                        v->valor=p->llaves.dondePrincipio()->valor;
                }

                //Liberar memoria del hermano derecho
                h_der->direccion.limpiar();
                h_der->llaves.limpiar();
                h_der->esHoja=false;
                h_der->padre=NULL;
                delete h_der;

            }
        }else{//Solo tiene hermano izquierdo

            if(h_izq->llaves.CuantosVal()>(int)orden/2){       //CASO 6           //Pedir al hermano izquierdo en caso de poder
                //Se saca la ultima llave del hermano izquierdo y se agrega al actual nodo
                valor=h_izq->llaves.sacar();
                h_izq->llaves.borrar(valor);
                p->llaves.agregar(valor);

                //Se indica la nueva primera llave del nodo en el padre
                v->valor=p->llaves.dondePrincipio()->valor;

            }else{      //CASO 7        //mandar llaves al hijo izquierdo y limpiar nodo
                //Sacar indice y direccion del nodo actual en el padre
                //Solo tiene hermano izquierdo
                padre->llaves.sacar();
                padre->direccion.sacar();

                //Mandar llaves del nodo actual al hermano izquierdo

                while(p->llaves.CuantosVal()>0){
                    valor=p->llaves.dondePrincipio()->valor;
                    p->llaves.borrar(valor);
                    h_izq->llaves.agregar(valor);
                }
                //Liberar memoria del nodo actual
                p->direccion.limpiar();
                p->llaves.limpiar();
                p->esHoja=false;
                p->padre=NULL;
                delete p;

            }
        }
    }else{//Es la ultima direccion del nodo (Solo tiene hermano izquierdo)

        h_izq=i->direccion;

        v=padre->llaves.dondePrincipio();
        for(int i=1; i<indice; i++){
            v=v->siguiente;
        }

        if(h_izq->llaves.CuantosVal()>(int)orden/2){       //CASO 8        //pedir prestado al hermano izquierdo
            //Se saca la ultima llave del hermano izquierdo y se agrega al actual nodo
            valor=h_izq->llaves.sacar();

            h_izq->llaves.borrar(valor);
            p->llaves.agregar(valor);

            //Se indica la nueva primera llave del nodo en el padre(ya que el hermano izquierdo le presto una llave menor que las que contenia)
            v->valor=p->llaves.dondePrincipio()->valor;

        }else{              //CASO 9        //mandar llaves al hermano izquierdo y limpiar nodo
            //Sacar indice y direccion del nodo actual en el padre
            valor=v->valor;
            padre->llaves.sacar();

            //Es la ultima direccion del nodo padre
            padre->direccion.sacar();

            //Mandar llaves del nodo actual al hermano izquierdo
            while(p->llaves.CuantosVal()>0){
                valor=p->llaves.dondePrincipio()->valor;
                p->llaves.borrar(valor);
                h_izq->llaves.agregar(valor);
            }
            //Liberar memoria del nodo actual
            p->direccion.limpiar();
            p->llaves.limpiar();
            p->esHoja=false;
            p->padre=NULL;
            delete p;

        }

    }

    //Falta checar cuando los padres se veran afectados
    while(padre!=raiz){

            //Se revisa si el padre tiene menos direcciones de las minimas para cumplir las reglas del arbol
            if(padre->direccion.CuantosDir()<(orden-1)/2+1){

                    //Si es necesario ajustar el arbol se ajusta y se revisa el padre del nodo actual
                    aux=padre->padre;//Se guarda el padre por si acaso se libera memoria al modificar los padres
                    modificarPadres(padre);
                    padre=aux;

            }else{
                //En caso de no ser necesario ajustar el arbol
                padre=raiz;
            }

    }

    //Se revisa si la raiz se debe ajustar
    if(raiz->direccion.CuantosDir() < 2){

        p=raiz;
        raiz=raiz->direccion.dondePrincipio()->direccion;
        raiz->padre=NULL;
        p->direccion.limpiar();
        p->llaves.limpiar();
        p->esHoja=false;
        p->padre=NULL;
        delete p;

    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Modifica los nodos intermedios del arbol y ajusta el arbol de ser necesario.

    Nodo *p la direccion del nodo que debe ajustarce en el arbol.
*/
void Arbol::modificarPadres(Nodo *p){//Estos casos permiten ajustar el arbol en los nodos intermedios
    Nodo *padre, *h_izq, *h_der, *direccion;
    int valor, indice=0;
    padre=p->padre;
    CajaDireccion *q, *i;
    CajaValor *v;

    q=padre->direccion.dondePrincipio();
    while(q->direccion!=p){
        indice+=1;
        if(q->siguiente!=NULL){
                i=q;
        }
        q=q->siguiente;

    }

    v=padre->llaves.dondePrincipio();
    for(int i=1; i<indice; i++){
        v=v->siguiente;
    }
    //Se saca el valor en el nodo padre y se agrega al nodo hijo 'p'
    valor=v->valor;

    padre->llaves.borrar(valor);
    p->llaves.agregar(valor);

    if(indice==0){//Es la primera direccion del nodo padre

        //Debe tener hermano derecho ya que no puede tener una sola direccion

        h_der=(q->siguiente)->direccion;

        if(h_der->llaves.CuantosVal()>(orden-1)/2){   //CASO 1   //El hermano derecho le puede prestar una llave

            //Se saca la primera llave del nodo derecho y se agrega al nodo padre
            valor=h_der->llaves.dondePrincipio()->valor;
            h_der->llaves.borrar(valor);
            padre->llaves.agregar(valor);

            //Se saca la primera direccion del hermano derecho y se agrega a las direcciones del nodo actual(quedara al final por ser una direccion del hermano derecho).
            direccion=h_der->direccion.dondePrincipio()->direccion;
            h_der->direccion.borrar(direccion);
            p->direccion.agregar(direccion);

            //Asignar nuevo padre al nodo que se movio
            direccion->padre=p;

        }else{  //CASO 2  //El hermano derecho no le puede prestar
            //Se sacan las llaves del hermano derecho para agregarse al nodo actual
            while(h_der->llaves.CuantosVal()>0){
                //valor=h_der->llaves.dondePrincipio()->valor;
                //h_der->llaves.borrar(valor);
                valor=h_der->llaves.sacar();

                p->llaves.agregar(valor);

            }
            //Se sacan las direcciones del hermano derecho para agregarse al nodo actual
            while(h_der->direccion.CuantosDir()>0){

                direccion=h_der->direccion.sacar();

                p->direccion.agregar(direccion);

                //Se asignan sus nuevos padres a los nodos
                direccion->padre=p;


            }
            //Se saca la direccion del hermano derecho en el padre
            padre->direccion.borrar(h_der);


            //Liberar memoria del hermano derecho
            h_der->direccion.limpiar();
            h_der->llaves.limpiar();
            h_der->esHoja=false;
            h_der->padre=NULL;
            delete h_der;

        }

        //Si es el padre de una hoja se actualiza al primer valor de su nuevo
        if(p->direccion.dondePrincipio()->direccion->esHoja==true){
            v=p->llaves.dondePrincipio();
            for(int j=0; j<((orden-1)/2-1); j++){
                v=v->siguiente;
            }
            i=p->direccion.dondePrincipio();
            for(int j=0; j<((orden+1)/2-1); j++){
                i=i->siguiente;
            }
            v->valor=i->direccion->llaves.dondePrincipio()->valor;
        }

    }else if(indice<orden-1){//Si el nodo cuelga entre la direccion[1] y direccion[orden-1]

        //Debe tener un hermano izquierdo
        h_izq=i->direccion;

        if(q->siguiente!=NULL){//Checar si tiene hermano derecho

            h_der=q->siguiente->direccion;

            if(h_der->llaves.CuantosVal()>(orden-1)/2||h_izq->llaves.CuantosVal()>(orden-1)/2){//Se revisa si el hermano derecho o izquierdo pueden prestar llaves sin incumplir las reglas del arbol

                if(h_der->llaves.CuantosVal()>(orden-1)/2){           //CASO 3        //Se revisa primero el hermano derecho para prestar
                    padre->llaves.agregar(valor);

                    p->llaves.borrar(valor);

                    v=padre->llaves.dondePrincipio();
                    for(int j=1; j<indice+1; j++){
                        v=v->siguiente;
                    }
                    valor=v->valor;

                    p->llaves.agregar(valor);

                    padre->llaves.borrar(valor);


                    //Se saca la primera llave del hermano derecho y se agrega al nodo padre
                    valor=h_der->llaves.dondePrincipio()->valor;
                    h_der->llaves.borrar(valor);

                    padre->llaves.agregar(valor);


                    //Se saca la primera direccion del hermano derecho y se agrega a las direcciones del nodo actual(quedara al final por ser una direccion del hermano derecho).
                    direccion=h_der->direccion.dondePrincipio()->direccion;
                    h_der->direccion.borrar(direccion);
                    p->direccion.agregar(direccion);

                    //Asignar nuevo padre al nodo que se movio
                    direccion->padre=p;

                    //Si es el padre de una hoja se actualiza al primer valor de su nuevo
                    if(p->direccion.dondePrincipio()->direccion->esHoja==true){
                        v=p->llaves.dondePrincipio();
                        for(int j=0; j<((orden-1)/2-1); j++){
                            v=v->siguiente;
                        }
                        i=p->direccion.dondePrincipio();
                        for(int j=0; j<((orden+1)/2-1); j++){
                            i=i->siguiente;
                        }
                        v->valor=i->direccion->llaves.dondePrincipio()->valor;

                    }

                }else{    //CASO 4    //Solo el hermano izquierdo es viable para prestarle una llave
                    //Se saca la ultima llave del hermano izquierdo y se agrega al nodo padre
                    valor=h_izq->llaves.sacar();
                    h_izq->llaves.borrar(valor);
                    padre->llaves.agregar(valor);

                    //Se saca la primera direccion del hermano izquierdo y se agrega a las direcciones del nodo actual(quedara al principio por ser una direccion del hermano izquierdo).
                    direccion=h_izq->direccion.sacar();
                    h_izq->direccion.borrar(direccion);
                    p->direccion.agregar(direccion);

                    //Asignar nuevo padre al nodo que se movio
                    direccion->padre=p;

                    //Si es el padre de una hoja se actualiza al primer valor de su nuevo
                    if(p->direccion.dondePrincipio()->direccion->esHoja==true){
                        i=p->direccion.dondePrincipio()->siguiente;
                        p->llaves.dondePrincipio()->valor=i->direccion->llaves.dondePrincipio()->valor;

                    }

                }

            }else{    //CASO 5    //Ninguno de los dos hermanos pueden prestarle llaves y direcciones.
                while(p->llaves.CuantosVal()>0){
                    valor=p->llaves.dondePrincipio()->valor;
                    p->llaves.borrar(valor);
                    h_izq->llaves.agregar(valor);
                }

                //Se sacan las direcciones del nodo actual para agregarse al hermano izquierdo
                while(p->direccion.CuantosDir()>0){
                    direccion=p->direccion.dondePrincipio()->direccion;

                    h_izq->direccion.agregar(direccion);

                    p->direccion.borrar(direccion);

                    //Se asignan sus nuevos padres a los nodos
                    direccion->padre=h_izq;

                }

                padre->direccion.borrar(p);

                //Liberar memoria del nodo actual
                p->direccion.limpiar();
                p->llaves.limpiar();
                p->esHoja=false;
                p->padre=NULL;
                delete p;

                //Si es el padre de una hoja se actualiza al primer valor de su nuevo
                if(h_izq->direccion.dondePrincipio()->direccion->esHoja==true){
                    v=h_izq->llaves.dondePrincipio();
                    for(int j=0; j<((orden-1)/2); j++){
                        v=v->siguiente;
                    }

                    i=h_izq->direccion.dondePrincipio();
                    for(int j=0; j<((orden+1)/2); j++){
                        i=i->siguiente;
                    }

                    v->valor=i->direccion->llaves.dondePrincipio()->valor;
                }

            }

        }else{//Solo tiene hermano izquierdo
            if(h_izq->llaves.CuantosVal()>(orden-1)/2){    //CASO 6    //Pedir al hermano izquierdo en caso de poder
                //Se saca la ultima llave del hermano izquierdo y se agrega al nodo padre
                valor=h_izq->llaves.sacar();
                h_izq->llaves.borrar(valor);
                padre->llaves.agregar(valor);

                //Se saca la primera direccion del hermano izquierdo y se agrega a las direcciones del nodo actual(quedara al principio por ser una direccion del hermano izquierdo).
                direccion=h_izq->direccion.sacar();
                h_izq->direccion.borrar(direccion);
                p->direccion.agregar(direccion);

                //Asignar nuevo padre al nodo que se movio
                direccion->padre=p;

                //Si es el padre de una hoja se actualiza al primer valor de su nuevo
                if(p->direccion.dondePrincipio()->direccion->esHoja==true){
                    i=p->direccion.dondePrincipio()->siguiente;
                    p->llaves.dondePrincipio()->valor=i->direccion->llaves.dondePrincipio()->valor;

                }

            }else{        //Caso 7    //Se tiene que unir con el hermano izquierdo
                //Se sacan las llaves del nodo actual para agregarse al hermano izquierdo
                while(p->llaves.CuantosVal()>0){
                    valor=p->llaves.dondePrincipio()->valor;
                    p->llaves.borrar(valor);
                    h_izq->llaves.agregar(valor);
                }

                //Se sacan las direcciones del nodo actual para agregarse al hermano izquierdo
                while(p->direccion.CuantosDir()>0){
                    direccion=p->direccion.dondePrincipio()->direccion;

                    h_izq->direccion.agregar(direccion);

                    p->direccion.borrar(direccion);

                    //Se asignan sus nuevos padres a los nodos
                    direccion->padre=h_izq;

                }

                //Se saca la direccion del nodo actual en el padre
                padre->direccion.borrar(p);

                //Liberar memoria del nodo actual
                p->direccion.limpiar();
                p->llaves.limpiar();
                p->esHoja=false;
                p->padre=NULL;
                delete p;

                //Si es el padre de una hoja se actualiza al primer valor de su nuevo
                if(h_izq->direccion.dondePrincipio()->direccion->esHoja==true){
                    v=h_izq->llaves.dondePrincipio();
                    for(int j=0; j<((orden-1)/2); j++){
                        v=v->siguiente;
                    }

                    i=h_izq->direccion.dondePrincipio();
                    for(int j=0; j<((orden+1)/2); j++){
                        i=i->siguiente;
                    }

                    v->valor=i->direccion->llaves.dondePrincipio()->valor;

                }

            }

        }
    }else{//Solo tiene hermano izquierdo

        h_izq=i->direccion;

        if(h_izq->llaves.CuantosVal()>(orden-1)/2){    //Caso 8    //El hermano izquierdo le puede prestar una llave y una direccion
            //Se saca la ultima llave del hermano izquierdo y se agrega al nodo padre
            valor=h_izq->llaves.sacar();
            h_izq->llaves.borrar(valor);
            padre->llaves.agregar(valor);

            //Se saca la primera direccion del hermano izquierdo y se agrega a las direcciones del nodo actual(quedara al principio por ser una direccion del hermano izquierdo).
            direccion=h_izq->direccion.sacar();
            h_izq->direccion.borrar(direccion);
            p->direccion.agregar(direccion);

            //Asignar nuevo padre al nodo que se movio
            direccion->padre=p;


            //Si es el padre de una hoja se actualiza al primer valor de su nuevo
            if(p->direccion.dondePrincipio()->direccion->esHoja==true){
                i=p->direccion.dondePrincipio()->siguiente;
                p->llaves.dondePrincipio()->valor=i->direccion->llaves.dondePrincipio()->valor;

            }

        }else{    //Caso 9    //Se tiene que unir el nodo con su hermano izquierdo
            //Se sacan las llaves del nodo actual para agregarse al hermano izquierdo
            while(p->llaves.CuantosVal()>0){
                valor=p->llaves.sacar();

                h_izq->llaves.agregar(valor);
            }

            //Se sacan las direcciones del nodo actual para agregarse al hermano izquierdo
            while(p->direccion.CuantosDir()>0){
                direccion=p->direccion.sacar();
                h_izq->direccion.agregar(direccion);
                //Se asignan sus nuevos padres a los nodos
                direccion->padre=h_izq;
            }

            //Se saca la direccion del nodo actual en el padre
            padre->direccion.borrar(p);
            //Liberar memoria del nodo actual
            p->direccion.limpiar();
            p->llaves.limpiar();
            p->esHoja=false;
            p->padre=NULL;
            delete p;

            //Si es el padre de una hoja se actualiza al primer valor de su nuevo
            if(h_izq->direccion.dondePrincipio()->direccion->esHoja==true){
                v=h_izq->llaves.dondePrincipio();
                for(int j=0; j<((orden-1)/2); j++){
                    v=v->siguiente;
                }
                i=h_izq->direccion.dondePrincipio();
                for(int j=0; j<((orden+1)/2); j++){
                    i=i->siguiente;
                }
                v->valor=i->direccion->llaves.dondePrincipio()->valor;

            }

        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Permite leer un archivo donde se encuentran los valores que se agregaran al arbol.
*/
void Arbol::lecturaLlaves(string mensaje){
    //Se abre el archivo
    string ruta="casos/"+mensaje+".txt";
    char *y = (char *)ruta.c_str();
    ifstream fin(y);
    //En caso de no poder abrir el archivo se le avisa al usuario
    if(fin.fail()){
        cout<<"No se pudo abrir el archivo";
        system("pause");
        exit(1);
    }
    int arcos, a;
    //Se lee la cantidad de numeros que se leeran
    fin>>arcos;
    for(int i=1; i<=arcos; i++){
	//Se agrega la informacion a la grafica
        fin>>a;
        agregar(a);
        cout<<"\n -> Numero agregado: "<<a<<"\n";
    }
    cout<<"\n\n\n";
    cout<<"Archivo leido ....\n";
    cout<<"Nodos generados ";
    cout<<"\n\n\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Permite leer un archivo donde se encuentran los valores que se borraran del arbol.
*/
void Arbol::borradoLlaves(string mensaje){
    //Se abre el archivo
    string ruta="casosDeBorrado/"+mensaje+".txt";
    char *y = (char *)ruta.c_str();
    ifstream fin(y);
    //En caso de no poder abrir el archivo se le avisa al usuario
    if(fin.fail()){
        cout<<"No se pudo abrir el archivo";
        system("pause");
        exit(1);
    }
    int arcos, a;
    //Se lee la cantidad de numeros que se leeran
    fin>>arcos;
    for(int i=1; i<=arcos; i++){
	//Se agrega la informacion a la grafica
        fin>>a;
        borrar(a);
        cout<<"\n -> Numero borrado: " <<a<<"\n";
    }
    cout<<"\n\n\n";
    cout<<"Archivo leido ....\n";
    cout<<"Valores borrados .....";
    cout<<"\n\n\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Permite pintar los nodos del arbol en pantalla.
*/
void Arbol::pintar(){
    cout<<"\n\n=========== Arbol =============\n\n";
    Cola *Q= new Cola;
    Cola *H= new Cola;
    Q->nuevo();
    H->nuevo();
	Nodo *siguiente;
	CajaDireccion *direccion;
	if(raiz!=NULL){
        Q->agregar(raiz);
        while(!Q->estaVacia()){
            siguiente= Q->sacar();
            if(siguiente->esHoja==true){
                cout<<"Es hoja: ";
            }
            siguiente->llaves.pintar();
            if(siguiente->esHoja==true){
                H->agregar(siguiente);
            }
            direccion=siguiente->direccion.dondePrincipio();
            while(direccion!=NULL){
                Q->agregar(direccion->direccion);
                direccion=direccion->siguiente;
            }
            cout<<"\n";
        }

        cout<<"Valores: ";
        while(!H->estaVacia()){
            siguiente=H->sacar();
            siguiente->llaves.pintar();
        }

        cout<<"\n";
	}else{
        cout<<"\nEl arbol esta vacio\n";
	}

	Q->limpiar();
	H->limpiar();
    cout<<"\n\n=========== Fin del Arbol =============\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

