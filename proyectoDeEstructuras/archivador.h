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
    examen borrarExamen();
    examen buscarExamen();
    
    
    
};

#endif /* archivador_h */
