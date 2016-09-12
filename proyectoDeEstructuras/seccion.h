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

struct nodoPreguntaSeleccionUnica{
    preguntaSeleccionUnica preguntaActual;
    nodoPreguntaSeleccionUnica *siguiente;
};

struct nodoPreguntaRespuestaCorta{
    preguntaSeleccionUnica preguntaActual;
    nodoPreguntaRespuestaCorta *siguiente;
};


class seccion{
private:
    int PuntajeDeSeccion;
    int PuntajeDeSeccionObtenido;
    
public:
    void ImprimirInforme();
    void anadirPregunta();
    
    
};

#endif /* seccion_h */
