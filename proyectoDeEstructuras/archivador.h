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
    examen examenEnNodo;
    nodoExamen *siguiente;
};

class archivador{
private:
    nodoExamen *listaExamenes;
    int cantidadExamenes;

public:
    void añadirExamen();
    void borrarExamen();
    examen buscarExamen();
};

archivador::añadirExamen(){
    nodoExamen *nuevoNodo = new nodoExamen();
    examen *nuevoExamen = new examen();//se crea examen con el constructor de examen

    nuevoNodo->examenEnNodo = nuevoExamen;//se apunta al examen en nodo el examen que se va a crear

    nuevoNodo->siguiente = archivador.listaExamenes;
    archivador.listaExamenes = nuevoNodo;
    archivador.cantidadExamenes++;
}

archivador::buscarExamen(string nombreExamen){
    nodoExamen *nodoActual = archivador.listaExamenes;
    while (nodoActual!=NULL){
        if (nodoActual->examenEnNodo->nombre== nombreExamen)//si el nombre del examen es igual al del nodo
            return nodoActual->examenEnNodo;
    nodoActual = nodoActual->siguiente;
    }
        return NULL;
}

archivador::borrarExamen(string nombreExamen){
    nodoExamen *nodoActual = archivador.listaExamenes;
    while ((nodoActual!= NULL) && (nodoActual->examenEnNodo->nombre != nombreExamen)){
        nodoActual=nodoActual->siguiente;
    }
        if (nodoActual!=NULL){
            if (archivador.listaExamenes->examenEnNodo->nombre == nombreExamen){
            archivador.listaExamenes = nodoActual->siguiente;
            free(nodoActual);
            return;
        } else if (nodoActual->siguiente->examenEnNodo->nombre == nombreExamen){
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
