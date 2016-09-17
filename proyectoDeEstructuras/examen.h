//
//  examen.h
//  proyectoDeEstructuras
//
//  Created by Jafeth  Vásquez on 11/9/16.
//  Copyright © 2016 Jafeth Vásquez. All rights reserved.
//

#ifndef examen_h
#define examen_h
#include "seccion.h"

struct nodoSeccion{
    seccion *seccionActual;
    nodoSeccion *siguiente;
};

class examen{
private:
    int puntaje;
    int notaObtenida;
    nodoSeccion *listaSecciones;
    string estudiante;
    string profesor;
    string nombre;
public:
    examen(string profesorEntrante, string entradaNombre){
        string nombre = entradaNombre;
        puntaje = 0;
        notaObtenida = 0;
        listaSecciones = NULL;
        estudiante = "";
        profesor = profesorEntrante;
        
        
    }
    int calificar();
    void añadirSeccion(bool tipo, string nombre);
    void borrarSeccion(string nombre);
    void imprimirInforme();
    void modificar();
    void setPuntaje();
    int getPuntaje;
    void setnotaObtenida();
    int getnotaObtenida();
    void setEstudiante();
    string getEstudiante();
    void setProfesor(string profeNuevo);
    string getProfesor();
    void setNombre(string entradaNombre);
    string getNombre();

};


void examen::añadirSeccion(bool tipo, string nombre){
    seccion *nuevaSeccion = new seccion(tipo, nombre);
    nodoSeccion *nuevoNodo = new nodoSeccion();
    nuevoNodo->seccionActual = nuevaSeccion;
    nuevoNodo->siguiente = listaSecciones;
    listaSecciones = nuevoNodo;
    
};

void examen::borrarSeccion(string nombre){
    nodoSeccion *actual = listaSecciones;
    if(actual->seccionActual->getNombre()==nombre){
        listaSecciones = actual->siguiente;
        free(actual);
        return;
    }
    while(actual!= NULL){
            if(actual->siguiente->seccionActual->getNombre() == nombre){
                nodoSeccion *aBorrar = actual->siguiente;
                actual->siguiente = actual->siguiente->siguiente;
                free(aBorrar);
                return;
        }
        else
            actual = actual->siguiente;
        return;
        
    }
}

int examen::calificar(){
    int puntaje;
    nodoSeccion *actual = listaSecciones;
    while (actual != NULL) {
        puntaje += actual->seccionActual->calificar();
    }
    
    return puntaje;
}

void examen::setProfesor(string profeNuevo){
    profesor = profeNuevo;
    
}

string examen::getProfesor(){
    return profesor;
}

void examen::setNombre(string entradaNombre){
    nombre = entradaNombre;
    
}

string examen::getNombre(){
    return nombre;
}









#endif /* examen_h */



