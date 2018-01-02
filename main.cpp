#include "arbol.h"

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
using namespace std;
int main(){

    string mensaje="mensaje";
    int orden=3;

    cout<<"\nPrograma que almacena numeros en una estructura arbol b+.\n\n";

    cout<<"De que orden quiere generar el arbol:";
    cin>>orden;

    Arbol A(orden);

    cout<<"\n\nIngrese el nombre del archivo con valores para\nagregar al arbol, en la carpeta valores:";
    cin>>mensaje;

    A.lecturaLlaves(mensaje);

    cout<<"\n//////////////////////////Arbol generado por archivo///////////////////////////\n";
    A.pintar();

    cout<<"\n\nDeseas borrar valores del arbol desde un archivo?\n[1]Si\n[Otra tecla]NO\n\nOpcion:";
    cin>>mensaje;
    if(mensaje=="1"){
        cout<<"\n\nIngrese el nombre del archivo con valores para\nborrar del arbol, en la carpeta valoresBorrados:";
        cin>>mensaje;

        A.borradoLlaves(mensaje);
        cout<<"\n//////////////////////////Arbol con valores borrados//////////////////////////\n";
        A.pintar();
    }

    cout<<"\n\nGracias por usar este programa\n\n";

    return 0;
}

