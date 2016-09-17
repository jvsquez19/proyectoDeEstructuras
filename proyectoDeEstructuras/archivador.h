//
//  archivador.h
//  proyectoDeEstructuras
//
//  Created by Jafeth  Vásquez on 11/9/16.
//  Copyright © 2016 Jafeth Vásquez. All rights reserved.
//

#ifndef archivador_h
#define archivador_h
#include "examen.h"

struct nodoExamen{
    examen *examenEnNodo;
    nodoExamen *siguiente;
};

class archivador{
private:
    nodoExamen *listaExamenes;
    int cantidadExamenes;

public:
    void añadirExamen();
    void borrarExamen(string nombreExamen);
    bool buscarExamen(string nombreExamen);
};

void archivador::añadirExamen(){
    nodoExamen *nuevoNodo = new nodoExamen();
    examen *nuevoExamen = new examen("jose","Ejemplo");//se crea examen con el constructor de examen

    nuevoNodo->examenEnNodo = nuevoExamen;//se apunta al examen en nodo el examen que se va a crear

    nuevoNodo->siguiente = listaExamenes;
    listaExamenes = nuevoNodo;
    cantidadExamenes++;
}

bool archivador::buscarExamen(string nombreExamen){
    nodoExamen *nodoActual = listaExamenes;
    while (nodoActual!=NULL){
        if (nodoActual->examenEnNodo->getNombre()== nombreExamen)//si el nombre del examen es igual al del nodo
            return true;
    nodoActual = nodoActual->siguiente;
    }
        return false ;
}

void archivador::borrarExamen(string nombreExamen){
    nodoExamen *nodoActual = listaExamenes;
    while ((nodoActual!= NULL) && (nodoActual->examenEnNodo->getNombre() != nombreExamen)){
        nodoActual=nodoActual->siguiente;
    }
        if (nodoActual!=NULL){
            if (listaExamenes->examenEnNodo->getNombre() == nombreExamen){
            listaExamenes = nodoActual->siguiente;
            free(nodoActual);
            return;
        } else if (nodoActual->siguiente->examenEnNodo->getNombre()== nombreExamen){
            nodoExamen *nodoBorrar = nodoActual->siguiente;
            nodoActual->siguiente = nodoActual->siguiente->siguiente;
            free(nodoBorrar);
            return;
        } else {
            free(nodoActual);
            return;
        }
    }
}
#endif /* archivador_h */
