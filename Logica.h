#ifndef LOGICA_H_INCLUDED
#define LOGICA_H_INCLUDED
#include <iostream>
#include <vector> // inclusion de arreglos inteligentes
#include <memory> // inclusion de memoria dinamica inteligente
#include <string> // libreria para la manipulacion de cadenas
#include <iomanip> // para crear salidas de datos bien formadas
#include "misc.h"
#include "Contrasenia.h"

using std::cin, std::cout, std::endl;

std::vector<std::unique_ptr<contrasenia>> coleccion; /*esto crea una coleccion de objetos que crece en tiempo de ejecucion
Es beneficioso ya que no sabemos cuantas contrasenias almacenara el usuario como tambien tenemos acceso al objeto a traves de punteros, tambien
la memoria se liberara de forma automatica evitando fugas que puedan perjudicar o colapsos de programa en la ejecucion en vivo
*/


// prototipos de funcion
void Alta(std::vector<std::unique_ptr<contrasenia>>& coleccion);
void Baja(std::vector<std::unique_ptr<contrasenia>>& coleccion);
void Actualizar(std::vector<std::unique_ptr<contrasenia>>& coleccion);
void mostrarTodo(std::vector<std::unique_ptr<contrasenia>>& coleccion);
void Buscar(std::vector<std::unique_ptr<contrasenia>>& coleccion);

// Esta funcion se encarga de gestionar el menu de la aplicacion
void menu(){
    int opcion; // variable que maneja las opciones del menu
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
    opcion = leerEntero("Opcion: ");

    /*En este switch invocamos a las funciones que son parte del programa principal*/
    switch(opcion){
        case ALTA:       Alta(coleccion);        break;
        case BAJA:       Baja(coleccion);        break;
        case ACTUALIZAR: Actualizar(coleccion);  break;
        case MOSTRAR:    mostrarTodo(coleccion); break;
        case BUSCAR:     Buscar(coleccion);      break;
        case GUARDAR: cout<<"En construccion....\n"; break;
        case CARGAR: cout<<"En construccion....\n"; break;
        case SALIR: break;
        default: cout<<"Error, Opcion invalida"<<endl;
            break;
    }

    }while(opcion!=SALIR);
    cout<<"Bytes!!!!!!";

}

void Alta(std::vector<std::unique_ptr<contrasenia>>& coleccion){
    static int id = 1; // al usar static al estar cambiendo entre funciones del programa el ultimo valor se mantiene,
    // eso explica rl iterador final de la variable al final de la funcion
    std::string nombre, descripcion, password; // variables auxiliares para almacenar datos del usuario

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
    // la funcion "push_back" se encarga de mover los elementos al final de la coleccion

    cout<<"Contrasenia guardada exitosamente con el ID: "<<id<<endl;
    id++; // la id o "numero de registro" empieza desde el 1
}

