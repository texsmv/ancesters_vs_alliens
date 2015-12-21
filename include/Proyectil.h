#ifndef PROYECTIL_H
#define PROYECTIL_H
#include "Objeto.h"

class Proyectil: public Objeto
{
    public:
        Proyectil();
        Proyectil(string, float, float, sf::Event*,sf::RenderWindow*, sf::Vector2f, float, bool);
        virtual ~Proyectil();
        virtual void update();
        sf::Clock * t_vida;

    protected:
    private:
        sf::Vector2f velocidad;
        int rango_colision;
        bool start_last_anim=false;
        bool destroy=false;
        bool empezo_t_muerte=false;
        sf::Clock* t_muerte;
        vector <sf::Texture*> arrow_anim;
        bool b_anim_inicial=true;
        float damage;
        bool anim_colision=false;

    friend class green_arrow;
    friend class Juego;
    friend class Arquero;
    friend class Personaje;
    friend class light_arrow;
    friend class Cleopatra;
};

#endif // PROYECTIL_H
