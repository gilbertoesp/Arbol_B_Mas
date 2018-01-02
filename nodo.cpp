#include "Nodo.h"

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
using namespace std;
//Constructor
listaVal::listaVal(){
	principio=NULL;
	anterior=NULL;
	donde=Vacio;
	encontrado=NO;
	cuantos_Val=0;
}
//Destructor
listaVal::~listaVal(){
	cajaVal *p, *aux;
	p=principio;
	while(p!=NULL){
        aux=p;
        p=p->siguiente;
        free(aux);
    }
    principio=NULL;
    anterior=NULL;
	donde=Vacio;
	encontrado=NO;
	cuantos_Val=0;
}
void listaVal::nuevo(){
    principio=NULL;
	anterior=NULL;
	donde=Vacio;
	encontrado=NO;
	cuantos_Val=0;
}
void listaVal::limpiar(){
    cajaVal *p, *aux;
	p=principio;
	while(p!=NULL){
        aux=p;
        p=p->siguiente;
        free(aux);
    }
    principio=NULL;
    anterior=NULL;
	donde=Vacio;
	encontrado=NO;
	cuantos_Val=0;
}
//Funciones de la clase
/*
    Esta funcion revisa la lista ordenada para determinar la ubicacion de una
    caja en la lista.
*/
void listaVal::buscar(int a){
	cajaVal *p;
	p=principio;
	if(p==NULL){
		encontrado=NO;
		donde=Vacio;
		return;
	}
	while(p){
		if(p->valor==a){
			encontrado=SI;
			if(principio==p){
				donde=Principio;
			}else{
				donde=EnMedio;
			}
			return;
		}else if(p->valor<a){
			anterior=p;
			p=p->siguiente;
		}else{
			encontrado=NO;
			if(principio==p){
				donde=Principio;
			}else{
				donde=EnMedio;
			}
			return;
		}
	}
	encontrado=NO;
	donde=Final;
	return;
}
/*
    Esta funcion agrega una caja a la lista ordenada con el valor que recibe, en
    la posicion que le corresponde.
*/
int listaVal::agregar(int a){
	cajaVal *p;
	buscar(a);
	if(encontrado==SI){
		return 0;
	}
	p=(cajaVal*)malloc(sizeof(cajaVal));
	if(donde==Vacio){
		principio=p;
		p->siguiente=NULL;
		p->valor=a;
	}else if(donde==Principio){
		p->siguiente=principio;
		principio=p;
		p->valor=a;
	}else if(donde==EnMedio){
		p->siguiente=anterior->siguiente;
		anterior->siguiente=p;
		p->valor=a;
	}else{
		p->siguiente=NULL;
		anterior->siguiente=p;
		p->valor=a;
	}
	cuantos_Val++;
	return 1;
}
/*
    Esta funcion busca el valor recibido en la lista para eliminar la caja que
    contenga ese valor.
*/
int listaVal::borrar(int a){
	cajaVal *p;
	buscar(a);
	if(encontrado==NO){
		return 0;
	}
	if(donde==Principio){
		p=principio;
		principio=p->siguiente;
	}else if(donde==EnMedio){
		p=anterior->siguiente;
		anterior->siguiente=p->siguiente;
	}else{
		p=anterior->siguiente;
		anterior->siguiente=NULL;
	}
	free(p);
	cuantos_Val--;
	return 1;
}
/*
    Esta funcion saca la primera caja de la lista ordenada.
*/
int listaVal::sacar(void){//Saca el ultimo
	cajaVal *p, *ultimo=NULL;
	int valor;
	if(principio==NULL){
		return 999999999;
	}
	p=principio;
	if(p->siguiente!=NULL){

        while(p->siguiente!=NULL){


            if(p->siguiente->siguiente==NULL){

                ultimo=p;
            }

            p=p->siguiente;
        }
        if(ultimo!=NULL){
            ultimo->siguiente=NULL;
        }
	}else{
        principio=NULL;
	}
	p->siguiente=NULL;
	valor=p->valor;
	free (p);
	cuantos_Val--;
	return valor;
}
/*
    Esta funcion esta funcion imprime los valores de cada caja en la lista.
*/

