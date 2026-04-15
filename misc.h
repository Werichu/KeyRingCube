#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED
#include <limits> // libreria para incluir limites a los tipos de datos
//-----------------------------
#define MAX_LARGO_TABLA 80
#define MAX_ID 8
#define MAX_NOMBRE 20
#define MAX_DESCRIPCION 25
#define MAX_CONTRASENIA 20
//Estas variables constantes son auxiliares para la tabla a la hora de imprimir valores en pantalla
//Dirigete a "Logica.h" a la funcion "mostrarTodo" para conocer su utilidad
//-----------------------------
#include "Contrasenia.h"
#include "Logica.h"


enum {SALIR,ALTA,BAJA,ACTUALIZAR,MOSTRAR,BUSCAR,GUARDAR,CARGAR};


//Esta funcion se encarga de validar si la coleccion de contrasenias esta vacia
// para ello pasamos a la funcion booleana la referencia del objeto y revisamos con un if si esta se encuentra con datos
bool coleccionVacia (std::vector<std::unique_ptr<contrasenia>>& coleccion){
    if (coleccion.empty()){
        cout<<"No hay contrasenias registradas\n";
        return true;
    }
    return false;
}

//Esta funcion se utiliza en todas las funciones que tengan que ver con alguna busqueda mendiente ID
int leerEntero(const std::string& mensaje){
/*const std::string&: significa que siempre se va a recibir un mensaje por referencia constante, no se va a copiar
    solo se va a leer
*/

    int valor;
    cout<<mensaje;

    while(!(cin>>valor)){ // mientras no se pueda leer unvalor entero
        cout<<"Error, ingrese un numero valido"<<endl;
        cin.clear(); // limpiamos el error
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiamos el buffer
        cout<<mensaje; // volvemos a pedir el mensaje
    }

    cin.ignore(); // limpiamos salto de linea

    return valor; // si se ingresa un numero correctamente se retorna el valor
}
#endif // MISC_H_INCLUDED
