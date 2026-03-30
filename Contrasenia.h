#ifndef CONTRASENIA_H_INCLUDED
#define CONTRASENIA_H_INCLUDED
#include <iostream>
#include <string>
#include <memory> // inclusion de memoria dinamica inteligente
#include <vector>// inclusion de arreglos inteligentes

using std::cin, std::cout, std::endl;

/*Esta clase se encarga de organizar las contrasenias ingresadas por el usuario
  Cada alta constara de estos 4 atributos que seran obligatorios para su registro*/

class contrasenia{
// Atributos privados de la clase
    int id;
    std::string nombre;
    std::string descripcion;
    std::string password;

public:
    //Setters, se encargan de fijar datos a los atributos del objeto
    void fijaId(int i) { id = i;}
    void fijaNombre(std::string n) {nombre = n;}
    void fijaDescripcion(std::string d) {descripcion = d;}
    void fijaPassword(std::string p) {password = p;}

    //Getters, se encargan de devolver los datos del objeto
    int dameId() {return id;}
    std::string dameNombre() {return nombre;}
    std::string dameDescripcion() {return descripcion;}
    std::string damePassword() {return password;}
};


#endif // CONTRASENIA_H_INCLUDED