void Baja(std::vector<std::unique_ptr<contrasenia>>& coleccion){
    int idEliminar; // variable auxiliar utilizada para buscar la contrasenia a eliminar
    char confirmar; // Esta variable guarda decision del usuario al momento de querer eliminar una contrasenia (S/N)
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    cout<<"\t\t\t\tELIMINAR CONTRASENIAS\n";
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;

    if(coleccionVacia(coleccion)){
        return;
    }

    idEliminar = leerEntero("Digite la id a eliminar: "); // el usuario digita su id
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    cout<<std::left;
    cout<<std::setw(MAX_ID)<<"ID"
        <<std::setw(MAX_NOMBRE)<<"Nombre"
        <<std::setw(MAX_DESCRIPCION)<<"Descripcion"
        <<std::setw(MAX_CONTRASENIA)<<"Contrasenia"<<endl;
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;

    bool encontrado = false;
    for(size_t i=0; i<coleccion.size(); i++){
        if(idEliminar == coleccion[i]->dameId()){
        encontrado = true;
            cout<<std::setw(MAX_ID)<<coleccion[i]->dameId()
                <<std::setw(MAX_NOMBRE)<<coleccion[i]->dameNombre()
                <<std::setw(MAX_DESCRIPCION)<<coleccion[i]->dameDescripcion()
                <<std::setw(MAX_CONTRASENIA)<<coleccion[i]->damePassword()<<endl;
            cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;

                cout<<"¿Desea eliminar estos datos? (S/n): ";
                cin>>confirmar;
                if(confirmar == 'S' || confirmar == 's'){
                    coleccion.erase(coleccion.begin() + i);
    /*Explicacion de "coleccion.erase(coleccion.begin() + i)":
        Supongamos que tenemos un vector de letras:
        Vector = [A,B,C,D,E]
    Posiciones->  0 1 2 3 4

    Ahora bien, queremos borrar la letra C del vector, digitamos la funcion ".erase()" para borrar algo de dicho vector,
    despues dentro de la funcion usamos el argumento ".begin() + 2" para indicar que debemos iniciar desde el principio
    del vector + 2 que seria la posicion que queremos eliminar dentro de este vector, al mismo tiempo, las posiciones se
    recorreran automaticamente evitando fugas de memoria

    El caso de la variable "i" es que cuando se digite una id por el usuario esta sera una copia de la posicion dentro del vector
    por lo cual se iterara hasta esa posicion y se eliminara ese espacio.
    */
                    cout<<"Contrasenia eliminada\n";
                }else{
                    cout<<"Eliminacion cancelada\n";
                }
        }else{
            cout<<"Error, la id digitada no existe"<<endl;
        }
    }
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    if(!encontrado){
        cout<<"Error, no existe una id con el numero "<<idEliminar;
    }
}

void Actualizar(std::vector<std::unique_ptr<contrasenia>>& coleccion){
    std::string nuevoNombre, nuevaDescripcion, nuevaPassword; // variables auxiliares para almacenar datos del usuario
    int idActualizar; // variable auxiliar utilizada para buscar dentro de la coleccion del objeto
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    cout<<"\t\t\t\tACTUALIZAR DATOS\n";
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;

    if(coleccionVacia(coleccion)){
        return;
    }

    idActualizar = leerEntero("Digite el numero de la id a modificar: ");
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    cout<<std::left;
    cout<<std::setw(MAX_ID)<<"ID"
        <<std::setw(MAX_NOMBRE)<<"Nombre"
        <<std::setw(MAX_DESCRIPCION)<<"Descripcion"
        <<std::setw(MAX_CONTRASENIA)<<"Contrasenia"<<endl;
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    // La variable "i" se usa como iterador dentro del ciclo for
    bool encontrado=false;
    for(size_t i=0; i<coleccion.size(); i++){
    /* Si el usuario digito una id que esta dentro de la iteracion de la coleccion, entonces se mostraran todos los datos al usuario
    sobre ese registro*/
        if(idActualizar == coleccion[i]->dameId()){
            encontrado=true;
            cout<<std::setw(MAX_ID)<<coleccion[i]->dameId()
                <<std::setw(MAX_NOMBRE)<<coleccion[i]->dameNombre()
                <<std::setw(MAX_DESCRIPCION)<<coleccion[i]->dameDescripcion()
                <<std::setw(MAX_CONTRASENIA)<<coleccion[i]->damePassword()<<endl;

                cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
                cout<<"Digite un nuevo nombre: "; getline(cin,nuevoNombre);
                cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
                cout<<"Digite una nueva descripcion: "; getline(cin,nuevaDescripcion);
                cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
                cout<<"Digite una nueva contrasenia: "; getline(cin,nuevaPassword);
                cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;

                coleccion[i]->fijaNombre(nuevoNombre);
                coleccion[i]->fijaDescripcion(nuevaDescripcion);
                coleccion[i]->fijaPassword(nuevaPassword);

                cout<<"Datos actualizados......."<<endl;
        }else{
            cout<<"Error, la id digitada no existe"<<endl;
        }
    }
    /*"size_t" es un tipo de dato especial para indices, este por ningun motivo puede iterar con numeros negativos
    "coleccion.size()": el bucle va a iterar dependiendo hasta que numero de elementos tenga registrados en mi objeto
    */
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
        if(!encontrado){
        cout<<"Error, no existe una id con el numero "<<idActualizar;
    }
}

