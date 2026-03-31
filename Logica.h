#ifndef LOGICA_H_INCLUDED
#define LOGICA_H_INCLUDED
#include <iostream>
#include <vector> // inclusion de arreglos inteligentes
#include <memory> // inclusion de memoria dinamica inteligente
#include <string>
#include <iomanip> // para crear salidas de datos bien formadas
#include "misc.h"
#include "Contrasenia.h"

using std::cin, std::cout, std::endl;

std::vector<std::unique_ptr<contrasenia>> coleccion; /*esto crea una coleccion de objetos que crece en tiempo de ejecucion
Es beneficioso ya que no sabemos cuantas contrasenias almacenara el usuario como tambien tenemos acceso al objeto a travez de punteros, tambien
la memoria se liberara de forma automatica evitando fugas que puedan perjudicar o colapsos de programa en la ejecucion en vivo
*/


// prototipos de funcion
void Alta(std::vector<std::unique_ptr<contrasenia>>& coleccion);
void mostrarTodo(std::vector<std::unique_ptr<contrasenia>>& coleccion);


// Esta funcion se encarga de gestionar el menu de la aplicacion
void menu(){
    int opc; // variable que maneja las opciones del menu
    do{
    cout<<"=== KeyRingCube ==="<<endl;
    cout<<"[1] Alta "<<endl;
    cout<<"[2] Eliminar"<<endl;
    cout<<"[3] Actualizar"<<endl;
    cout<<"[4] Mostrar Todos"<<endl;
    cout<<"[5] Buscar (por ID)"<<endl;
    cout<<"[6] Guardar datos"<<endl;
    cout<<"[7] Cargar datos"<<endl;
    cout<<"[0] Salir"<<endl;
    cout<<"Opcion: "; cin>>opc;

    switch(opc){
        case ALTA: Alta(coleccion); break;
        case BAJA:  cout<<"En construccion....\n"; break;
        case ACTUALIZAR: cout<<"En construccion....\n"; break;
        case MOSTRAR: mostrarTodo(coleccion); break;
        case BUSCAR: cout<<"En construccion....\n"; break;
        case GUARDAR: cout<<"En construccion....\n"; break;
        case CARGAR: cout<<"En construccion....\n"; break;
        case SALIR: break;
        default: cout<<"Error, Opcion invalida"<<endl;
            break;
    }

    }while(opc!=SALIR);
    cout<<"Bytes!!!!!!";

}

void Alta(std::vector<std::unique_ptr<contrasenia>>& coleccion){
    static int id = 1; // al usar static al estar cambiendo entre funciones del programa el ultimo valor se mantiene,
    // eso explica rl iterador final de la variable al final de la funcion
    std::string nombre, descripcion, password;

    cin.ignore();
    cout<<"Digite el nombre de la clave a guardar: "; getline(cin,nombre);
    cout<<"Digite una descripcion: "; getline(cin,descripcion);
    cout<<"Digite la contrasenia a guardar: "<<endl; getline(cin,password);

    auto lista = std::make_unique<contrasenia>(); // creamos el objeto para agregar datos al vector dinamico
    lista->fijaId(id);
    lista->fijaNombre(nombre);
    lista->fijaDescripcion(descripcion);
    lista->fijaPassword(password);

    coleccion.push_back(std::move(lista)); // agrega datos al vector hacia el final de la coleccion es decir
    // alta que se registra, va al final de la coleccion

    cout<<"Contrasenia guardada exitosamente con el ID: "<<id<<endl;
    id++; // la id o "numero de registro" empieza desde el 1
}

void mostrarTodo(std::vector<std::unique_ptr<contrasenia>>& coleccion){
    cin.ignore();
    cout<<std::string(80, '-')<<endl; // esto crea una cadena de 80 caracteres
    cout<<"\t\t\t\tMOSTRAR TODO\n";
    cout<<std::string(80, '-')<<endl;
    // configuracion de los anchos de la columna
    cout<<std::left; // con esto todos los datos se alinean a la izquierda
    cout<<std::setw(8)<<"ID" // "setw()" reserva un numero de estacios para el siguiente elemento, se alinea a la derecha por defecto
        <<std::setw(20)<<"Nombre"
        <<std::setw(25)<<"Descripcion"
        <<std::setw(20)<<"Contrasenia"<<endl;
    cout<<std::string(80, '-')<<endl;

    for(size_t i = 0; i < coleccion.size(); i++ ){
        cout<<std::setw(8)<<coleccion[i]->dameId()
            <<std::setw(20)<<coleccion[i]->dameNombre()
            <<std::setw(25)<<coleccion[i]->dameDescripcion()
            <<std::setw(20)<<coleccion[i]->damePassword()<<endl;
    }
    /*"size_t" es un tipo de dato especial para indices, este por ningun motivo puede iterar con numeros negativos
      "coleccion.size()": el bucle va a iterar dependiendo hasta que numero de elementos tenga registrados en mi objeto
        */
    cout<<std::string(80, '-')<<endl;
}


#endif // LOGICA_H_INCLUDED