//Constructor
listaDir::listaDir(){
	principio=NULL;
	anterior=NULL;
	donde=Vacio;
	encontrado=NO;
	cuantos_Dir=0;
}
//Destructor
listaDir::~listaDir(){
	cajaDir *p, *aux;
	p=principio;
	while(p!=NULL){
        aux=p;
        p=p->siguiente;
        free(aux);
    }
    principio=NULL;
    anterior=NULL;
	donde=Vacio;
	encontrado=NO;
	cuantos_Dir=0;
}
void listaDir::nuevo(){
    principio=NULL;
	anterior=NULL;
	donde=Vacio;
	encontrado=NO;
	cuantos_Dir=0;
}
void listaDir::limpiar(){
    cajaDir *p, *aux;
	p=principio;
	while(p!=NULL){
        aux=p;
        p=p->siguiente;
        free(aux);
    }
    principio=NULL;
    anterior=NULL;
	donde=Vacio;
	encontrado=NO;
	cuantos_Dir=0;
}
//Funciones de la clase
/*
    Esta funcion revisa la lista ordenada para determinar la ubicacion de una
    caja en la lista.
*/
void listaDir::buscar(Nodo *p){
	cajaDir *q;
	q=principio;
	if(q==NULL){
		encontrado=NO;
		donde=Vacio;
		return;
	}
	while(q){

		if(q->dir==p){

			encontrado=SI;
			if(principio==q){

				donde=Principio;
			}else{

				donde=EnMedio;
			}
			return;

		}else if(p->llaves.dondePrincipio()!=NULL){

             if(q->dir->llaves.dondePrincipio()->valor<p->llaves.dondePrincipio()->valor){

                anterior=q;
                q=q->siguiente;
            }else{

                encontrado=NO;
                if(principio==q){
                    donde=Principio;
                }else{
                    donde=EnMedio;
                }
                return;
            }
		}else{

            anterior=q;
            encontrado=NO;
            if(principio==q){
                donde=Principio;
            }else if(q->siguiente!=NULL){
                donde=EnMedio;
            }else{
                donde=Final;
            }

            return;
		}
	}

	encontrado=NO;
	donde=Final;
	return;

}
void listaDir::buscarBorrar(Nodo *p){
	cajaDir *q;
	q=principio;
	if(q==NULL){
		encontrado=NO;
		donde=Vacio;
		return;
	}
	while(q){

		if(q->dir==p){
			encontrado=SI;
			if(principio==q){
				donde=Principio;
			}else{
				donde=EnMedio;
			}
			return;
		}else{

            anterior=q;
            q=q->siguiente;
        }

	}
	encontrado=NO;
	donde=Final;
	return;

}
/*
    Esta funcion agrega una caja a la lista ordenada con el valor que recibe, en
    la posicion que le corresponde.
*/
int listaDir::agregar(Nodo *p){
	cajaDir *q;

	buscar(p);

	if(encontrado==SI){
		return 0;
	}

	q=(cajaDir*)malloc(sizeof(cajaDir));
	if(donde==Vacio){
		principio=q;
		q->siguiente=NULL;
		q->dir=p;
	}else if(donde==Principio){
		q->siguiente=principio;
		principio=q;
		q->dir=p;
	}else if(donde==EnMedio){
		q->siguiente=anterior->siguiente;
		anterior->siguiente=q;
		q->dir=p;
	}else{
		q->siguiente=NULL;
		anterior->siguiente=q;
		q->dir=p;
	}
	cuantos_Dir++;
	return 1;
}
/*
    Esta funcion busca el valor recibido en la lista para eliminar la caja que
    contenga ese valor.
*/
int listaDir::borrar(Nodo *p){
	cajaDir *q;

	buscarBorrar(p);

	if(encontrado==NO){
		return 0;
	}
	if(donde==Principio){
		q=principio;
		principio=q->siguiente;
	}else if(donde==EnMedio){
	    q=anterior->siguiente;
	    anterior->siguiente=q->siguiente;
	}else{

		q=anterior->siguiente;
		anterior->siguiente=NULL;
	}
	free(q);
	cuantos_Dir--;
	return 1;
}
/*
    Esta funcion saca la primera caja de la lista ordenada.
*/
Nodo* listaDir::sacar(void){//Saca la ultima direccion
	cajaDir *p, *ultimo=NULL;

	Nodo * dir;
	if(principio==NULL){
		return NULL;
	}

	p=principio;
	if(p->siguiente!=NULL){
        while(p->siguiente!=NULL){
            if(p->siguiente->siguiente==NULL){
                ultimo=p;
            }
            p=p->siguiente;
        }
        ultimo->siguiente=NULL;
	}else{
        principio=NULL;
	}
	dir=p->dir;
	if(ultimo!=NULL){
        ultimo->siguiente=NULL;
	}
	free (p);
	cuantos_Dir--;
	return dir;
}
/*
    Esta funcion esta funcion imprime los valores de cada caja en la lista.
*/
void listaVal::pintar(void){
   cajaVal *p;
   p=principio;

   if(cuantos_Val==0){
        cout<<"lista vacia.\n\n";
   }else{
       while(p!=NULL){
           cout<<p->valor<<" ";
           p=p->siguiente;

       }
   }
}

cajaVal* listaVal::dondePrincipio(){
    return principio;
}
cajaDir* listaDir::dondePrincipio(){
    return principio;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int listaDir::cuantosDir(){
    return cuantos_Dir;
}
int listaVal::cuantosVal(){

    return cuantos_Val;

}

