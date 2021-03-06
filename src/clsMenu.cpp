//#############################################################################
// ARCHIVO             : clsMenu.cpp
// AUTOR               : Javier Eduardo Pereyra/Juan Agustin Gonzalez
// VERSION             : 1.0.
// FECHA DE CREACION   : 06/11/2018.
// ULTIMA ACTUALIZACION: 15/11/2018.          .
// LICENCIA            : GPL (General Public License) - Version 3.
//=============================================================================
// SISTEMA OPERATIVO   : Linux / Windows.
// IDE                 : Code::Blocks - 17.12.
// COMPILADOR          : GNU GCC Compiler (Linux) / MinGW (Windows).
//=============================================================================
// DESCRIPCION: Este archivo contiene la definici�n de los m�todos de la clas
//              "clsMenu".
//
//              "clsMenu" consta de los m�todos necesarios para el control del
//              juego con un sistema de men�.
//
///////////////////////////////////////////////////////////////////////////////
#include "clsMenu.h"

//=============================================================================
// METODO    : int init(clsScreen* scr, clsEvent* ev, clsMusic* mus)
// ACCION    : Inicializa los objetos de la clase.
// PARAMETROS: clsScreen* s --> puntero a la pantalla.
//             clsMusic* m --> puntero a la m�sica.
//             clsEvent* e --> puntero al manager de eventos.
// DEVUELVE  : int --> codigo de error. (0 = todo bien)
//-----------------------------------------------------------------------------
int clsMenu::init(clsScreen *s, clsMusic *m, clsEvent *e)
{
    screen = s;
    musicMenu = m;
    event = e;

    error.set(texto.init());
    if(error.get()) return error.get();
    error.set(texto.loadFont("FONTS/FreeMono.ttf", 30));
    if(error.get()) return error.get();
    texto.setFontColor(WHITE);

    error.set(fondoPuntajes.init("IMAGES/fondoPuntaje600x800.png"));
    if(error.get()) return error.get();

    setItems(3);
    char ruta[]= "IMAGES/MENUINTRO/00.png";
    for(int d=0; d<1; d++)
    {
        ruta[17] = d + 48;
        for(int u=0; u<10; u++)
        {
            ruta[18] = u + 48;
            setI(d*10+u);

            error.set(load(ruta));
            if(error.get())
                return error.get();

            if(d*10+u == 2)
                break;
        }
    }

    return error.get();
}

//=============================================================================
// METODO    : int run()
// ACCION    : Dispone el men� al jugador y toma acciones seg�n su decisi�n.
// PARAMETROS: NADA.
// DEVUELVE  : int --> codigo de error. (0 = todo bien)
//-----------------------------------------------------------------------------
int clsMenu::run()
{
    error.set(0);

    error.set(musicMenu->loadMusic("MUSIC/MENU.mp3"));
    if(error.get()) return error.get();

    musicMenu->playMusic(-1);
    setI(0);
    salir = false;

    while(!salir)
    {
        if(event->wasEvent())
        {
            if(event->getEventType() == SDL_QUIT)
            {
                musicMenu->closeMusic();
                return -1;
            }
            if(event->getEventType() == KEY_PRESSED)
            {
                switch(event->getKey())
                {
                    case KEY_ESCAPE:
                    {
                        musicMenu->closeMusic();
                        return -2;
                    }break;
                    case KEY_ENTER:
                    {
                        salir = true;
                    }break;
                    case KEY_UP:
                    {
                        if(getI() == 0)
                            setI(2);
                        else
                            setI(getI()-1);
                    }break;
                    case KEY_DOWN:
                    {
                        if(getI() == 2)
                            setI(0);
                        else
                            setI(getI()+1);
                    }break;
                }//Fin switch
            }//Fin if KEY_PRESSED
        }//Fin if wasEvent()
        paste(screen->getPtr());
        screen->refresh();
    }//Fin while

    musicMenu->closeMusic();

    if(getI() == 2)
    {
        return -2;
    }

    else if(getI() == 1)
    {
        char aux[5];
        int cant;
        while(true)
        {
            if(event->wasEvent())
            {
                if(event->getEventType() == SDL_QUIT) return -1;
                if(event->getEventType() == KEY_PRESSED)
                {
                    if(event->getKey() == KEY_ESCAPE) break;
                    if(event->getKey() == KEY_b)
                    {
                        puntajes.borrar();
                    }
                }
            }
            if(puntajes.cantPuntajes()<10) cant = puntajes.cantPuntajes();
            else cant = 10;
            puntajes.cargarYordenar();
            fondoPuntajes.paste(screen->getPtr());
            for(int x=0; x<cant; x++)
            {
                puntajes.setI(x);

                texto.write(puntajes.getPuntaje().getNombre(), 30, x*44+142, screen->getPtr());

                itoa(puntajes.getPuntaje().getPuntos(), aux, 10);
                texto.write(aux, screen->getWidth()/2+20, x*44+142, screen->getPtr());
            }
            texto.write("ESC para volver", 10, screen->getHeight()-30, screen->getPtr());
            texto.write("B para borrar puntajes", screen->getWidth()/2, screen->getHeight()-30, screen->getPtr());
            screen->refresh();
        }
        error.set(run());
        return error.get();
    }

    return 0;
}

