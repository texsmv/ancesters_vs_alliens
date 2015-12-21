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
        Objeto(sf::Texture*,float,float);
        void cambiar_anim(vector<sf::Texture*>);
        virtual void animar(float);
        virtual void update();
        virtual ~Objeto();
    protected:

    private:
        sf::Texture textura;
        vector <sf::Texture*> anim_actual;
        vector <sf::Texture*> anim_anterior;
        vector <sf::Texture*> anim_inicial;
        int pos_animacion=0;
        sf::Clock * t_animacion;
        sf::Clock * t_anim_inicial;
        sf::Event* evento;
        sf::RenderWindow* win;
        float alto;
        float ancho;
        sf::Vector2f Coordenadas;
        sf::Vector2f punto_medio;
    friend class Pet;
    friend class Proyectil;
    friend class Personaje;
    friend class Nave;
    friend class Juego;
    friend class Hogar;
    friend class Arquero;
    friend class Inca;
    friend class green_arrow;
    friend class Cleopatra;
    friend class light_arrow;
};

#endif // OBJETO_H
