//
//  main.cpp
//  proyectoDeEstructuras
//
//  Created by Jafeth  Vásquez and Kembly Quirós on 10/9/16.
//  Copyright © 2016 Jafeth Vásquez. All rights reserved.
//

#include <iostream>
#include "archivador.h"



int main(int argc, const char * argv[]) {
    cout << "Hola mundo"<< endl;
    examen *examen1 = new examen("julio" , "examen1");
    examen1->añadirSeccion(true, "RespuestaCorta1");
    examen1->añadirSeccion(true, "RespuestaCorta2");
    examen1->añadirSeccion(false, "Selecion Unica");
    cout << "PROBANDO AÑADIR SECCIONES" << endl;
    examen1->imprimirInforme();
    examen1->borrarSeccion("RespuestaCorta1");
    cout << "PROBANDO BORRAR SECCIONES" << endl;
    examen1->imprimirInforme();
    
    



    return 0;
}