void mostrarTodo(std::vector<std::unique_ptr<contrasenia>>& coleccion){
    if(coleccionVacia(coleccion)){ // si la coleccion de contrasenias esta vacia mostrara un mensaje y se retornara al menu
        return; // la funcion condicional se encuantra en el archivo "misc.h"
    }

    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl; // esto crea una cadena de 80 caracteres
    cout<<"\t\t\t\tMOSTRAR TODO\n";
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    // configuracion de los anchos de la columna
    cout<<std::left; // con esto todos los datos se alinean a la izquierda
    cout<<std::setw(MAX_ID)<<"ID" /*"setw()" reserva un numero de estacios para el siguiente elemento, se alinea a la derecha por defecto
    usa las variables contantes "MAX" en el archivo "misc.h" como numero de caracteres reservados para la creacion de la tabla*/
        <<std::setw(MAX_NOMBRE)<<"Nombre"
        <<std::setw(MAX_DESCRIPCION)<<"Descripcion"
        <<std::setw(MAX_CONTRASENIA)<<"Contrasenia"<<endl;
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    // la variable "i" se usa como iterador dentro del ciclo for
    for(size_t i=0; i<coleccion.size(); i++ ){
        cout<<std::setw(MAX_ID)<<coleccion[i]->dameId()
            <<std::setw(MAX_NOMBRE)<<coleccion[i]->dameNombre()
            <<std::setw(MAX_DESCRIPCION)<<coleccion[i]->dameDescripcion()
            <<std::setw(MAX_CONTRASENIA)<<coleccion[i]->damePassword()<<endl;
    }
    /*"size_t" es un tipo de dato especial para indices, este por ningun motivo puede iterar con numeros negativos
      "coleccion.size()": el bucle va a iterar dependiendo hasta que numero de elementos tenga registrados en mi objeto
        */
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
}

void Buscar(std::vector<std::unique_ptr<contrasenia>>& coleccion){
    int idBuscar; // variable auxiliar utilizada para buscar dentro de la coleccion del objeto

    if(coleccionVacia(coleccion)){ // si la coleccion de contrasenias esta vacia mostrara un mensaje y se retornara al menu
        return; // la funcion condicional se encuantra en el archivo "misc.h"
    }
 // Caso contrario el programa te pedira que digites la id a buscar y mostrara los resultados de la busqueda
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    cout<<"\t\t\t\tBUSCAR\n";
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    idBuscar = leerEntero("Digite la id a buscar: ");
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    cout<<std::left;
    cout<<std::setw(MAX_ID)<<"ID"
        <<std::setw(MAX_NOMBRE)<<"Nombre"
        <<std::setw(MAX_DESCRIPCION)<<"Descripcion"
        <<std::setw(MAX_CONTRASENIA)<<"Contrasenia"<<endl;
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;

    // La variable "i" se usa como iterador dentro del ciclo for
    bool encontrado=false;
    for(size_t i=0; i<coleccion.size(); i++){
    /* Si el usuario digito una id que esta dentro de la iteracion de la coleccion, entonces se mostraran todos los datos al usuario
    sobre ese registro*/
        if(idBuscar == coleccion[i]->dameId()){
        encontrado=true;
            cout<<std::setw(MAX_ID)<<coleccion[i]->dameId()
                <<std::setw(MAX_NOMBRE)<<coleccion[i]->dameNombre()
                <<std::setw(MAX_DESCRIPCION)<<coleccion[i]->dameDescripcion()
                <<std::setw(MAX_CONTRASENIA)<<coleccion[i]->damePassword()<<endl;
        }else{
            cout<<"Error, la id digitada no existe"<<endl;
        }
    }
    /*"size_t" es un tipo de dato especial para indices, este por ningun motivo puede iterar con numeros negativos
    "coleccion.size()": el bucle va a iterar dependiendo hasta que numero de elementos tenga registrados en mi objeto
    */
    cout<<std::string(MAX_LARGO_TABLA, '-')<<endl;
    if(!encontrado){
        cout<<"Error, no existe una id con el numero "<<idBuscar;
    }
}

#endif // LOGICA_H_INCLUDED
