//#############################################################################
// ARCHIVO             : clsMotor.cpp
// AUTOR               : Javier Pereyra
// VERSION             : 1.0.
// FECHA DE CREACION   : 06/10/2018.
// ULTIMA ACTUALIZACION: 15/11/2018.          .
// LICENCIA             : GPL (General Public License) - Version 3.
//=============================================================================
// SISTEMA OPERATIVO   : Linux / Windows.
// IDE                 : Code::Blocks - 17.12.
// COMPILADOR          : GNU GCC Compiler (Linux) / MinGW (Windows).
//=============================================================================
// DESCRIPCION: Este archivo contiene la definici�n de los m�todos de la clas
//              "clsMotor".
//
//              "clsMotor" consta de los objetos necesarios para levantar el
//              modo gr�fico, la presentaci�n, el juego y la salida.
//
///////////////////////////////////////////////////////////////////////////////
#include "clsIntro.h"

int clsIntro::init(clsScreen *s, clsMusic *m, clsEvent *e, clsTimer *t)
{
    screen = s;
    music = m;
    event = e;
    timer = t;

    error.set(music->loadMusic("MUSIC/PRESENTACION.mp3"));
    if(error.get()) return error.get();

    error.set(texto.init());
    if(error.get()) return error.get();

    error.set(texto.loadFont("FONTS/FreeMono.ttf",30));
    if(error.get()) return error.get();

    texto.setFontColor(WHITE);

    setItems(14);
    char ruta[]= "IMAGES/MAGOINTRO/00.jpg";
    for(int d=0; d<2; d++)
    {
        ruta[17] = d + 48;
        for(int u=0; u<10; u++)
        {
            ruta[18] = u + 48;
            setI(d*10+u);

            error.set(load(ruta));
            if(error.get()) return error.get();

            if(d*10+u == 13)
                break;
        }
    }
    setI(0);

    return error.get();
}

void clsIntro::animar()
{
    paste(screen->getPtr());
    if(getI() == 13)
        setI(0);
    else
        setI(getI() + 1);
}

int clsIntro::run()
{
    error.set(0);

    music->playMusic(-1);

    texto.write("Magic Software",400,200,screen->getPtr());
    texto.write("Presenta",100,400,screen->getPtr());
    texto.write("�CalaBird!",200,500,screen->getPtr());

    while(true)
    {
        if(event->wasEvent())
        {
            if(event->getEventType() == SDL_QUIT || event->getKey() == KEY_ESCAPE)
            {
                music->closeMusic();
                return -1;
            }
            if(event->getKey() == KEY_ENTER)
            {
                music->closeMusic();
                return 0;
            }
        }
        timer->wait(150);
        animar();
        screen->refresh();
    }

    return error.get();
}











