#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED
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
#endif // MISC_H_INCLUDED
