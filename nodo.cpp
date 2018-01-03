#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include "nodo.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Constructor
ListaValor::ListaValor(){
	principio = NULL;
	anterior = NULL;
	donde = Vacio;
	encontrado = NO;
	cuantosVal = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Destructor
ListaValor::~ListaValor(){
	CajaValor *p, *aux;
	p = principio;
	while(p!= NULL){
        aux = p;
        p = p->siguiente;
        delete aux;
    }
    principio = NULL;
    anterior = NULL;
	donde = Vacio;
	encontrado = NO;
	cuantosVal = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ListaValor::nuevo(){
    principio = NULL;
	anterior = NULL;
	donde = Vacio;
	encontrado = NO;
	cuantosVal = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ListaValor::limpiar(){
    CajaValor *p, *aux;
	p = principio;
	while(p!= NULL){
        aux = p;
        p = p->siguiente;
        delete aux;
    }
    principio = NULL;
    anterior = NULL;
	donde = Vacio;
	encontrado = NO;
	cuantosVal = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Funciones de la clase
/*
    Esta funcion revisa la lista ordenada para determinar la ubicacion de una
    caja en la lista.
*/
void ListaValor::buscar(int a){
	CajaValor *p;
	p = principio;
	if(p == NULL){
		encontrado = NO;
		donde = Vacio;
		return;
	}
	while(p){
		if(p->valor == a){
			encontrado = SI;
			if(principio == p){
				donde = Principio;
			}else{
				donde = EnMedio;
			}
			return;
		}else if(p->valor<a){
			anterior = p;
			p = p->siguiente;
		}else{
			encontrado = NO;
			if(principio == p){
				donde = Principio;
			}else{
				donde = EnMedio;
			}
			return;
		}
	}
	encontrado = NO;
	donde = Final;
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Esta funcion agrega una caja a la lista ordenada con el valor que recibe, en
    la posicion que le corresponde.
*/
int ListaValor::agregar(int a){
	CajaValor *p;
	buscar(a);
	if(encontrado == SI){
		return 0;
	}
	p = new CajaValor;
	if(donde == Vacio){
		principio = p;
		p->siguiente = NULL;
		p->valor = a;
	}else if(donde == Principio){
		p->siguiente = principio;
		principio = p;
		p->valor = a;
	}else if(donde == EnMedio){
		p->siguiente = anterior->siguiente;
		anterior->siguiente = p;
		p->valor = a;
	}else{
		p->siguiente = NULL;
		anterior->siguiente = p;
		p->valor = a;
	}
	cuantosVal++;
	return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Esta funcion busca el valor recibido en la lista para eliminar la caja que
    contenga ese valor.
*/
int ListaValor::borrar(int a){
	CajaValor *p;
	buscar(a);
	if(encontrado == NO){
		return 0;
	}
	if(donde == Principio){
		p = principio;
		principio = p->siguiente;
	}else if(donde == EnMedio){
		p = anterior->siguiente;
		anterior->siguiente = p->siguiente;
	}else{
		p = anterior->siguiente;
		anterior->siguiente = NULL;
	}
	delete p;
	cuantosVal--;
	return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Esta funcion saca la primera caja de la lista ordenada.
*/
int ListaValor::sacar(void){//Saca el ultimo
	CajaValor *p, *ultimo = NULL;
	int valor;
	if(principio == NULL){
		return 999999999;
	}
	p = principio;
	if(p->siguiente!= NULL){
        while(p->siguiente!= NULL){
            if(p->siguiente->siguiente == NULL){
                ultimo = p;
            }
            p = p->siguiente;
        }
        if(ultimo!= NULL){
            ultimo->siguiente = NULL;
        }
	}else{
        principio = NULL;
	}
	p->siguiente = NULL;
	valor = p->valor;
	delete p;
	cuantosVal--;
	return valor;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Constructor
ListaDireccion::ListaDireccion(){
	principio = NULL;
	anterior = NULL;
	donde = Vacio;
	encontrado = NO;
	cuantosDir = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Destructor
ListaDireccion::~ListaDireccion(){
	CajaDireccion *p, *aux;
	p = principio;
	while(p!= NULL){
        aux = p;
        p = p->siguiente;
        delete aux;
    }
    principio = NULL;
    anterior = NULL;
	donde = Vacio;
	encontrado = NO;
	cuantosDir = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ListaDireccion::nuevo(){
    principio = NULL;
	anterior = NULL;
	donde = Vacio;
	encontrado = NO;
	cuantosDir = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ListaDireccion::limpiar(){
    CajaDireccion *p, *aux;
	p = principio;
	while(p!= NULL){
        aux = p;
        p = p->siguiente;
        delete aux;
    }
    principio = NULL;
    anterior = NULL;
	donde = Vacio;
	encontrado = NO;
	cuantosDir = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Funciones de la clase
/*
    Esta funcion revisa la lista ordenada para determinar la ubicacion de una
    caja en la lista.
*/
void ListaDireccion::buscar(Nodo *p){
	CajaDireccion *q;
	q = principio;
	if(q == NULL){
		encontrado = NO;
		donde = Vacio;
		return;
	}
	while(q){
		if(q->direccion == p){
			encontrado = SI;
			if(principio == q){
				donde = Principio;
			}else{
				donde = EnMedio;
			}
			return;
		}else if(p->llaves.dondePrincipio()!= NULL){
             if(q->direccion->llaves.dondePrincipio()->valor<p->llaves.dondePrincipio()->valor){
                anterior = q;
                q = q->siguiente;
            }else{
                encontrado = NO;
                if(principio == q){
                    donde = Principio;
                }else{
                    donde = EnMedio;
                }
                return;
            }
		}else{
            anterior = q;
            encontrado = NO;
            if(principio == q){
                donde = Principio;
            }else if(q->siguiente!= NULL){
                donde = EnMedio;
            }else{
                donde = Final;
            }
            return;
		}
	}
	encontrado = NO;
	donde = Final;
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ListaDireccion::buscarBorrar(Nodo *p){
	CajaDireccion *q;
	q = principio;
	if(q == NULL){
		encontrado = NO;
		donde = Vacio;
		return;
	}
	while(q){

		if(q->direccion == p){
			encontrado = SI;
			if(principio == q){
				donde = Principio;
			}else{
				donde = EnMedio;
			}
			return;
		}else{
            anterior = q;
            q = q->siguiente;
        }
	}
	encontrado = NO;
	donde = Final;
	return;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Esta funcion agrega una caja a la lista ordenada con el valor que recibe, en
    la posicion que le corresponde.
*/
int ListaDireccion::agregar(Nodo *p){
	CajaDireccion *q;
	buscar(p);
	if(encontrado == SI){
		return 0;
	}
	q = new CajaDireccion;
	if(donde == Vacio){
		principio = q;
		q->siguiente = NULL;
		q->direccion = p;
	}else if(donde == Principio){
		q->siguiente = principio;
		principio = q;
		q->direccion = p;
	}else if(donde == EnMedio){
		q->siguiente = anterior->siguiente;
		anterior->siguiente = q;
		q->direccion = p;
	}else{
		q->siguiente = NULL;
		anterior->siguiente = q;
		q->direccion = p;
	}
	cuantosDir++;
	return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Esta funcion busca el valor recibido en la lista para eliminar la caja que
    contenga ese valor.
*/
int ListaDireccion::borrar(Nodo *p){
	CajaDireccion *q;
	buscarBorrar(p);
	if(encontrado == NO){
		return 0;
	}
	if(donde == Principio){
		q = principio;
		principio = q->siguiente;
	}else if(donde == EnMedio){
	    q = anterior->siguiente;
	    anterior->siguiente = q->siguiente;
	}else{
		q = anterior->siguiente;
		anterior->siguiente = NULL;
	}
	delete q;
	cuantosDir--;
	return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Esta funcion saca la primera caja de la lista ordenada.
*/
Nodo* ListaDireccion::sacar(void){//Saca la ultima direccion
	CajaDireccion *p, *ultimo = NULL;
	Nodo * direccion;
	if(principio == NULL){
		return NULL;
	}

	p = principio;
	if(p->siguiente!= NULL){
        while(p->siguiente!= NULL){
            if(p->siguiente->siguiente == NULL){
                ultimo = p;
            }
            p = p->siguiente;
        }
        ultimo->siguiente = NULL;
	}else{
        principio = NULL;
	}
	direccion = p->direccion;
	if(ultimo!= NULL){
        ultimo->siguiente = NULL;
	}
	delete p;
	cuantosDir--;
	return direccion;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Esta funcion esta funcion imprime los valores de cada caja en la lista.
*/
void ListaValor::pintar(void){
   CajaValor *p;
   p = principio;

   if(cuantosVal == 0){
        cout<<"lista vacia.\n\n";
   }else{
       while(p!= NULL){
           cout<<p->valor<<" ";
           p = p->siguiente;

       }
   }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CajaValor* ListaValor::dondePrincipio(){
    return principio;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CajaDireccion* ListaDireccion::dondePrincipio(){
    return principio;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ListaDireccion::CuantosDir(){
    return cuantosDir;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ListaValor::CuantosVal(){
    return cuantosVal;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
