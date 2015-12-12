#ifndef PROYECTIL_H
#define PROYECTIL_H
#include "Objeto.h"

class Proyectil: public Objeto
{
    public:
        Proyectil();
        Proyectil(string, float, float, sf::Event*,sf::RenderWindow*, sf::Vector2f, float, bool);
        virtual ~Proyectil();
        void update();
        sf::Clock * t_vida;

    protected:
    private:
        float velocidad;
};

#endif // PROYECTIL_H
