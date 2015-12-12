#ifndef OBJETO_H
#define OBJETO_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>


using namespace std;

class Objeto: public sf::Sprite
{
    public:
        Objeto(string, float, float);
        Objeto();
        void cambiar_anim(vector<sf::Texture*>);
        virtual void animar(float);
        virtual void update();
        virtual ~Objeto();
    protected:

    private:
        sf::Texture textura;
        vector <sf::Texture*> anim_actual;
        vector <sf::Texture*> anim_anterior;

        int pos_animacion=0;
        sf::Clock * t_animacion;
        sf::Event* evento;
        sf::RenderWindow* win;
        float alto;
        float ancho;
        sf::Vector2f Coordenadas;

    friend class Proyectil;
    friend class Personaje;
    friend class Nave;
    friend class Juego;
    friend class Hogar;
};

#endif // OBJETO_H
