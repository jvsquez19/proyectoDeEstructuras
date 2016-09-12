//
//  seccion.h
//  proyectoDeEstructuras
//
//  Created by Jafeth  Vásquez on 11/9/16.
//  Copyright © 2016 Jafeth Vásquez. All rights reserved.
//

#ifndef seccion_h
#define seccion_h

using namespace std;


struct preguntaSeleccionUnica{
    string textoPregunta;
    int cantOpciones;
    int respuestaCorrecta;
};

struct preguntaRespuestaCorta{
    string textoPregunta;
    string RespuestaCorrecta;
    int PuntajeDePregunta;
    int PuntajeObtenido;
};


class seccion{
private:
    int valorEnPuntos;
public:
    seccion(int puntos){
        valorEnPuntos = puntos;
        
    }
    
    
    
};

#endif /* seccion_h */
