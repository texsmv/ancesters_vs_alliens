#ifndef BOTON_H
#define BOTON_H
#include <Objeto.h>




using namespace std;
class Boton
{
    public:
        Boton();
        Boton(string,string, float, float,string,sf::Event*,sf::RenderWindow*, float, float);
        void draw2();
        bool clicked();
        virtual ~Boton();
        void setEvento(sf::Event*);

    protected:
    private:
        float ancho, alto;

        string texto;
        string letra;
        sf::Event* evento;
        sf::RenderWindow* win;
        Objeto* boton;
        float Coor_x, Coor_y;
};

#endif // BOTON_H
