#include "arbol.h"

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
using namespace std;
int main(){

    string mensaje="mensaje";
    int orden=3;

    cout<<"\nPrograma que almacena numeros en una estructura arbol B+ de orden 3.\n\n";

    cout << "\nSe cargan los datos que agregar al arbol desde un archivo de texto guardado en la carpeta 'valores', este no debe incluir .txt, la ruta ya esta definida.\n \
        Para eliminar datos, de igual manera se cargan en desde la carpeta 'valoresBorrados', y se eliminan los valores que contenga este archivo\n" <<endl;

    Arbol A(orden);

    cout<<"\n\nIngrese el nombre del archivo con valores para\nagregar al arbol, en la carpeta valores:  ";
    cin>>mensaje;

    A.lecturaLlaves(mensaje);

    cout<<"\nArbol generado por archivo\n";
    A.pintar();

    cout<<"\n\nDeseas borrar valores del arbol desde un archivo?\n [1]Si\n [Otra tecla]NO\n \nOpcion:  ";

    cin>>mensaje;
    if(mensaje=="1"){
        cout<<"\n\nIngrese el nombre del archivo con valores para\nborrar del arbol, en la carpeta valoresBorrados:  ";
        cin>>mensaje;

        A.borradoLlaves(mensaje);
        cout<<"\nArbol con valores borrados\n";
        A.pintar();
    }

    cout<<"\nEspinoza Maciel Gilberto \n Paredes Padilla Jorge Xavier \n Figueroa Miranda Jose Jesus \n\n";

    system("pause");
    return 0;
}

