#ifndef MENU_H
#define MENU_H
#include <Boton.h>
#include <vector>


class Menu
{
    public:
        Menu();
        Menu(string,string, float, float,string*,int ,sf::Event*,sf::RenderWindow*, float, float);
        void update();
        void draw();
        virtual ~Menu();
    protected:
    private:
        Boton ** botones;
        int num_botones;
        void setEvento(sf::Event*);
        float alto_boton, ancho_boton;
        float posx, posy;
    friend class Juego;
};

#endif // MENU_H
